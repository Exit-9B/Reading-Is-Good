#include "Papyrus.h"
#include "ReferenceAliasExt.h"
#include "SkillBookUtil.h"

namespace Papyrus
{
	void Register()
	{
		auto papyrus = SKSE::GetPapyrusInterface();

		papyrus->Register(ReferenceAliasExt::RegisterFuncs);
		logger::info("Registered RIG_ReferenceAliasExt"sv);

		papyrus->Register(SkillBookUtil::RegisterFuncs);
		logger::info("Registered RIG_SkillBookUtil"sv);
	}
}