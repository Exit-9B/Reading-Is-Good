#include "Papyrus.h"
#include "Papyrus/ActiveMagicEffectExt.h"
#include "Papyrus/AliasExt.h"
#include "Papyrus/FormExt.h"
#include "Papyrus/SkillBookUtil.h"

bool Papyrus::RegisterFuncs(RE::BSScript::IVirtualMachine* a_vm)
{
	ActiveMagicEffectExt::RegisterFuncs(a_vm);
	logger::info("Registered RIG_ActiveMagicEffectExt"sv);

	AliasExt::RegisterFuncs(a_vm);
	logger::info("Registered RIG_AliasExt"sv);

	FormExt::RegisterFuncs(a_vm);
	logger::info("Registered RIG_FormExt"sv);

	SkillBookUtil::RegisterFuncs(a_vm);
	logger::info("Registered RIG_SkillBookUtil"sv);

	return true;
}