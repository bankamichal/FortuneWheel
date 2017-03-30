#pragma once
#include "Libs.h"
//#include "FortuneWheel.h" XD

class Player
{
private:
	bool finish;
	std::string name;
	std::string surname;
	int age;
	std::map<std::string, int> correctLettersAndFields;
	int numberOfBROKE;
	int numberOfSpecialTurn;
	int totalEarnedMoney;
	int numberOfVowels;
public:
	Player();
	Player(const std::string& name, const std::string& surname, const int& age, const std::map<std::string, int>& map,
		   const bool& finish, const int& numberOfBROKE);
	Player(const std::string& fileName);
	~Player();

	void setName(const std::string& name);
	void setSurame(const std::string& surname);
	void setAge(const int& age);
	void setCorrectLettersAndFields(const std::map<std::string, int>& map);
	void addToCorrectLettersAndFields(const std::string& key,const int& value);
	void setFinish(const bool& finish);
	void setNumberOfBROKE(const int& numberOfBROKE);
	void setNumberOfBROKE();
	void setTotalEarnedMoney(const int& totalEarnedMoney);
	void setNumberofSpecialTurn(const int& number);
	void setNumberofSpecialTurn();
	void setNumberOfVowels();
	void setNumberOfVowels(const int& vowels);

	std::string getName() const;
	std::string getSurame() const;
	int getAge() const;
	std::map<std::string, int> getCorrectLettersAndFields() const;
	bool getFinish() const;
	int getNumberOfBROKE() const;
	int getTotalEarnedMoney() const;
	int getNumberofSpecialTurn() const;
	int getNumberOfVowels() const;
	
	void clearCorrectLettersAndFields();
	void addToTotalEarnedMoney(const int& fieldToInt);
	void setTotalEarnedMoneyAtEndGame();
	void showMap() const;
	void checkIfVowel(const char& letter);
};

