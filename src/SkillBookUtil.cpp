#include "SkillBookUtil.h"
#include "Registration.h"
#include "BookHandler.h"
#include "Offsets.h"

namespace SkillBookUtil
{
	void RegisterForOnSkillBookReadEvent(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BGSRefAlias* a_alias)
	{
		if (!a_alias)
		{
			a_vm->TraceStack("akAlias is a NONE alias!", a_stackID, Severity::kWarning);
			return;
		}

		auto regs = OnSkillBookReadRegSet::GetSingleton();
		regs->Register(a_alias);
	}

	void UnregisterForOnSkillBookReadEvent(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BGSRefAlias* a_alias)
	{
		if (!a_alias)
		{
			a_vm->TraceStack("akAlias is a NONE alias!", a_stackID, Severity::kWarning);
			return;
		}

		auto regs = OnSkillBookReadRegSet::GetSingleton();
		regs->Unregister(a_alias);
	}

	bool AddReadSkillBooksToLists(RE::StaticFunctionTag*, std::vector<RE::BGSListForm*> a_lists)
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

	std::string GetSkillName(RE::StaticFunctionTag*, int32_t a_actorValue)
	{
		static REL::Relocation<const char*(int32_t)> func{ Offset::GetSkillName };
		return func(a_actorValue);
	}

	bool RegisterFuncs(VM* a_vm)
	{
		a_vm->RegisterFunction("RegisterForOnSkillBookReadEvent"sv, "RIG_SkillBookUtil"sv, RegisterForOnSkillBookReadEvent, true);
		a_vm->RegisterFunction("UnregisterForOnSkillBookReadEvent"sv, "RIG_SkillBookUtil"sv, UnregisterForOnSkillBookReadEvent, true);
		a_vm->RegisterFunction("GetSkillName"sv, "RIG_SkillBookUtil"sv, GetSkillName, true);
		a_vm->RegisterFunction("AddReadSkillBooksToLists"sv, "RIG_SkillBookUtil"sv, AddReadSkillBooksToLists, true);

		return true;
	}
}