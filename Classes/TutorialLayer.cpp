#include "TutorialLayer.h"

bool  TutorialLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initSoundEngine();
	initPageViewFromCSB();
	setTouchListeners();
	getItemsFromRoot();
	return true;
}

void TutorialLayer::onEnter()
{
	Layer::onEnter();
	this->runInAnimation();
}

void TutorialLayer::initSoundEngine()
{
	setSoundEngine(GameSound::getInstance());
}

void TutorialLayer::initPageViewFromCSB()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->setContentSize(Size(200,300));
	this->setAnchorPoint(Point(0.5, 0.5));
	Point nextLocation = Point(this->getContentSize().width + visibleSize.width, visibleSize.height / 2);
	this->setPosition(nextLocation);
    rootNode = CSLoader::createNode("TutorNode.csb");
	this->addChild(rootNode);
}

void  TutorialLayer::setTouchListeners()
{
	eventListener = EventListenerTouchOneByOne::create();
	eventListener->setSwallowTouches(true);
	eventListener->onTouchBegan = CC_CALLBACK_2(TutorialLayer::onTouchBegan, this);
	eventListener->onTouchCancelled = CC_CALLBACK_2(TutorialLayer::onTouchCancelled, this);
	eventListener->onTouchEnded = CC_CALLBACK_2(TutorialLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}


void TutorialLayer::getItemsFromRoot()
{
	pageView = (PageView*)rootNode->getChildByName("PageView");
	pageView->setClippingEnabled(true);
	pageView->addEventListener(CC_CALLBACK_2(TutorialLayer::pageViewEvent, this));
}


void TutorialLayer::runInAnimation()
{
	eventListener->setEnabled(true);
	this->setVisible(true);
	//	this->setScale(1.0f);
	auto action = Spawn::create(MoveTo::create(0.3f, CENTER), FadeIn::create(0.3f), nullptr);
	this->runAction(action);
}

void TutorialLayer::runOutAnimation()
{
	eventListener->setEnabled(false);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point nextLocation = Point(this->getContentSize().width + visibleSize.width, visibleSize.height / 2);
	//	auto action = Spawn::create(MoveTo::create(0.3f, nextLocation), FadeOut::create(0.3f), ScaleBy::create(0.3f, 0.3f), nullptr);
	auto action = Spawn::create(MoveTo::create(0.3f, nextLocation), FadeOut::create(0.3f), nullptr);
	auto set = CallFunc::create(CC_CALLBACK_0(TutorialLayer::setVisible, this, false));
	//auto remove = CallFunc::create(CC_CALLBACK_0(OptionLayer::removeFromParent, this));
	//auto action_ = Sequence::create(set,action, remove, nullptr);
	auto action_ = Sequence::create(action, set, nullptr);

	this->runAction(action_);
}

void  TutorialLayer::playClickEffect()
{
	getSoundEngine()->playClickEffect();
}

void TutorialLayer::playSwingEffect()
{
	getSoundEngine()->playSwingEffect();
}


void TutorialLayer::onShow()
{
	this->playClickEffect();
	this->runInAnimation();
}

void TutorialLayer::onCancel()
{
	this->playClickEffect();
	this->runOutAnimation();
}



//touch
bool  TutorialLayer::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}
void  TutorialLayer::onTouchEnded(Touch* touch, Event* event)
{
	if (!isTouchOnPanel(touch))
	{
		this->onCancel();
	}
}

void  TutorialLayer::onTouchCancelled(Touch* touch, Event* event)
{

}

bool  TutorialLayer::isTouchOnPanel(Touch* touch)
{
	Point position = touch->getLocationInView();
	Rect panelRect = rootNode->boundingBox();
	return panelRect.containsPoint(position);

}


void TutorialLayer::pageViewEvent(Ref *pSender, PageView::EventType type)
{
	switch (type)
	{
	case PageView::EventType::TURNING:
	{
		this->playSwingEffect();
	}
	break;

	default:
		break;
	}
}
