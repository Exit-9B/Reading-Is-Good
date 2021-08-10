#include "SkillBookManager.h"
#include "Offsets.h"
#include "Registration.h"
#include <xbyak/xbyak.h>

void SkillBookManager::InstallHooks()
{
	REL::Relocation<std::uintptr_t> hook{ Offset::TESObjectBOOK_Read.address() + 0xA3 };

	struct Nop21 : Xbyak::CodeGenerator
	{
		Nop21() { nop(0x15, false); }
	};
	Nop21 nop21;
	nop21.ready();

	struct Patch : Xbyak::CodeGenerator
	{
		Patch(std::uintptr_t a_funcAddr)
		{
			movss(xmm1, dword[rsp + 0x78]);  // A3+6
			mov(rcx, rdi);                   // A9+3
			mov(rax, a_funcAddr);            // AC+A
			call(rax);                       // B6+2
		}
	};
	Patch patch{ reinterpret_cast<std::uintptr_t>(ReadSkillBook) };
	patch.ready();

	assert(nop21.getSize() == 0x15);
	assert(patch.getSize() <= 0x15);

	REL::safe_write(hook.address(), nop21.getCode(), nop21.getSize());
	REL::safe_write(hook.address(), patch.getCode(), patch.getSize());

	logger::info("Installed hooks for {}", typeid(SkillBookManager).name());
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
