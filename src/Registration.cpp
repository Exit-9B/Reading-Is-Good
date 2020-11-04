#include "Registration.h"

OnSkillBookReadRegSet* OnSkillBookReadRegSet::GetSingleton()
{
	static OnSkillBookReadRegSet singleton;
	return &singleton;
}

OnSkillBookReadRegSet::OnSkillBookReadRegSet() :
	Base("OnSkillBookRead"sv)
{ }