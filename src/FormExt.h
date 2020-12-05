#pragma once

namespace FormExt
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	void RegisterForSkillBookReadEvent(
		VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*,
		const RE::TESForm* a_form);

	void UnregisterForSkillBookReadEvent(
		VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*,
		const RE::TESForm* a_form);

	bool RegisterFuncs(VM* a_vm);
}
