#include "Hooks.h"
#include "Offsets.h"
#include "Registration.h"
#include "xbyak/xbyak.h"

namespace Hooks
{
	class PlayerCharacterEx : public RE::PlayerCharacter
	{
	public:
		static void InstallHooks()
		{
			REL::Relocation<std::uintptr_t> hook{ Offset::TESObjectBOOK_Read, 0xA3 };

			struct Patch : Xbyak::CodeGenerator {
				Patch() {
					movss(xmm1, dword[rsp + 0x78]); // A3+6
					mov(rcx, rdi); // A9+3
					mov(rax, SKSE::unrestricted_cast<std::uintptr_t>(ReadSkillBook)); // AC+A
					call(rax); // B6+2
				}
			} patch;
			patch.ready();
			assert(patch.getSize() == 0x15);

			REL::safe_write(hook.address(), patch.getCode(), patch.getSize());

			logger::info("Installed hooks for (%s)", typeid(PlayerCharacterEx).name());
		}

	private:
		static void ReadSkillBook(RE::TESObjectBOOK* a_book, [[maybe_unused]] float a_increment)
		{
			auto skill = a_book->GetSkill();
			const char* skillName = GetSkillName(skill);

			if (ShowNotifications())
			{
				auto strHolder = RE::InterfaceStrings::GetSingleton();
				char strBuf[200];
				const char* format = "%s insight gained."; // TODO localize this
				snprintf(strBuf, 200, format, skillName);

				const char* sound = nullptr;
				if (PlaySound())
				{
					sound = "RIGInsightGainedSD";
				}

				// Don't mind the name, this function is used everywhere in the engine
				RE::DebugNotification(strBuf, sound, true);
			}

			auto regs = OnSkillBookReadRegSet::GetSingleton();
			regs->QueueEvent(a_book, static_cast<int32_t>(skill));
		}

		static const char* GetFormatString()
		{
			static auto form = RE::TESForm::LookupByEditorID("RIG_sInsightGained");
			static auto mesg = skyrim_cast<RE::BGSMessage*>(form);

			if (!mesg)
				return nullptr;

			RE::BSString str;
			mesg->GetDescription(str, nullptr);
			return str.c_str();
		}

		static bool ShowNotifications()
		{
			static auto form = RE::TESForm::LookupByEditorID("RIG_ShowNotification");
			static auto glob = skyrim_cast<RE::TESGlobal*>(form);

			if (!glob)
				return true;

			return glob->value;
		}

		static bool PlaySound()
		{
			static auto form = RE::TESForm::LookupByEditorID("RIG_PlaySound");
			static auto glob = skyrim_cast<RE::TESGlobal*>(form);

			if (!glob)
				return true;

			return glob->value;
		}

		static const char* GetSkillName(RE::ActorValue a_skill)
		{
			static REL::Relocation<decltype(GetSkillName)> func{ Offset::GetSkillName };
			return func(a_skill);
		}
	};

	void Install()
	{
		PlayerCharacterEx::InstallHooks();
		logger::info("Installed all hooks");
	}
}