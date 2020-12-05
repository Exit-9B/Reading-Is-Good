#include "Papyrus.h"
#include "FormExt.h"
#include "ReferenceAliasExt.h"
#include "SkillBookUtil.h"

void Papyrus::Register()
{
	auto papyrus = SKSE::GetPapyrusInterface();

	papyrus->Register(FormExt::RegisterFuncs);
	logger::info("Registered RIG_FormExt"sv);

	papyrus->Register(ReferenceAliasExt::RegisterFuncs);
	logger::info("Registered RIG_ReferenceAliasExt"sv);

	papyrus->Register(SkillBookUtil::RegisterFuncs);
	logger::info("Registered RIG_SkillBookUtil"sv);
}