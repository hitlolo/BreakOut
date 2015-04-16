#include "GameLottery.h"

GameLottery*   GameLottery::_gameLottery = nullptr;

GameLottery*  GameLottery::getInstance()
{
	if (_gameLottery == nullptr)
	{
		_gameLottery = new GameLottery();
		return _gameLottery;
	}
	else
		return _gameLottery;
}

GameLottery::GameLottery()
{
	_mt = new std::mt19937(randomDevice());
}

GameLottery::~GameLottery()
{
	CC_SAFE_DELETE(_mt);
	CC_SAFE_DELETE(_gameLottery);
}

LOTTERY GameLottery::lottery()
{
	if (isBonus())
	{
		//true buff,false debuff
		int bonus = buffOrDebuffOrRandom();
		switch (bonus)
		{
		case 0:
			//0.furit 
			//1.add ball
			//2.speed down
			//3.bar up
			return getBuff();
			break;
		case 1:
			//1.speed up
			//2.bar down
			return getDeBuff();
			break;
		case 2:
			//1.question
			//2.excalmation
			//3.bad things
			return getRandom();
		default:
			break;
		}
		
		
	}
	else //no bonus
	{
		return LOTTERY::NONE;
	}
	
	
}


int GameLottery::getRandomByRange(int from, int to)
{
	//std::default_random_engine random_e;
	std::uniform_int_distribution<int> dist(from, to);
	return dist(*_mt);
}

float GameLottery::getRandomByRange(float from, float to)
{
	//std::default_random_engine random_e;
	std::uniform_real_distribution<float> dist(from, to);
	return dist(*_mt);
}


bool GameLottery::isBonus()
{
	// probability = 1/10
	int probability = this->getRandomByRange(0, 9);
	if (probability != 5)
		return true;
	else
		return false;
}

int GameLottery::buffOrDebuffOrRandom()
{
	int probability = this->getRandomByRange(0, 2);
	return probability;
}

LOTTERY GameLottery::getBuff()
{
	int probability = this->getRandomByRange(0, 1);
	if (probability == 0)
	{
		return LOTTERY::FRUIT;
	}
	else
	{
		int probability = this->getRandomByRange(0, 2);
		switch (probability)
		{
		case 0:
			return LOTTERY::BALL;
			break;
		case 1:
			return LOTTERY::BAR_UP;
			break;
		case 2:
			return LOTTERY::SPEED_DOWN;
			break;
		}
	}
}

LOTTERY GameLottery::getDeBuff()
{
	int probability = this->getRandomByRange(0, 1);
	if (probability == 0)
	{
		return LOTTERY::SPEED_UP;
	}
	else
		return LOTTERY::BAR_DOWN;
	
}

LOTTERY GameLottery::getRandom()
{
	int probability = this->getRandomByRange(0, 2);
	switch (probability)
	{
	case 0:
		return LOTTERY::QUESTION;
		break;
	case 1:
		return LOTTERY::EXCLAMATION;
		break;
	case 2:
		return LOTTERY::BAD;
		break;
	}
}