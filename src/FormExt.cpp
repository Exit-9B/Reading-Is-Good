#include "FormExt.h"
#include "Registration.h"

#define REGISTER(vm, script_name, fn_name) \
vm->RegisterFunction(#fn_name ## sv, script_name, fn_name, true)

namespace FormExt
{
	void RegisterForSkillBookReadEvent(
		VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*,
		const RE::TESForm* a_form)
	{
		if (!a_form)
		{
			a_vm->TraceStack("akForm is a NONE form!", a_stackID, Severity::kWarning);
			return;
		}

		auto regs = OnSkillBookReadRegSet::GetSingleton();
		regs->Register(a_form);
	}

	void UnregisterForSkillBookReadEvent(
		VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*,
		const RE::TESForm* a_form)
	{
		if (!a_form)
		{
			a_vm->TraceStack("akForm is a NONE form!", a_stackID, Severity::kWarning);
			return;
		}

		auto regs = OnSkillBookReadRegSet::GetSingleton();
		regs->Unregister(a_form);
	}

	bool RegisterFuncs(VM* a_vm)
	{
		constexpr std::string_view scriptname = "RIG_FormExt"sv;
		REGISTER(a_vm, scriptname, RegisterForSkillBookReadEvent);
		REGISTER(a_vm, scriptname, UnregisterForSkillBookReadEvent);

		return true;
	}
}
