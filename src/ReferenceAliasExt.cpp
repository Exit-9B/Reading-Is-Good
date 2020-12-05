#include "ReferenceAliasExt.h"
#include "Registration.h"

#define REGISTER(vm, script_name, fn_name) \
vm->RegisterFunction(#fn_name ## sv, script_name, fn_name, true)

namespace ReferenceAliasExt
{
	void RegisterForSkillBookReadEvent(
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

	void UnregisterForSkillBookReadEvent(
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

	bool RegisterFuncs(VM* a_vm)
	{
		constexpr std::string_view scriptname = "RIG_ReferenceAliasExt"sv;
		REGISTER(a_vm, scriptname, RegisterForSkillBookReadEvent);
		REGISTER(a_vm, scriptname, UnregisterForSkillBookReadEvent);

		return true;
	}
}
