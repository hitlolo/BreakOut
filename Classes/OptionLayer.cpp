#include "OptionLayer.h"

bool OptionLayer::init()
{
	if (!Layer::init())
	{
		return  false;
	}

	initSoundEngine();
	addCSBRootFile();
	getItemsFromRoot();
	setClickListenersToItems();
	setTouchListeners();

	return true;
}

void OptionLayer::onEnter()
{
	Layer::onEnter();
	this->runInAnimation(); 
}

void  OptionLayer::initSoundEngine()
{
	setSoundEngine(GameSound::getInstance());
}

void OptionLayer::addCSBRootFile()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->setAnchorPoint(Point(0.5,0.5));
	Point nextLocation = Point(this->getContentSize().width + visibleSize.width, visibleSize.height/2);
	this->setPosition(nextLocation);
	rootNode = CSLoader::createNode("optionNode.csb");	
	this->addChild(rootNode);
	//rootNode->setPosition(CENTER);
}

void  OptionLayer::setTouchListeners()
{
	eventListener = EventListenerTouchOneByOne::create();
	eventListener->setSwallowTouches(true);
	eventListener->onTouchBegan = CC_CALLBACK_2(OptionLayer::onTouchBegan, this);
	eventListener->onTouchCancelled = CC_CALLBACK_2(OptionLayer::onTouchCancelled, this);
	eventListener->onTouchEnded = CC_CALLBACK_2(OptionLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}

void  OptionLayer::runInAnimation()
{
	eventListener->setEnabled(true);
	this->setVisible(true);
//	this->setScale(1.0f);
	auto action = Spawn::create(MoveTo::create(0.3f, CENTER), FadeIn::create(0.3f) ,nullptr);
	this->runAction(action);
}

void OptionLayer::runOutAnimation()
{
	eventListener->setEnabled(false);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point nextLocation = Point(this->getContentSize().width + visibleSize.width, visibleSize.height / 2);
//	auto action = Spawn::create(MoveTo::create(0.3f, nextLocation), FadeOut::create(0.3f), ScaleBy::create(0.3f, 0.3f), nullptr);
	auto action = Spawn::create(MoveTo::create(0.3f, nextLocation), FadeOut::create(0.3f), nullptr);
	auto set = CallFunc::create(CC_CALLBACK_0(OptionLayer::setVisible, this, false));
	//auto remove = CallFunc::create(CC_CALLBACK_0(OptionLayer::removeFromParent, this));
	//auto action_ = Sequence::create(set,action, remove, nullptr);
	auto action_ = Sequence::create(action, set, nullptr);
	
	this->runAction(action_);
}

void OptionLayer::getItemsFromRoot()
{
	auto panel = rootNode->getChildByName("panel");
	if (!panel)
		return;
	
	GET_BUTTON(panel, cancelButton);
//	GET_CHECKBOX(panel, soundCheck);
//	GET_CHECKBOX(panel, effectCheck);
	soundCheck = dynamic_cast<ui::CheckBox*>(panel->getChildByName("soundCheck"));
	soundCheck->setSelectedState(getSoundEngine()->isMusicOn());
	effectCheck = dynamic_cast<ui::CheckBox*>(panel->getChildByName("effectCheck"));
	effectCheck->setSelectedState(getSoundEngine()->isEffectOn());
}



void OptionLayer::setClickListenersToItems()
{
	cancelButton->addClickEventListener(CC_CALLBACK_1(OptionLayer::onCancelCallBack,this));
	soundCheck->addEventListenerCheckBox(this, checkboxselectedeventselector(OptionLayer::onMusicCheckBoxCallback));
	effectCheck->addEventListenerCheckBox(this, checkboxselectedeventselector(OptionLayer::onEffectCheckBoxCallback));
}

void  OptionLayer::onCancelCallBack(Ref* sender)
{
	onCancel();
}

void  OptionLayer::onMusicCheckBoxCallback(Ref *pSender, ui::CheckBoxEventType event_type)
{
	this->playClickEffect();
	switch (event_type)
	{
	case ui::CheckBoxEventType::CHECKBOX_STATE_EVENT_SELECTED:
		getSoundEngine()->musicOn();
		break;
	case ui::CheckBoxEventType::CHECKBOX_STATE_EVENT_UNSELECTED:
		getSoundEngine()->musicOff();
		break;
	}
}
void  OptionLayer::onEffectCheckBoxCallback(Ref *pSender, ui::CheckBoxEventType event_type)
{
	this->playClickEffect();
	switch (event_type)
	{
	case ui::CheckBoxEventType::CHECKBOX_STATE_EVENT_SELECTED:
		getSoundEngine()->effectOn();
		break;
	case ui::CheckBoxEventType::CHECKBOX_STATE_EVENT_UNSELECTED:
		getSoundEngine()->effectOff();
		break;
	}

}

//touch
bool  OptionLayer::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}
void  OptionLayer::onTouchEnded(Touch* touch, Event* event)
{
	if (!isTouchOnPanel(touch))
	{
		this->onCancel();
	}
}

void  OptionLayer::onTouchCancelled(Touch* touch, Event* event)
{

}

void  OptionLayer::playClickEffect()
{
	getSoundEngine()->playClickEffect();
}

bool  OptionLayer::isTouchOnPanel(Touch* touch)
{
	Point position = touch->getLocationInView();
	Rect panelRect = rootNode->boundingBox();
	return panelRect.containsPoint(position);
}


void OptionLayer::onShow()
{
	this->playClickEffect();
	this->runInAnimation();
}

void OptionLayer::onCancel()
{
	this->playClickEffect();
	this->runOutAnimation();
}