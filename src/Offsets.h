#pragma once

namespace Offset
{
#ifndef SKYRIMVR
	constexpr REL::ID TESObjectBOOK_Read{ 17439 };
	constexpr REL::ID GetSkillName{ 26561 };
#else
	constexpr REL::Offset TESObjectBOOK_Read{ 0x0023B240 };
	constexpr REL::Offset GetSkillName{ 0x003F0AE0 };
#endif
}
