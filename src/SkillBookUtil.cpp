#include "SkillBookUtil.h"
#include "Registration.h"
#include "SkillBookManager.h"
#include "BookHandler.h"

#define str(a) #a ## sv
#define REGISTER(vm, script_name, fn_name) \
vm->RegisterFunction(str(fn_name), script_name, fn_name, true)

namespace SkillBookUtil
{
	void RegisterForOnSkillBookReadEvent(
		VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*,
		const RE::BGSRefAlias* a_alias)
	{
		if (!a_alias)
		{
			a_vm->TraceStack("akAlias is a NONE alias!", a_stackID, Severity::kWarning);
			return;
		}

		auto regs = OnSkillBookReadRegSet::GetSingleton();
		regs->Register(a_alias);
	}

	void UnregisterForOnSkillBookReadEvent(
		VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*,
		const RE::BGSRefAlias* a_alias)
	{
		if (!a_alias)
		{
			a_vm->TraceStack("akAlias is a NONE alias!", a_stackID, Severity::kWarning);
			return;
		}

		auto regs = OnSkillBookReadRegSet::GetSingleton();
		regs->Unregister(a_alias);
	}

	std::string GetSkillName(RE::StaticFunctionTag*, RE::ActorValue a_actorValue)
	{
		return SkillBookManager::GetSkillName(a_actorValue);
	}

	void Notification(RE::StaticFunctionTag*,
		RE::BGSMessage* a_format,
		RE::ActorValue a_actorValue,
		std::string a_soundID)
	{
		char strBuf[200];
		const char* format = a_format->GetFullName();
		const char* skillName = SkillBookManager::GetSkillName(a_actorValue);
		snprintf(strBuf, 200, format, skillName);

		const char* sound = a_soundID.empty() ? nullptr : a_soundID.c_str();

		// Don't mind the name, this function is used everywhere in the engine
		RE::DebugNotification(strBuf, sound, true);
	}

	bool AddReadSkillBooksToLists(
		RE::StaticFunctionTag*,
		std::vector<RE::BGSListForm*> a_lists)
	{
		constexpr int32_t numSkills = 18;
		constexpr int32_t firstSkill = 6;

		if (a_lists.size() != numSkills)
			return false;

		int32_t booksUpdated = 0;

		for (auto [book, skill] : BookHandler::GetSingleton().SkillBooks)
		{
			if (book->IsRead())
			{
				int32_t skillIndex = static_cast<int32_t>(skill) - firstSkill;
				if (skillIndex >= 0 && skillIndex < numSkills)
				{
					if (!a_lists[skillIndex]->HasForm(book))
					{
						a_lists[skillIndex]->AddForm(book);
						booksUpdated++;
					}
				}
			}
		}

		if (booksUpdated > 0)
		{
			logger::info("Found (%i) skill books read before installing"sv, booksUpdated);
		}

		return booksUpdated > 0;
	}

	bool RegisterFuncs(VM* a_vm)
	{
		constexpr std::string_view scriptname = "RIG_SkillBookUtil"sv;
		REGISTER(a_vm, scriptname, RegisterForOnSkillBookReadEvent);
		REGISTER(a_vm, scriptname, UnregisterForOnSkillBookReadEvent);
		REGISTER(a_vm, scriptname, GetSkillName);
		REGISTER(a_vm, scriptname, Notification);
		REGISTER(a_vm, scriptname, AddReadSkillBooksToLists);

		return true;
	}
}