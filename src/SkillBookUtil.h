#pragma once

namespace SkillBookUtil
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	void RegisterForOnSkillBookReadEvent(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BGSRefAlias* a_alias);
	void UnregisterForOnSkillBookReadEvent(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BGSRefAlias* a_alias);
	bool AddReadSkillBooksToLists(RE::StaticFunctionTag*, std::vector<RE::BGSListForm*> a_lists);
	std::string GetSkillName(RE::StaticFunctionTag*, int32_t a_actorValue);

	bool RegisterFuncs(VM* a_vm);
}
