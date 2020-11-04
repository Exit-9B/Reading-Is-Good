#pragma once

namespace SkillBookUtil
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	void RegisterForOnSkillBookReadEvent(
		VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*,
		const RE::BGSRefAlias* a_alias);

	void UnregisterForOnSkillBookReadEvent(
		VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*,
		const RE::BGSRefAlias* a_alias);

	std::string GetSkillName(
		RE::StaticFunctionTag*,
		RE::ActorValue a_actorValue);

	void Notification(
		RE::StaticFunctionTag*,
		RE::BGSMessage* a_format,
		RE::ActorValue a_actorValue,
		std::string a_soundID);

	bool AddReadSkillBooksToLists(
		RE::StaticFunctionTag*,
		std::vector<RE::BGSListForm*> a_lists);

	bool RegisterFuncs(VM* a_vm);
}
