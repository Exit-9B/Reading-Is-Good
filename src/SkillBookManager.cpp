#include "SkillBookManager.h"
#include "Offsets.h"
#include "Registration.h"
#include "xbyak/xbyak.h"

void SkillBookManager::InstallHooks()
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

	logger::info("Installed hooks for (%s)", typeid(SkillBookManager).name());
}

const char* SkillBookManager::GetSkillName(RE::ActorValue a_skill)
{
	static REL::Relocation<decltype(GetSkillName)> func{ Offset::GetSkillName };
	return func(a_skill);
}

void SkillBookManager::ReadSkillBook(
	RE::TESObjectBOOK* a_book,
	[[maybe_unused]] float a_increment)
{
	auto skill = a_book->GetSkill();
	auto regs = OnSkillBookReadRegSet::GetSingleton();
	regs->QueueEvent(a_book, static_cast<int32_t>(skill));
}