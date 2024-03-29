#pragma once

namespace Offset
{
#ifndef SKYRIMVR
	namespace TESObjectBOOK
	{
		// SkyrimSE 1.6.318.0: 0x2392A0
		inline constexpr REL::ID ProcessBook(17842);
	}

	// SkyrimSE 1.6.318.0: 0x3F9D70
	inline constexpr REL::ID GetSkillName(27192);
#else
	namespace TESObjectBOOK
	{
		inline constexpr REL::Offset ProcessBook{ 0x0023B240 };
	}

	inline constexpr REL::Offset GetSkillName{ 0x003F0AE0 };
#endif
}
