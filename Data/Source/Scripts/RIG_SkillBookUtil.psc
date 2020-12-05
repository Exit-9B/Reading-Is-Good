Scriptname RIG_SkillBookUtil Hidden

string Function GetSkillName(int aiActorValue) global native

Function Notification(\
		Message akFormat, \
		int aiActorValue, \
		string asSoundID = "") global native

bool Function AddReadSkillBooksToLists(FormList[] akBookLists) global native

; DEPRECATED
Function RegisterForOnSkillBookReadEvent(ReferenceAlias akAlias) global
	RIG_ReferenceAliasExt.RegisterForSkillBookReadEvent(akAlias)
EndFunction

; DEPRECATED
Function UnregisterForOnSkillBookReadEvent(ReferenceAlias akAlias) global
	RIG_ReferenceAliasExt.UnregisterForSkillBookReadEvent(akAlias)
EndFunction
