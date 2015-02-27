#include "PreviewLayer.h"


PreviewLayer* PreviewLayer::create(int level)
{
	PreviewLayer * ret = new (std::nothrow) PreviewLayer(level);
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool PreviewLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
//	setTouchEnabled(true);
	setAnchorPoint(Point(0, 0));
	addBackground();
	setTouchListeners();
	initFromTMXFile(tmxFileName);
	return true;

}

PreviewLayer::PreviewLayer(int level)
	:brickLayer(nullptr)
{
	String *file = String::createWithFormat("level%d.tmx", level);
	tmxFileName = file->getCString();
	CCLOG("%s", tmxFileName.c_str());

}

PreviewLayer::~PreviewLayer()
{

}

void PreviewLayer::onEnter()
{
	Layer::onEnter();
	this->setScale(0.5);
	
	runAction(FadeIn::create(0.3f));
}

void PreviewLayer::addBackground()
{
	
	auto background = Scale9Sprite::createWithSpriteFrameName("res/panel.png");
	background->setInsetTop(30);
	background->setInsetBottom(30);
	background->setInsetRight(30);
	background->setInsetLeft(30);
	background->setContentSize(Size(576, 1024));
	background->setPosition(CENTER);
	this->addChild(background);
	this->setColor(Color3B(0, 0, 0));
}

void  PreviewLayer::setTouchListeners()
{
	auto eventListener = EventListenerTouchOneByOne::create();
	//eventListener->setSwallowTouches(true);
	eventListener->onTouchBegan = CC_CALLBACK_2(PreviewLayer::onTouchBegan, this);
	eventListener->onTouchCancelled = CC_CALLBACK_2(PreviewLayer::onTouchCancelled, this);
	eventListener->onTouchEnded = CC_CALLBACK_2(PreviewLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}

//touch
bool  PreviewLayer::onTouchBegan(Touch* touch, Event* event)
{
	
	return true;
}
void  PreviewLayer::onTouchEnded(Touch* touch, Event* event)
{

	if (isTouchOnPanel(touch))
	{
		GameController::getInstance()->goState(GAME_STATE::GAME);
	}
}

void  PreviewLayer::onTouchCancelled(Touch* touch, Event* event)
{

}

bool  PreviewLayer::isTouchOnPanel(Touch* touch)
{
	Point position = touch->getLocationInView();
	position = Director::getInstance()->convertToGL(position);
	Rect panelRect = getParent()->getBoundingBox();

	return panelRect.containsPoint(position);

}


void PreviewLayer::initFromTMXFile(std::string &file)
{
	brickLayer = TMXTiledMap::create(file);
//brickLayer->setAnchorPoint(Point(0.5, 0.5));
//	brickLayer->setPosition(CENTER);
//	this->addChild(brickLayer);
	auto bricks = brickLayer->getObjectGroup("tiles");
	CCLOG("%f,%f,brickLayer->getPosition()", brickLayer->getPosition().x, brickLayer->getPosition().y);
	//CCLOG("%f,%f", this->getPosition().x, this->getPosition().y);
	//CCLOG("%f,%f", background->getAnchorPoint().x, background->getAnchorPoint().y);
	CCLOG("%f,%f,brickLayer->getAnchorPoint()", brickLayer->getAnchorPoint().x, brickLayer->getAnchorPoint().y);
	ValueVector objectsVector = bricks->getObjects();

	for (auto brickObject : objectsVector)
	{
		this->addChild(createBrickWithDef(brickObject));	
	}
	CCLOG("%f,%f,this->getPosition()", this->getPosition().x, this->getPosition().y);
	CCLOG("%f,%f,this->getAnchorPoint()", this->getAnchorPoint().x, this->getAnchorPoint().y);
	this->addChild(brickLayer);
//	brickLayer->setPosition(Point(-144, -256));
	CCLOG("%f,%f,brickLayer->getPosition()", brickLayer->getPosition().x, brickLayer->getPosition().y);
	//CCLOG("%f,%f", this->getPosition().x, this->getPosition().y);
	//CCLOG("%f,%f", background->getAnchorPoint().x, background->getAnchorPoint().y);
	CCLOG("%f,%f,brickLayer->getAnchorPoint()", brickLayer->getAnchorPoint().x, brickLayer->getAnchorPoint().y);
}

Sprite* PreviewLayer::createBrickWithDef(Value &def)
{
	auto brickDef = def.asValueMap();
	float positionX = brickDef["x"].asInt();
	float positionY = brickDef["y"].asInt();
	float rotation = brickDef["rotation"].asFloat();
	std::string filename = getBrickColor(def);
	CCLOG("%s", filename.c_str());
	auto brick = Sprite::createWithSpriteFrameName(filename.c_str());
	brick->setAnchorPoint(Point(0, 0));
	brick->setPosition(Point(positionX, positionY));
	brick->setRotation(rotation);
	return brick;

}

std::string PreviewLayer::getBrickColor(Value &def)
{
	auto brickDef = def.asValueMap();
	bool type = brickDef["type"].asBool();
	if (type)
	{
		return getLongBrickColor(def);
	}
	else
	{
		return getShortBrickColor(def);
	}
}

std::string PreviewLayer::getLongBrickColor(Value &def)
{
	auto brickDef = def.asValueMap();
	auto color = brickDef["color"].asString(); 
	if (color == "white")
		return std::string("element_grey_rectangle_glossy.png");
	else if (color == "blue")
		return std::string("element_blue_rectangle_glossy.png");
	else if (color == "yellow")
		return std::string("element_yellow_rectangle_glossy.png");
	else if (color == "red")
		return std::string("element_red_rectangle_glossy.png");
	else if (color == "purple")
		return std::string("element_purple_rectangle_glossy.png");
	else if (color == "green")
		return std::string("element_green_rectangle_glossy.png");
}

std::string PreviewLayer::getShortBrickColor(Value &def)
{
	auto brickDef = def.asValueMap();
	auto color = brickDef["color"].asString();
	if (color == "white")
		return std::string("element_grey_square_glossy.png");
	else if (color == "blue")
		return std::string("element_blue_square_glossy.png");
	else if (color == "yellow")
		return std::string("element_yellow_square_glossy.png");
	else if (color == "red")
		return std::string("element_red_square_glossy.png");
	else if (color == "purple")
		return std::string("element_purple_square_glossy.png");
	else if (color == "green")
		return std::string("element_green_square_glossy.png");
	
}