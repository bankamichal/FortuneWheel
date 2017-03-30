#include "FortuneWheel.h"
#include "Word.h"
#include "Player.h"

int main()
{
	srand((unsigned)time(NULL));
	FortuneWheel* wheel = FortuneWheel::getInstance();
	wheel->game();
	std::cin.get();
	return 0;
}