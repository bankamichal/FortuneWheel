#include "Word.h"

Word::Word()
{
	std::cout << "Set word: ";
	std::cin >> this->word;
	std::cin.get();
	this->correctLettersOfWord = new int[this->word.size()];
	this->n = this->word.size();
}

/*Word::Word(std::string word)
{
	setWord(word);
	this->correctLettersOfWord = new int[this->word.size()];
	setN(this->word.size());
}*/



Word::Word(const std::string& fileName)
{
	std::string word;
	std::ifstream read;
	read.open(fileName);
	if (read.is_open())
	{
			getline(read, word);
			if (word.size() == 0) std::cout << "Reading file error occured. (Word)" << std::endl;
			else setWord(word);
	}
	else std::cout << "Opening file error occured. (Word)" << std::endl;
	this->correctLettersOfWord = new int[this->word.size()];
	setN(this->word.size());
	for (int i = 0; i < getN(); i++)
	{
		if (!isalpha(this->word[i]))
		{
			this->correctLettersOfWord[i] = 1;
		}
	}
}

Word::~Word()
{
}

void Word::setWord(const std::string & word)
{
	this->word = word;
}

void Word::setCorrectLettersOfWord(int* lettersOfWord)
{
	this->correctLettersOfWord = lettersOfWord;
}

void Word::setN(const int & n)
{
	this->n = n;
}

std::string Word::getWord() const
{
	return this->word;
}

int* Word::getCorrectLettersOfWord() const
{
	return this->correctLettersOfWord;
}

int Word::getN() const
{
	return this->n;
}

void Word::setSingleCorrectLetterOfWord(const int & idxOfLetter, const int& newValue)
{
	int* lettersTmp = getCorrectLettersOfWord();
	lettersTmp[idxOfLetter] = newValue;
	setCorrectLettersOfWord(lettersTmp);
}

bool Word::checkLetter(const char& letter)
{
	std::string wordTmp = getWord();
	bool found = false;
	for (int i = 0; i < getN(); i++)
	{
		if (wordTmp[i] == letter)
		{
			found = true;
			setSingleCorrectLetterOfWord(i, 1);
		}
	}
	return found;
}

int Word::checkAmountOfKnownLetters()
{
	int amount = 0;
	int* correctLetters = getCorrectLettersOfWord();
	for (int i = 0; i < getN(); i++)
	{
		if (correctLetters[i] == 1) amount++;
	}
	return amount;
}

bool Word::checkWord() const
{
	std::string guessedWord;
	std::cout << "Now you can try to guess the word: ";
	getline(std::cin, guessedWord);

	for (int i = 0; i < guessedWord.size(); i++)
	{
		if (islower(guessedWord[i])) guessedWord[i] = toupper(guessedWord[i]);
	}

	if (getWord() == guessedWord)
	{
		std::cout << "\nCONGRATULATIONS! That's correct word - " << getWord() << std::endl;
		return true;
	}
	else
	{
		std::string wordTmp = getWord();
		std::cout << "That's not correct word..." << std::endl;
		std::cout << "\n";
		return false;
	}
}

void Word::showWord() const
{
	std::cout << "Word: ";
	for (int i = 0; i < getWord().size(); i++)
	{
		if (getCorrectLettersOfWord()[i] == 1) std::cout << getWord()[i];
		else std::cout << "_";
		std::cout << ' ';
	}
	std::cout << "\n\n";
}
