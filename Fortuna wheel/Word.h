#pragma once
#include "Libs.h"
class Word
{
private:
	std::string word;
	int* correctLettersOfWord;
	int n;
public:
	Word();
	//Word(std::string word);
	Word(const std::string& fileName);
	~Word();

	void setWord(const std::string& word);
	void setCorrectLettersOfWord(int* lettersOfWord);
	void setN(const int& n);
	std::string getWord() const;
	int* getCorrectLettersOfWord() const;
	int getN() const;

	void setSingleCorrectLetterOfWord(const int& idxOfLetter, const int& newValue);
	bool checkLetter(const char& letter);
	int checkAmountOfKnownLetters();
	bool checkWord() const;
	void showWord() const;
};
