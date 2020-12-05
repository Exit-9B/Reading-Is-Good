Scriptname RIG_PlayerRefAliasScript extends ReferenceAlias

Import RIG_ReferenceAliasExt
Import RIG_SkillBookUtil

FormList[] Property RIG_ReadBookLists  Auto
Perk Property RIG_LearningPerk  Auto
Perk Property RIG_BlackBookPerk  Auto
GlobalVariable Property RIG_BonusPerBook  Auto
GlobalVariable Property RIG_MaxBooks  Auto
GlobalVariable Property RIG_ShowNotification  Auto
GlobalVariable Property RIG_PlaySound  Auto
Message Property RIG_InsightGainedMessage  Auto
string Property SoundID  Auto

Event OnInit()
	AddPerks()

	AddReadSkillBooksToLists(RIG_ReadBookLists)
	RefreshPerks()

	RegisterForSkillBookReadEvent(self)
EndEvent

Event OnPlayerLoadGame()
	RefreshPerks()
	RegisterForSkillBookReadEvent(self)
EndEvent

Event OnSkillBookRead(Book akSkillBook, int aiSkill, int aiIncrement)
	ReadSkillBook(akSkillBook, aiSkill)

	if RIG_ShowNotification.GetValueInt() as bool
		string sSound = ""
		if RIG_PlaySound.GetValueInt() as bool
			sSound = SoundID
		endif

		Notification(RIG_InsightGainedMessage, aiSkill, sSound)
	endif
EndEvent

Function AddPerks()
	Actor kPlayerRef = GetActorReference()
	kPlayerRef.AddPerk(RIG_LearningPerk)
	kPlayerRef.AddPerk(RIG_BlackBookPerk)
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
	RIG_LearningPerk.SetNthEntryValue(aiSkillIndex, 0, 1.0 + fLevelBonus)
	RIG_BlackBookPerk.SetNthEntryValue(aiSkillIndex, 0, 1.0 + 2.0 * fLevelBonus)
EndFunction

float Function GetSkillBonus(int aiReadCount)
{Compute the XP bonus from the number of books read.}
	float fMaxBooks = RIG_MaxBooks.GetValue()
	if (fMaxBooks >= 0 && aiReadCount >= fMaxBooks)
		return fMaxBooks * RIG_BonusPerBook.GetValue()
	endif

	return aiReadCount * RIG_BonusPerBook.GetValue()
EndFunction
