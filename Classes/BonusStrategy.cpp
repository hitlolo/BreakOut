#include "BonusStrategy.h"

///fruit
FruitStrategy::FruitStrategy()
{

}

FruitStrategy::~FruitStrategy()
{

}

PhysicsSprite* FruitStrategy::createBonusSprite()
{
	int type = this->getRandomFruit();

}

int FruitStrategy::getRandomFruit()
{
	using namespace std;
	random_device randomDevice;
	mt19937      mt(randomDevice());
	uniform_int_distribution<float> dist(0, 3);
	return dist(mt);
}

///end of fruit 