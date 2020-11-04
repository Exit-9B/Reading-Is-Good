#include "Hooks.h"
#include "SkillBookManager.h"
#include "Offsets.h"
#include "Registration.h"
#include "xbyak/xbyak.h"

namespace Hooks
{
	void Install()
	{
		SkillBookManager::InstallHooks();
		logger::info("Installed all hooks");
	}
}