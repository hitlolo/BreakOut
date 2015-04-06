#include "BrickLayer.h"

BrickLayer* BrickLayer::create(int level, b2World* world)
{
	BrickLayer * ret = new (std::nothrow) BrickLayer(level, world);
	if (ret && ret->init(level, world))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}


BrickLayer::BrickLayer(int level, b2World* world)
	:m_curLevel(level)
	, m_brickCount(0)
	, m_world(world)
{

}

BrickLayer::~BrickLayer()
{

}

bool BrickLayer::init(int level, b2World* world)
{
	if (!Layer::init())
	{
		return false;
	}
	initLevelData(level);
	return true;
}

void BrickLayer::initLevelData(int level)
{
	//CCLOG("%s", getFileName().c_str());
	auto tmx_map = TMXTiledMap::create(getFileName());
	auto bricks = tmx_map->getObjectGroup("tiles");
	ValueVector objectsVector = bricks->getObjects();
	for (auto brickObject : objectsVector)
	{
		auto brick = GameBrick::create(m_world, brickObject);
		tmx_map->addChild(brick);
		m_bricksVector.push_back(brick);
		m_brickCount += 1;
	}
	this->addChild(tmx_map);
}



std::string BrickLayer::getFileName()
{
	String *file = String::createWithFormat("level%d.tmx", m_curLevel);
	return std::string(file->getCString());
}

std::vector<GameBrick*> BrickLayer::getBricks()
{
	return this->m_bricksVector; 
}





