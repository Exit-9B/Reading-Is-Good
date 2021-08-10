#include "Registration.h"

OnSkillBookReadRegSet* OnSkillBookReadRegSet::GetSingleton()
{
	static OnSkillBookReadRegSet singleton;
	return std::addressof(singleton);
}

OnSkillBookReadRegSet::OnSkillBookReadRegSet() : Base("OnSkillBookRead"sv)
{
}
