#include "Papyrus.h"
#include "ActiveMagicEffectExt.h"
#include "AliasExt.h"
#include "FormExt.h"
#include "SkillBookUtil.h"

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