#include "FortuneWheel.h"

std::list<FortuneWheel::fields> FortuneWheel::board;

FortuneWheel* FortuneWheel::instance = NULL;

FortuneWheel::FortuneWheel()
{
	int random = 0;
	int specialTurnField = 0;
	int brokeField1 = 0;
	int brokeField2 = 0;
	int numberOfFields = 0;
	do
	{
		std::cout << "Set number of fields (8-14): ";
		std::cin >> numberOfFields;
		std::cin.get();
	} while (numberOfFields < 8 || numberOfFields > 14);


	specialTurnField = rand() % (numberOfFields);

	do
	{
		brokeField1 = rand() % (numberOfFields);
		brokeField2 = rand() % (numberOfFields);
	} while ((abs(brokeField2 - brokeField1) < 4) || brokeField1 == specialTurnField || brokeField2 == specialTurnField || (abs(brokeField2 - brokeField1) > numberOfFields - 3));

	for (int i = 0; i < numberOfFields; i++)
	{
		random = rand() % 3;
		switch (random)
		{
		case 0:
			board.push_back(value1);
			break;
		case 1:
			board.push_back(value2);
			break;
		case 2:
			board.push_back(value3);
			break;
		}
	}
	std::list<FortuneWheel::fields>::iterator itBoard = board.begin();
	int i = 0;
	while (itBoard != board.end())
	{
		if (i == brokeField1 || i == brokeField2) *itBoard = BROKE;
		if (i == specialTurnField) *itBoard = SPECIAL_TURN;
		i++;
		itBoard++;
	}
}

FortuneWheel * FortuneWheel::getInstance()
{
	if (!instance) {
		instance = new FortuneWheel();
	};
	return instance;
}

FortuneWheel::~FortuneWheel()
{
}

void FortuneWheel::setBoard(std::list<fields> board)
{
	this->board = board;
}

std::list<FortuneWheel::fields> FortuneWheel::getBoard() const
{
	return this->board;
}

FortuneWheel::fields FortuneWheel::lottery(const Player& character) const
{
	int number = -1;
	if (character.getAge() <= 24 && character.getAge() >= 18)
	{
		do
		{
			number = std::rand() % 16;
		} while (number % 2 == 1);
	}
	else if (character.getAge() <= 30 && character.getAge() > 24)
	{
		number = 1 + std::rand() % 29;
		if (number == 2 || number == 1) number = 1;
		else if (number % 2 == 1) number = 15;
		else
		{
			int fib1 = 1;
			int fib2 = 1;
			int tmp = 0;
			for (int i = 2; i < number; i++)
			{
				tmp = fib1;
				fib1 += fib2;
				fib2 = tmp;
			}
			number = fib1 % 10;
		}
	}
	else number = std::rand() % 16;

	std::list<FortuneWheel::fields> boardTmp = getBoard();
	std::list<FortuneWheel::fields>::iterator boardIt = boardTmp.begin();
	int i = 0;
	while (boardIt != boardTmp.end())
	{
		if (i == (number % boardTmp.size())) return *boardIt;
		boardIt++;
		i++;
	}
}

void FortuneWheel::showBoard() const 
{
	std::cout << "YOUR BOARD:" << std::endl;
	int i = 0;
	std::list<fields>::iterator itBoard = board.begin();
	while (itBoard != board.end())
	{
		std::cout << i + 1 << ". ";
		if (*itBoard == value1) std::cout << "100" << std::endl;
		if (*itBoard == value2) std::cout << "200" << std::endl;
		if (*itBoard == value3) std::cout << "300" << std::endl;
		if (*itBoard == BROKE) std::cout << "BROKE" << std::endl;
		if (*itBoard == SPECIAL_TURN) std::cout << "SPECIAL_TURN" << std::endl;
		itBoard++;
		i++;
	}
}

std::string FortuneWheel::showField(FortuneWheel::fields singleField) const
{
	if (singleField == value1) return "100";
	if (singleField == value2) return "200";
	if (singleField == value3) return "300";
	if (singleField == BROKE) return "BROKE";
	if (singleField == SPECIAL_TURN) return "SPECIAL TURN";
}

bool FortuneWheel::gamePlayerInner(Player& currentPlayer, Word w, FortuneWheel::fields randomField) const
{
	int newLetters = 0;
	char charNewLetters = ' ';
	std::string letter = "";
	std::string guessedWord = "";

	do
	{
		std::cout << "Try to guess letter from the word: ";
		std::cin >> letter;
		std::cin.get();
	} while (letter.size() != 1);

	currentPlayer.checkIfVowel(letter[0]);
	letter = toupper(letter[0]);
	newLetters = w.checkAmountOfKnownLetters();
	w.checkLetter(letter[0]);
	newLetters = w.checkAmountOfKnownLetters() - newLetters;
	charNewLetters = '0' + newLetters;
	if (newLetters > 1)
	{
		std::cout << "Word has " << newLetters << " like your." << std::endl;
		w.showWord();
		letter += charNewLetters;
		currentPlayer.addToCorrectLettersAndFields(letter, (int)randomField);
		if (w.checkWord())
		{
			currentPlayer.setFinish(true);
			return true;
		}
	}
	else if (newLetters == 1)
	{
		std::cout << "Word has one letter like your." << std::endl;
		w.showWord();
		currentPlayer.addToCorrectLettersAndFields(letter, (int)randomField);
		if (w.checkWord())
		{
			currentPlayer.setFinish(true);
			return true;
		}
	}
	else std::cout << "Word doesn't have this letter." << std::endl;
	return false;
}

bool FortuneWheel::gamePlayer(Player& currentPlayer,Word w) const
{
	FortuneWheel::fields randomField;
	std::cout << currentPlayer.getName() << " " << currentPlayer.getSurame() << " is spinning the wheel." << std::endl;
	randomField = lottery(currentPlayer);
	bool won = false;

	if (randomField == FortuneWheel::SPECIAL_TURN) // only SPECIAL_TURN
	{
		currentPlayer.setNumberofSpecialTurn();
		do
		{
			std::cout << "Your random field is " << showField(randomField) << "\nIt means that you will have one more spin.\n\n";
			if (gamePlayerInner(currentPlayer, w, randomField)) return true;
			randomField = lottery(currentPlayer);
		} while (randomField == FortuneWheel::SPECIAL_TURN);
		std::cout << "Your random field is " << showField(randomField) << "\n\n";
		if (randomField == FortuneWheel::BROKE) return false;
		if (gamePlayerInner(currentPlayer, w, randomField)) return true;
	}
	else if (randomField != FortuneWheel::BROKE) //must be 100, 200 or 300
	{
		std::cout << "Your random field is " << showField(randomField) << "\n\n";
		if (gamePlayerInner(currentPlayer, w, randomField)) return true;
	}
	else //must be BROKE
	{
		currentPlayer.setNumberOfBROKE();
		std::cout << "Oh, it's 'BROKE'... " << currentPlayer.getNumberOfBROKE() << ". time...\n\n";
		if (currentPlayer.getNumberOfBROKE() >= 3) currentPlayer.setFinish(true);
	}
	std::cout << std::endl;
	return false;
}



void FortuneWheel::game() const
{
	showBoard();
	const int howManyPlayers = 3;
	Player p1("PlayerInfo1.txt");
	Player p2("PlayerInfo2.txt");
	Player p3("PlayerInfo3.txt");
	Player allPlayers[howManyPlayers] = { p1,p2,p3 };
	Word w("Word.txt");
	bool quit = false;
	int leftPlayers = howManyPlayers;
	int currentIdxOfPlayer = 0;

	do
	{
		for (int i = 0; i < howManyPlayers; i++)
		{
			currentIdxOfPlayer = i;
			if (allPlayers[i].getFinish() == false)
			{
				std::cout << "\n====================================================" << std::endl;
				w.showWord();
				quit = gamePlayer(allPlayers[i], w);
				leftPlayers = 0;
			}
			else
			{
				leftPlayers++;
			}
			if (quit) break;
		}
		if (leftPlayers >= howManyPlayers) quit = true;
	} while (!quit);

	if (leftPlayers != howManyPlayers) std::cout << "Game over, " << allPlayers[currentIdxOfPlayer].getName() << " " << allPlayers[currentIdxOfPlayer].getSurame() << " won!\n\n";
	else std::cout << "Everbody has to much BROKE fields... game over, nobody wins." << std::endl;
	statistics(howManyPlayers, allPlayers);
}

void FortuneWheel::statistics(const int& howManyPlayers, Player* players) const 
{
	int choice = 0;
	std::map<std::string, int> map;
	std::cout << "1. Statistics\n2. Quit\n";
	do
	{
		std::cout << "Your choice: ";
		std::cin >> choice;
		std::cin.get();
	} while (choice < 1 || choice > 2);

	if (choice == 1)
	{
		int brokeCounter = 0;
		int value1Counter = 0;
		int value2Counter = 0;
		int value3Counter = 0;
		int specialCounter = 0;
		Player mostEarend = players[0];
		int* specialCounter2 = new int [howManyPlayers];
		for (int i = 0; i < howManyPlayers; i++) specialCounter2[i] = 0;
		std::map<std::string, int>::iterator it = players[0].getCorrectLettersAndFields().begin();
	
		for (int i = 0; i < howManyPlayers; i++)
		{
			map = players[i].getCorrectLettersAndFields();
			//counters
			brokeCounter += players[i].getNumberOfBROKE();
			it = map.begin();
			while (it != map.end())
			{
				if (it->second == (int)FortuneWheel::value1) value1Counter++;
				if (it->second == (int)FortuneWheel::value2) value2Counter++;
				if (it->second == (int)FortuneWheel::value3) value3Counter++;
				if (it->second == (int)FortuneWheel::SPECIAL_TURN)
				{
					specialCounter2[i]++;
					specialCounter++;
				}
				++it;
			}
			//most earnings player
			players[i].setTotalEarnedMoneyAtEndGame();
			if (players[i].getTotalEarnedMoney() > mostEarend.getTotalEarnedMoney()) mostEarend = players[i];
		//Players sorted by number of SPECIAL_TURN
		}
		for (int i = 0; i < howManyPlayers; i++)
		{
			for (int j = 1; j < howManyPlayers; j++)
			{
				if (players[j].getNumberofSpecialTurn() > players[j-1].getNumberofSpecialTurn())
				{
					std::swap(players[j], players[j - 1]);
				}
			}
		}
		//most vowels
		int idxOfMostVowels = 0;
		for (int i = 1; i < howManyPlayers; i++)
		{
			if (players[idxOfMostVowels].getNumberOfVowels() < players[i].getNumberOfVowels()) idxOfMostVowels = i;
		}
		std::cout << "\n====STATISTICS====" << std::endl;
		std::cout << "'BROKE' counter = " << brokeCounter << std::endl;
		std::cout << "'100' counter = " << value1Counter << std::endl;
		std::cout << "'200' counter = " << value2Counter << std::endl;
		std::cout << "'300' counter = " << value3Counter << std::endl;
		std::cout << "'SPECIAL_TURN' counter = " << specialCounter << std::endl << std::endl;
		std::cout << "Player with the biggest reward is " << mostEarend.getName() << ' ' << mostEarend.getSurame() << " with " << mostEarend.getTotalEarnedMoney() << "$\n\n";
		std::cout << "\nPlayer who gave the most vowels is " << players[idxOfMostVowels].getName() << " " << players[idxOfMostVowels].getSurame() << " - " << players[idxOfMostVowels].getNumberOfVowels() << std::endl;
		std::cout << "\nPlayers sorted by number of SPECIAL_TURN: "<< std::endl;
		for (int i = 0; i < howManyPlayers; i++)
		{
			std::cout << i+1 << ") " << players[i].getName() << " " << players[i].getSurame() << " - " << players[i].getNumberofSpecialTurn() << std::endl;
		}
	}
}

