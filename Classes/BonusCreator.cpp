#include "BonusCreator.h"

BonusCreator*  BonusCreator::_bonusCreator = nullptr;


BonusCreator* BonusCreator::getInstance()
{
	if (_bonusCreator == nullptr)
	{
		_bonusCreator = new BonusCreator();
		return  _bonusCreator;
	}
	else
		return  _bonusCreator;
}

BonusCreator::BonusCreator()
{

}

BonusCreator::~BonusCreator()
{
	CC_SAFE_DELETE(_bonusCreator);
}

PhysicsSprite* BonusCreator::createBonus(Lottery type, b2World* world, Point position)
{
	PhysicsSprite* sprite = nullptr;
	switch (type)
	{
	case LOTTERY::NONE:
		return nullptr;
		break;
	case LOTTERY::FRUIT:
		{
			FruitStrategy strategy;
			sprite = strategy.createBonusSprite(world);
			sprite->setPosition(position);
			break;
		}	
	case LOTTERY::BALL:
		{
			BallBonusStrategy strategy;
			sprite = strategy.createBonusSprite(world);
			sprite->setPosition(position);
			break;
		}	
	case LOTTERY::SPEED_UP:
		{
			SpeedUpStrategy strategy;
			sprite = strategy.createBonusSprite(world);
			sprite->setPosition(position);
			break;
		}
	case LOTTERY::SPEED_DOWN:
		{
			SpeedDownStrategy strategy;
			sprite = strategy.createBonusSprite(world);
			sprite->setPosition(position);
			break;
		}
		
	case LOTTERY::BAR_UP:
		{
			BarUpStrategy strategy;
			sprite = strategy.createBonusSprite(world);
			sprite->setPosition(position);
			break;
		}
		
	case LOTTERY::BAR_DOWN:
		{
			BarDownStrategy strategy;
			sprite = strategy.createBonusSprite(world);
			sprite->setPosition(position);
			break;
		}
		
	case LOTTERY::QUESTION:
		{
			QuestionMarkStrategy strategy;
			sprite = strategy.createBonusSprite(world);
			sprite->setPosition(position);
			break;
		}
		
	case LOTTERY::EXCLAMATION:
		{
			ExcalmationMarkStrategy strategy;
			sprite = strategy.createBonusSprite(world);
			sprite->setPosition(position);
			break;
		}
		
	case LOTTERY::BAD:
		{
			BadThingStrategy strategy;
			sprite = strategy.createBonusSprite(world);
			sprite->setPosition(position);

			break;
		}	
	default:
		return nullptr;
		break;
	}


	return sprite;
}