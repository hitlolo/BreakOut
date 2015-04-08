#include "HudLayer.h"


bool HudLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->initRootNodeFromCSB();

	return true;
}


void HudLayer::initRootNodeFromCSB()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->setAnchorPoint(Point(0.5, 0.5));
	auto node = CSLoader::createNode("HudNode.csb");
	//Point nextLocation = Point(getContentSize().width + visibleSize.width, visibleSize.height / 2);
	//this->setPosition(nextLocation);
	node->setPosition(Point(0, 50));
	this->addChild(node);
}