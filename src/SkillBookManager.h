#pragma once

class SkillBookManager
{
public:
	SkillBookManager() = delete;

	static void InstallHooks();

	static const char* GetSkillName(RE::ActorValue a_skill);

private:
	static void ReadSkillBook(RE::TESObjectBOOK* a_book, float a_increment);
};
