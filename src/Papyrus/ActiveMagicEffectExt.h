#pragma once

namespace ActiveMagicEffectExt
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	void RegisterForSkillBookReadEvent(
		VM* a_vm,
		StackID a_stackID,
		RE::StaticFunctionTag*,
		const RE::ActiveEffect* a_alias);

	void UnregisterForSkillBookReadEvent(
		VM* a_vm,
		StackID a_stackID,
		RE::StaticFunctionTag*,
		const RE::ActiveEffect* a_alias);

	bool RegisterFuncs(VM* a_vm);
}
