#include "Patches.h"
#include "Offsets.h"
#include <xbyak/xbyak.h>

#ifndef SKYRIMVR
bool Patch::WriteSkillBookPatch(ReadSkillBookCallback* a_callback)
{
	std::uintptr_t hookAddr = Offset::TESObjectBOOK::ProcessBook.address() + 0xB4;

	struct Patch : Xbyak::CodeGenerator
	{
		Patch(std::uintptr_t a_funcAddr)
		{
			movss(xmm1, dword[rsp + 0x88]);
			mov(rcx, rdi);
			mov(rax, a_funcAddr);
			call(rax);
		}
	};
	Patch patch{ reinterpret_cast<std::uintptr_t>(a_callback) };
	patch.ready();

	if (patch.getSize() > 0x19) {
		logger::critical("Patch was too large, failed to install"sv);
		return false;
	}
	assert(patch.getSize() <= 0x19);

	REL::safe_fill(hookAddr, REL::NOP, 0x19);
	REL::safe_write(hookAddr, patch.getCode(), patch.getSize());

	logger::info("Installed hook for reading skill book"sv);
	return true;
}

#else

bool Patch::WriteSkillBookPatch(ReadSkillBookCallback* a_callback)
{
	std::uintptr_t hookAddr = Offset::TESObjectBOOK::ProcessBook.address() + 0xA3;

	struct Patch : Xbyak::CodeGenerator
	{
		Patch(std::uintptr_t a_funcAddr)
		{
			movss(xmm1, dword[rsp + 0x78]);
			mov(rcx, rdi);
			mov(rax, a_funcAddr);
			call(rax);
		}
	};
	Patch patch{ reinterpret_cast<std::uintptr_t>(a_callback) };
	patch.ready();

	if (patch.getSize() > 0x15) {
		logger::critical("Patch was too large, failed to install"sv);
		return false;
	}
	assert(patch.getSize() <= 0x15);

	REL::safe_fill(hookAddr, REL::NOP, 0x15);
	REL::safe_write(hookAddr, patch.getCode(), patch.getSize());

	logger::info("Installed hook for reading skill book"sv);
	return true;
}
#endif
