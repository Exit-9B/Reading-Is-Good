#pragma once

class BookHandler
{
public:
	static BookHandler* GetSingleton();

	void Initialize();

	std::unordered_map<RE::TESObjectBOOK*, RE::ActorValue> SkillBooks;

private:
	BookHandler() = default;
	~BookHandler() = default;
	BookHandler(const BookHandler& other) = delete;
	BookHandler(BookHandler&& other) = delete;
	BookHandler& operator=(const BookHandler& other) = delete;
	BookHandler& operator=(BookHandler&& other) = delete;
};
