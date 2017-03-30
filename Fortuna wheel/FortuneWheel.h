#pragma once
#include "Libs.h"
#include "Player.h"
#include "Word.h"

class FortuneWheel
{
public:
	enum fields
	{
		BROKE,
		SPECIAL_TURN,
		value1 = 100,
		value2 = 200,
		value3 = 300,
	};
private:
	FortuneWheel();
	static FortuneWheel* instance;
	static std::list<fields> board;
public:
	static FortuneWheel* getInstance();

	~FortuneWheel();

	void setBoard(std::list<fields> board);
	std::list<fields> getBoard() const;
	FortuneWheel::fields lottery(const Player& character) const;
	void showBoard() const;
	std::string showField(FortuneWheel::fields singleField) const;
	bool gamePlayerInner(Player& currentPlayer, Word w, FortuneWheel::fields randomField) const;
	bool gamePlayer(Player& currentPlayer, Word w) const;
	void game() const;
	void statistics(const int& howManyPlayers,Player* players) const;
};

