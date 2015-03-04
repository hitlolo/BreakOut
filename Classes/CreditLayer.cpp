#include "CreditLayer.h"

CreditLayer::CreditLayer()
{
	soundEngine = GameSound::getInstance();
}

CreditLayer::~CreditLayer()
{

}

bool CreditLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	addCSBRootFile();
	setTouchListeners();
	return true;
}

void CreditLayer::onEnter()
{
	Layer::onEnter();
	this->runInAnimation();
}

void CreditLayer::addCSBRootFile()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->setAnchorPoint(Point(0.5, 0.5));
	auto node = CSLoader::createNode("creditNode.csb");
//	node->setPosition(CENTER);
	Point nextLocation = Point(getContentSize().width + visibleSize.width, visibleSize.height / 2);
	this->setPosition(nextLocation);
	this->addChild(node);

	//auto panel = node->getChildByName("panel");
	//if (!panel)
	//	return;

	////set font name again due to the cocos studio 2.0 bugs (Text load ttf error)
	//for (auto node : panel->getChildren())
	//{
	//	auto textNode = dynamic_cast<ui::Text*>(node);
	//	if (textNode)
	//	{
	//		textNode->enableOutline(Color4B(25, 26, 25, 155), 1);
	//	}
	//}
}

void CreditLayer::setTouchListeners()
{
	eventListener = EventListenerTouchOneByOne::create();
	eventListener->setSwallowTouches(true);
	eventListener->onTouchBegan = CC_CALLBACK_2(CreditLayer::onTouchBegan, this);
	eventListener->onTouchCancelled = CC_CALLBACK_2(CreditLayer::onTouchCancelled, this);
	eventListener->onTouchEnded = CC_CALLBACK_2(CreditLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}

void  CreditLayer::runInAnimation()
{
	eventListener->setEnabled(true);
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->setVisible(true);
	this->setScale(1.0f);
	auto action = Spawn::create(MoveTo::create(0.3f, Point(originPoint.x + visibleSize.width / 2, (originPoint.y + visibleSize.height / 2))), FadeIn::create(0.3f), nullptr);
	this->runAction(action);
	
}

void  CreditLayer::runOutAnimation()
{
	eventListener->setEnabled(false);
	Point originPoint = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto action = Spawn::create(MoveTo::create(0.3f, Point(getContentSize().width + visibleSize.width, (originPoint.y + visibleSize.height / 2))), FadeOut::create(0.3f), ScaleBy::create(0.3f, 0.3f), nullptr);
	auto set = CallFunc::create(CC_CALLBACK_0(CreditLayer::setVisible, this, false));
//	auto remove = CallFunc::create(CC_CALLBACK_0(CreditLayer::removeFromParent, this));
//	auto action_ = Sequence::create(action, set, remove, nullptr);
	auto action_ = Sequence::create(action, set, nullptr);
	this->runAction(action_);
}

bool  CreditLayer::onTouchBegan(Touch* touch, Event* event)
{
	if (isVisible())
	{
		onCancel();
	}
	return true;
}
void  CreditLayer::onTouchEnded(Touch* touch, Event* event)
{
	

}
void  CreditLayer::onTouchCancelled(Touch* touch, Event* event)
{

}

void CreditLayer::onCancel()
{
	this->playClickEffect();
	runOutAnimation();
	
}

void CreditLayer::onShow()
{
	this->playClickEffect();
	runInAnimation();
}

void  CreditLayer::playClickEffect()
{
	getSoundEngine()->playClickEffect();
}
