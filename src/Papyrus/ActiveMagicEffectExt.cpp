#include "Papyrus/ActiveMagicEffectExt.h"
#include "Registration.h"

#define REGISTER(vm, script_name, fn_name) \
	vm->RegisterFunction(#fn_name##sv, script_name, fn_name, true)

void ActiveMagicEffectExt::RegisterForSkillBookReadEvent(
	VM* a_vm,
	StackID a_stackID,
	RE::StaticFunctionTag*,
	const RE::ActiveEffect* a_alias)
{
	if (!a_alias) {
		a_vm->TraceStack("akEffect is a NONE effect!", a_stackID, Severity::kWarning);
		return;
	}

	auto regs = OnSkillBookReadRegSet::GetSingleton();
	regs->Register(a_alias);
}

void ActiveMagicEffectExt::UnregisterForSkillBookReadEvent(
	VM* a_vm,
	StackID a_stackID,
	RE::StaticFunctionTag*,
	const RE::ActiveEffect* a_alias)
{
	if (!a_alias) {
		a_vm->TraceStack("akEffect is a NONE effect!", a_stackID, Severity::kWarning);
		return;
	}

	auto regs = OnSkillBookReadRegSet::GetSingleton();
	regs->Unregister(a_alias);
}

bool ActiveMagicEffectExt::RegisterFuncs(VM* a_vm)
{
	constexpr std::string_view scriptname = "RIG_ActiveMagicEffectExt"sv;
	REGISTER(a_vm, scriptname, RegisterForSkillBookReadEvent);
	REGISTER(a_vm, scriptname, UnregisterForSkillBookReadEvent);

	return true;
}
