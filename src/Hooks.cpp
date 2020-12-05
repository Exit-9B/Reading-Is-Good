#include "Hooks.h"
#include "SkillBookManager.h"
#include "Offsets.h"
#include "Registration.h"
#include "xbyak/xbyak.h"

void Hooks::Install()
{
	SkillBookManager::InstallHooks();
	logger::info("Installed all hooks");
}