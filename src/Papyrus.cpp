#include "Papyrus.h"
#include "SkillBookUtil.h"

namespace Papyrus
{
	void Register()
	{
		auto papyrus = SKSE::GetPapyrusInterface();

		papyrus->Register(SkillBookUtil::RegisterFuncs);
		logger::info("Registered RIG_Utility"sv);
	}
}