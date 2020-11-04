Scriptname RIG_SkillBookUtil Hidden

Function RegisterForOnSkillBookReadEvent(ReferenceAlias akAlias) global native

Function UnregisterForOnSkillBookReadEvent(ReferenceAlias akAlias) global native

string Function GetSkillName(int aiActorValue) global native

Function Notification(\
		Message akFormat, int aiActorValue, string asSoundID = "") global native

bool Function AddReadSkillBooksToLists(FormList[] akBookLists) global native
