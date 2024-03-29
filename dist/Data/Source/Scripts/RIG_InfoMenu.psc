Scriptname RIG_InfoMenu extends SKI_ConfigBase

RIG_PlayerRefAliasScript Property PlayerAlias  Auto
GlobalVariable Property RIG_ShowNotification  Auto
GlobalVariable Property RIG_PlaySound  Auto

Perk Property DLC2BlackBookSkillBookPerk  Auto

string Property PluginName = "ReadingIsGood" AutoReadOnly

int[] BookListOptions

int Function GetVersion()
	return 1
EndFunction

Event OnConfigInit()
	BookListOptions = new int[18]

	Pages = new string[2]
	Pages[0] = "$Status"
	Pages[1] = "$Settings"

	LoadModSettings()
EndEvent

Event OnGameReload()
	parent.OnGameReload()

	LoadModSettings()
EndEvent

Event OnPageReset(string a_page)
	if a_page == ""
		LoadCustomContent("ReadingIsGood/RIG_splash.dds", 128, 173)
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
			float fBonus = PlayerAlias.GetSkillBonus(iCount)
			if PlayerAlias.GetActorRef().HasPerk(DLC2BlackBookSkillBookPerk)
				fBonus *= 2.0
			endif
			int iBonusPercent = ((fBonus * 100.0) + 0.5) as int
			int iFlag = GetFlag(iCount)
			BookListOptions[iSkillIndex] = AddMenuOption(sSkillName, iBonusPercent + "%", iFlag)
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
		SetMenuDialogOptions(ToStringArray(PlayerAlias.RIG_ReadBookLists[iSkillIndex]))
	endif
EndEvent

Function LoadModSettings()
	if (MCM.GetVersionCode() > 0)
		RIG_ShowNotification.SetValueInt(\
				MCM.GetModSettingBool(PluginName, "bShowNotification:Notification") as int)
		RIG_PlaySound.SetValueInt(\
				MCM.GetModSettingBool(PluginName, "bPlaySound:Notification") as int)
		PlayerAlias.RIG_BonusPerBook.SetValue(\
				MCM.GetModSettingFloat(PluginName, "fBonusPerBook:Bonus"))
		PlayerAlias.RIG_MaxBooks.SetValueInt(\
				MCM.GetModSettingInt(PluginName, "iMaxBooks:Bonus"))
	endif
EndFunction

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
	MCM.SetModSettingBool(PluginName, "bShowNotification:Notification", !bEnabled)
	SetToggleOptionValueST(!bEnabled)
	GotoState("PlaySound")
	SetOptionFlagsST(OPTION_FLAG_DISABLED * (bEnabled as int))
EndFunction

Function OnDefaultST()
	RIG_ShowNotification.SetValueInt(1)
	MCM.SetModSettingBool(PluginName, "bShowNotification:Notification", true)
	SetToggleOptionValueST(true)
EndFunction
EndState

State PlaySound
Function OnSelectST()
	bool bEnabled = RIG_PlaySound.GetValueInt() as bool
	MCM.SetModSettingBool(PluginName, "bPlaySound:Notification", !bEnabled)
	RIG_PlaySound.SetValueInt((!bEnabled) as int)
	SetToggleOptionValueST(!bEnabled)
EndFunction

Function OnDefaultST()
	RIG_PlaySound.SetValueInt(1)
	MCM.SetModSettingBool(PluginName, "bPlaySound:Notification", true)
	SetToggleOptionValueST(true)
EndFunction
EndState
