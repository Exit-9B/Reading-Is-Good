#include "SkillBookManager.h"
#include "Offsets.h"
#include "Patches.h"
#include "Registration.h"

void SkillBookManager::InstallHooks()
{
	Patch::WriteSkillBookPatch(ReadSkillBook);
}

const char* SkillBookManager::GetSkillName(RE::ActorValue a_skill)
{
	static REL::Relocation<decltype(GetSkillName)> func{ Offset::GetSkillName };
	return func(a_skill);
}

void SkillBookManager::ReadSkillBook(RE::TESObjectBOOK* a_book, float a_increment)
{
	auto skill = a_book->GetSkill();
	auto regs = OnSkillBookReadRegSet::GetSingleton();
	regs->QueueEvent(a_book, skill, static_cast<int32_t>(a_increment));
}
