Scriptname RIG_InfoMenu extends SKI_ConfigBase

RIG_PlayerRefAliasScript Property PlayerAlias  Auto
GlobalVariable Property RIG_ShowNotification  Auto
GlobalVariable Property RIG_PlaySound  Auto

int[] BookListOptions

int Function GetVersion()
	return 1
EndFunction

Event OnInit()
	parent.OnInit()
	BookListOptions = new int[18]
EndEvent

Event OnConfigInit()
	Pages = new string[2]
	Pages[0] = "$Status"
	Pages[1] = "$Settings"
EndEvent

Event OnPageReset(string a_page)
	if a_page == ""
		LoadCustomContent("ReadingIsGood/RIG_splash.dds")
		return
	else
		UnloadCustomContent()
	endif

	if a_page == "$Status"
		SetCursorFillMode(LEFT_TO_RIGHT)

		AddHeaderOption("$Current Bonuses")
		AddEmptyOption()

		int iSkillIndex = 0
		while iSkillIndex < 18
			string sSkillName = RIG_SkillBookUtil.GetSkillName(iSkillIndex + 6)
			int iCount = BookCount(iSkillIndex)
			int iBonusPercent = (PlayerAlias.GetSkillBonus(iCount) * 100) as int
			int iFlag = GetFlag(iCount)
			BookListOptions[iSkillIndex] =\
				AddMenuOption(sSkillName, iBonusPercent + "%", iFlag)
			iSkillIndex += 1
		endwhile
	elseif a_page == "$Settings"
		SetCursorFillMode(TOP_TO_BOTTOM)

		AddHeaderOption("$Skill Book Settings")

		AddToggleOptionST(\
				"ShowNotification", \
				"$Show Notification", \
				RIG_ShowNotification.GetValueInt())

		int iSoundFlag = OPTION_FLAG_NONE
		if RIG_ShowNotification.GetValueInt() == 0
			iSoundFlag = OPTION_FLAG_DISABLED
		endif

		AddToggleOptionST(\
				"PlaySound", \
				"$Play Sound", \
				RIG_PlaySound.GetValueInt(), \
				a_flags = iSoundFlag)
	endif
EndEvent

Event OnOptionMenuOpen(int a_option)
	int iSkillIndex = 0
	while BookListOptions[iSkillIndex] != a_option && iSkillIndex < 18
		iSkillIndex += 1
	endwhile

	if iSkillIndex < 18
		SetMenuDialogOptions(\
				ToStringArray(PlayerAlias.RIG_ReadBookLists[iSkillIndex]))
	endif
EndEvent

int Function BookCount(int a_skillIndex)
	return PlayerAlias.RIG_ReadBookLists[a_skillIndex].GetSize()
EndFunction

int Function GetFlag(int a_count)
	if a_count > 0
		return OPTION_FLAG_NONE
	else
		return OPTION_FLAG_DISABLED
	endif
EndFunction

string[] Function ToStringArray(FormList list)
	int size = list.GetSize()
	string[] outArray = Utility.CreateStringArray(size)

	int index = 0
	while index < size
		outArray[index] = list.GetAt(index).GetName()
		index += 1
	endwhile

	return outArray
EndFunction

State ShowNotification
Function OnSelectST()
	bool bEnabled = RIG_ShowNotification.GetValueInt() as bool
	RIG_ShowNotification.SetValueInt((!bEnabled) as int)
	SetToggleOptionValueST(!bEnabled)
	GotoState("PlaySound")
	SetOptionFlagsST(OPTION_FLAG_DISABLED * (bEnabled as int))
EndFunction

Function OnDefaultST()
	RIG_ShowNotification.SetValueInt(1)
EndFunction
EndState

State PlaySound
Function OnSelectST()
	bool bEnabled = RIG_PlaySound.GetValueInt() as bool
	RIG_PlaySound.SetValueInt((!bEnabled) as int)
	SetToggleOptionValueST(!bEnabled)
EndFunction

Function OnDefaultST()
	RIG_PlaySound.SetValueInt(1)
EndFunction
EndState
