#include "Player.h"

Player::Player()
{
}

Player::Player(const std::string & name, const std::string & surname, const int & age, const std::map<std::string, int>& map, const bool & finish, const int & numberOfBROKE)
{
	setName(name);
	setSurame(surname);
	setAge(age);
	setCorrectLettersAndFields(map);
	setNumberOfBROKE(numberOfBROKE);
}

Player::Player(const std::string & fileName)
{
	std::string line = "";
	int ageTmp = 0;
	std::map<std::string, int> clearMap;
	clearMap.clear();
	std::ifstream getInfo;
	getInfo.open(fileName);
	if (getInfo.is_open())
	{
		setTotalEarnedMoney(0);
		setFinish(false);
		setNumberOfBROKE(0);
		setCorrectLettersAndFields(clearMap);
		setNumberofSpecialTurn(0);
		setNumberOfVowels(0);
		while (!getInfo.eof())
		{
			getInfo >> line;
			setName(line);
			getInfo >> line;
			setSurame(line);
			getInfo >> ageTmp;
			setAge(ageTmp);
		}
	}
}

Player::~Player()
{
}

void Player::setName(const std::string & name)
{
	this->name = name;
}

void Player::setSurame(const std::string & surname)
{
	this->surname = surname;
}

void Player::setAge(const int & age)
{
	this->age = age;
}

void Player::setCorrectLettersAndFields(const std::map<std::string, int>& map)
{
	this->correctLettersAndFields = map;
}

void Player::addToCorrectLettersAndFields(const std::string & key, const int & value)
{
	std::map<std::string, int> tmp = getCorrectLettersAndFields();
	tmp[key] = value;
	setCorrectLettersAndFields(tmp);
}

void Player::setFinish(const bool & finish)
{
	this->finish = finish;
}

void Player::setNumberOfBROKE(const int & numberOfBROKE)
{
	this->numberOfBROKE = numberOfBROKE;
}

void Player::setNumberOfBROKE()
{
	setNumberOfBROKE(getNumberOfBROKE() + 1);
}

void Player::setTotalEarnedMoney(const int & totalEarnedMoney)
{
	this->totalEarnedMoney = totalEarnedMoney;
}

void Player::setNumberofSpecialTurn(const int & number)
{
	this->numberOfSpecialTurn = number;
}

void Player::setNumberofSpecialTurn()
{
	setNumberofSpecialTurn(getNumberofSpecialTurn() + 1);
}

void Player::setNumberOfVowels()
{
	setNumberOfVowels(getNumberOfVowels() + 1);
}

void Player::setNumberOfVowels(const int & vowels)
{
	this->numberOfVowels = vowels;
}

std::string Player::getName() const
{
	return this->name;
}

std::string Player::getSurame() const
{
	return this->surname;
}

int Player::getAge() const
{
	return this->age;
}

std::map<std::string, int> Player::getCorrectLettersAndFields() const
{
	return this->correctLettersAndFields;
}

bool Player::getFinish() const
{
	return this->finish;
}

int Player::getNumberOfBROKE() const
{
	return this->numberOfBROKE;
}

int Player::getTotalEarnedMoney() const
{
	return this->totalEarnedMoney;
}

int Player::getNumberofSpecialTurn() const
{
	return this->numberOfSpecialTurn;
}

int Player::getNumberOfVowels() const
{
	return this->numberOfVowels;
}

void Player::clearCorrectLettersAndFields()
{
	std::map<std::string, int> map;
	map.clear();
	setCorrectLettersAndFields(map);
	setTotalEarnedMoney(0);
}

void Player::addToTotalEarnedMoney(const int & fieldToInt)
{
	int total = getTotalEarnedMoney();
	total += fieldToInt;
	setTotalEarnedMoney(total);
}

void Player::setTotalEarnedMoneyAtEndGame()
{
	int total = 0;
	std::map<std::string, int> map = getCorrectLettersAndFields();
	std::map<std::string, int>::iterator it = map.begin();
	while (it != map.end())
	{
		if (it->second != 1 && it->second != 0)
		{
			if (it->first.size() == 1) total += it->second;
			else if (it->first.size() == 2) total += (it->first[1] - '0') * it->second;
			else std::cout << "Adding total earning error - Map key too long. " << std::endl;
		}
		++it;
	}
	setTotalEarnedMoney(total);
}

void Player::showMap() const
{
	std::map<std::string, int> map = getCorrectLettersAndFields();
	std::map<std::string, int>::iterator it = map.begin();
	while (it != map.end())
	{
		std::cout << "key = " << it->first << ", value = " << it->second << std::endl;
		++it;
	}
}

void Player::checkIfVowel(const char& letter)
{
	char l = toupper(letter);
	if (l == 'A' || l == 'E' || l == 'U' || l == 'O' || l == 'I' || l == 'Y')
		setNumberOfVowels();
}
