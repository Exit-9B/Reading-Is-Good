#pragma once

namespace Patch
{
	using ReadSkillBookCallback = void(RE::TESObjectBOOK*, float);

	bool WriteSkillBookPatch(ReadSkillBookCallback* a_callback);
}
