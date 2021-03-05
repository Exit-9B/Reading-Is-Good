#include "Papyrus.h"
#include "ActiveMagicEffectExt.h"
#include "AliasExt.h"
#include "FormExt.h"
#include "SkillBookUtil.h"

void Papyrus::Register()
{
	auto papyrus = SKSE::GetPapyrusInterface();

	papyrus->Register(ActiveMagicEffectExt::RegisterFuncs);
	logger::info("Registered RIG_ActiveMagicEffectExt"sv);

	papyrus->Register(AliasExt::RegisterFuncs);
	logger::info("Registered RIG_AliasExt"sv);

	papyrus->Register(FormExt::RegisterFuncs);
	logger::info("Registered RIG_FormExt"sv);

	papyrus->Register(SkillBookUtil::RegisterFuncs);
	logger::info("Registered RIG_SkillBookUtil"sv);
}