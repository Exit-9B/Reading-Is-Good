#pragma once

class OnSkillBookReadRegSet : public SKSE::RegistrationSet<const RE::TESObjectBOOK*, int32_t>
{
public:
	using Base = SKSE::RegistrationSet<const RE::TESObjectBOOK*, int32_t>;

	static OnSkillBookReadRegSet* GetSingleton();

private:
	OnSkillBookReadRegSet();
	OnSkillBookReadRegSet(const OnSkillBookReadRegSet&) = delete;
	OnSkillBookReadRegSet(OnSkillBookReadRegSet&&) = delete;
	~OnSkillBookReadRegSet() = default;

	OnSkillBookReadRegSet& operator=(const OnSkillBookReadRegSet&) = delete;
	OnSkillBookReadRegSet& operator=(OnSkillBookReadRegSet&&) = delete;
};
