#pragma once

namespace Offset
{
#ifndef VR
	constexpr REL::ID TESObjectBOOK_Read{ 17439 };
	constexpr REL::ID GetSkillName{ 26561 };
#else
	constexpr std::uintptr_t TESObjectBOOK_Read = 0x23B240;
	constexpr std::uintptr_t GetSkillName = 0x3F0AE0;
#endif
}
