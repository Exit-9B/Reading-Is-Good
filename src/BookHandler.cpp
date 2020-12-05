#include "BookHandler.h"

BookHandler& BookHandler::GetSingleton()
{
	static BookHandler instance;
	return instance;
}

void BookHandler::Initialize()
{
	SkillBooks.clear();

	auto dataHandler = RE::TESDataHandler::GetSingleton();
	auto books = dataHandler->GetFormArray<RE::TESObjectBOOK>();

	for (auto book : books)
	{
		if (book->TeachesSkill())
		{
			SkillBooks[book] = book->GetSkill();
		}
	}
}