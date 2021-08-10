#include "AliasExt.h"
#include "Registration.h"

#define REGISTER(vm, script_name, fn_name) \
	vm->RegisterFunction(#fn_name##sv, script_name, fn_name, true)

void AliasExt::RegisterForSkillBookReadEvent(
	VM* a_vm,
	StackID a_stackID,
	RE::StaticFunctionTag*,
	const RE::BGSBaseAlias* a_alias)
{
	if (!a_alias) {
		a_vm->TraceStack("akAlias is a NONE alias!", a_stackID, Severity::kWarning);
		return;
	}

	auto regs = OnSkillBookReadRegSet::GetSingleton();
	regs->Register(a_alias);
}

void AliasExt::UnregisterForSkillBookReadEvent(
	VM* a_vm,
	StackID a_stackID,
	RE::StaticFunctionTag*,
	const RE::BGSBaseAlias* a_alias)
{
	if (!a_alias) {
		a_vm->TraceStack("akAlias is a NONE alias!", a_stackID, Severity::kWarning);
		return;
	}

	auto regs = OnSkillBookReadRegSet::GetSingleton();
	regs->Unregister(a_alias);
}

bool AliasExt::RegisterFuncs(VM* a_vm)
{
	constexpr std::string_view scriptname = "RIG_AliasExt"sv;
	REGISTER(a_vm, scriptname, RegisterForSkillBookReadEvent);
	REGISTER(a_vm, scriptname, UnregisterForSkillBookReadEvent);

	return true;
}
