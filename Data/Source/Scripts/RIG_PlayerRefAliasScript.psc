Scriptname RIG_PlayerRefAliasScript extends ReferenceAlias

FormList[] Property RIG_ReadBookLists  Auto
Perk[] Property RIG_Perks  Auto
GlobalVariable Property RIG_BonusPerBook  Auto
GlobalVariable Property RIG_HardCap  Auto

Event OnInit()
	AddPerks()

	RIG_SkillBookUtil.AddReadSkillBooksToLists(RIG_ReadBookLists)
	RefreshPerks()

	RIG_SkillBookUtil.RegisterForOnSkillBookReadEvent(self)
EndEvent

Event OnPlayerLoadGame()
	RefreshPerks()
	RIG_SkillBookUtil.RegisterForOnSkillBookReadEvent(self)
EndEvent

Event OnSkillBookRead(Book akSkillBook, int aiSkill)
	ReadSkillBook(akSkillBook, aiSkill)
EndEvent

Function AddPerks()
	Actor kPlayerRef = GetActorReference()
	int iIndex = 0
	while iIndex < RIG_Perks.Length
		kPlayerRef.AddPerk(RIG_Perks[iIndex])
		iIndex += 1
	endwhile
EndFunction

Function ReadSkillBook(Book akSkillBook, int aiSkill)
	int iSkillIndex = aiSkill - 6
	if iSkillIndex < 0 || iSkillIndex > 17
		return
	endif

	FormList kReadBookList = RIG_ReadBookLists[iSkillIndex]

	if !kReadBookList.HasForm(akSkillBook)
		kReadBookList.AddForm(akSkillBook)
		RefreshPerk(iSkillIndex)
	endif
EndFunction

Function RefreshPerks()
{Set all perks to their appropriate values.}
	int iSkillIndex = 0
	while iSkillIndex < 18
		RefreshPerk(iSkillIndex)
		iSkillIndex += 1
	endwhile
EndFunction

Function RefreshPerk(int aiSkillIndex)
{Set perks for one skill to their appropriate values.}
	FormList kReadBookList = RIG_ReadBookLists[aiSkillIndex]

	int iReadCount = kReadBookList.GetSize()
	float fLevelBonus = GetSkillBonus(iReadCount)
	RIG_Perks[aiSkillIndex].SetNthEntryValue(0, 0, 1.0 + fLevelBonus)
	RIG_Perks[aiSkillIndex].SetNthEntryValue(1, 0, 1.0 + 2.0 * fLevelBonus)
EndFunction

float Function GetSkillBonus(int aiReadCount)
{Compute the XP bonus from the number of books read.}
	float fHardCap = RIG_HardCap.GetValue()
	if (fHardCap >= 0 && aiReadCount >= fHardCap)
		return fHardCap * RIG_BonusPerBook.GetValue()
	endif

	return aiReadCount * RIG_BonusPerBook.GetValue()
EndFunction
