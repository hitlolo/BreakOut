#include "GameMenu.h"

Scene* GameMenu::createScene()
{

	auto scene = Scene::create();
    auto layer = GameMenu::create();
    scene->addChild(layer);
    return scene;
}

bool GameMenu::init()
{
    if(!Layer::init())
    {
        return false;
    }
	setKeyboardEnabled(true);
	addMenu();
    return true;
}

GameMenu::GameMenu():
buttonStart(nullptr),
buttonOptions(nullptr),
buttonCredits(nullptr),
buttonTutorial(nullptr),
menuRoot(nullptr),
optionLayer(nullptr),
creditLayer(nullptr),
tutorLayer(nullptr)
{
	soundEngine = GameSound::getInstance();
}

GameMenu::~GameMenu()
{
	soundEngine = nullptr;
}

void GameMenu::addMenu()
{
	auto node = CSLoader::createNode("menuScene.csb");
	this->addChild(node);

	this->getMenuRoot(node);
	this->setTitleFontLineout();
	this->getButtonsFromRoot();
	this->addButtonListeners();
	
}

void GameMenu::onEnter()
{
	Layer::onEnter();
	this->setAndStartUIAnimation();
	getSoundEngine()->playBackgroundMusic();
	//if (optionLayer)
	//	optionLayer->onCancel();
	//if (creditLayer)
	//	creditLayer->onCancel();

}

void GameMenu::onExit()
{
	Layer::onExit();
//	this->stopAllActions();
//	this->removeAllChildrenWithCleanup(false);
	this->removeChild(optionLayer);
	this->removeChild(creditLayer);
	this->removeChild(tutorLayer);
	optionLayer = nullptr;
	creditLayer = nullptr;
	tutorLayer  = nullptr;
	
}

void GameMenu::getMenuRoot(Node* root)
{
	menuRoot = root->getChildByName("menuRoot");
}

void GameMenu::setTitleFontLineout()
{
	auto title = dynamic_cast<Text*>(menuRoot->getChildByName("textTitle"));
	title->enableOutline(Color4B(25, 26, 25, 155), 3);
	title->enableShadow(Color4B::BLACK,Size(8,-8),2);
}

void GameMenu::getButtonsFromRoot()
{
	GET_BUTTON(menuRoot, buttonStart);
	GET_BUTTON(menuRoot, buttonOptions);
	GET_BUTTON(menuRoot, buttonTutorial);
	GET_BUTTON(menuRoot, buttonCredits);
}

void GameMenu::addButtonListeners()
{
	buttonStart->addClickEventListener(CC_CALLBACK_1(GameMenu::startGame,this));
	buttonOptions->addClickEventListener(CC_CALLBACK_1(GameMenu::showOptions, this));
	buttonTutorial->addClickEventListener(CC_CALLBACK_1(GameMenu::showTutorial, this));
	buttonCredits->addClickEventListener(CC_CALLBACK_1(GameMenu::showCredits, this));
}

void GameMenu::setAndStartUIAnimation()
{
	//set start position
	//button start
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point originLocation = buttonStart->getPosition();
	buttonStart->setPosition(Point((-buttonStart->getContentSize().width/2), originLocation.y));
	buttonStart->runAction(MoveTo::create(0.8f, originLocation));

	//button options
	originLocation = buttonOptions->getPosition();
	buttonOptions->setPosition(Point(buttonOptions->getContentSize().width + visibleSize.width, originLocation.y));
	buttonOptions->runAction(MoveTo::create(0.8f, originLocation));

	//button Tutorial
	originLocation = buttonTutorial->getPosition();
	buttonTutorial->setPosition(Point(-buttonTutorial->getContentSize().width, originLocation.y));
	buttonTutorial->runAction(MoveTo::create(0.8f, originLocation));

	//button Credits
	originLocation = buttonCredits->getPosition();
	buttonCredits->setPosition(Point(buttonCredits->getContentSize().width + visibleSize.width, originLocation.y));
	buttonCredits->runAction(MoveTo::create(0.8f, originLocation));
}


void GameMenu::startGame(Ref* sender)
{
	//test
	this->playClickEffect();
	GameController::getInstance()->goState(GAME_STATE::MAP);
}

void GameMenu::showOptions(Ref* sender)
{
	//this->playClickEffect();
	if (!optionLayer)
	{
		this->playClickEffect();
		optionLayer = OptionLayer::create();
		this->addChild(optionLayer);
	}
	else
		optionLayer->onShow();
	
}

void GameMenu::showCredits(Ref* sender)
{
	if (!creditLayer)
	{
		this->playClickEffect();
		creditLayer = CreditLayer::create();
		this->addChild(creditLayer);
	}
	else
		creditLayer->onShow();
	
}

void GameMenu::showTutorial(Ref* sender)
{
	//this->playClickEffect();
	if (!tutorLayer)
	{
		this->playClickEffect();
		tutorLayer = TutorialLayer::create();
		this->addChild(tutorLayer);
	}
	else
		tutorLayer->onShow();

}



void GameMenu::playClickEffect()
{
	getSoundEngine()->playClickEffect();
}

//void GameMenu::keyBackClicked()
//{
//	Director::getInstance()->end();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
//	exit(0);
//#endif  
//}

void GameMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{	
		
		if (optionLayer&&optionLayer->isVisible())
		{
			optionLayer->onCancel();
		}
		else if (creditLayer&&creditLayer->isVisible())
		{
			creditLayer->onCancel();
		//	creditLayer = nullptr;
		}
		else
		{
			
			getSoundEngine()->end();
			Director::getInstance()->end();
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
				exit(0);
			#endif  
		
		}
		
	}
}