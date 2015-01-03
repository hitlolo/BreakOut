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
	addMenu();
    return true;
}

GameMenu::GameMenu():
buttonStart(nullptr),
buttonOptions(nullptr),
buttonCredits(nullptr),
buttonTutorial(nullptr),
menuRoot(nullptr)
{

}

GameMenu::~GameMenu()
{

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

void GameMenu::getMenuRoot(Node* root)
{
	menuRoot = root->getChildByName("menuRoot");
}

void GameMenu::setTitleFontLineout()
{
	auto title = dynamic_cast<Text*>(menuRoot->getChildByName("textTitle"));
	title->enableOutline(Color4B(25, 26, 25, 155), 3);
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

void GameMenu::startGame(Ref* sender)
{
	//test
	GameController::getInstance()->goState(GAME_STATE::GAME);
}

void GameMenu::showOptions(Ref* sender)
{

}

void GameMenu::showCredits(Ref* sender)
{

}

void GameMenu::showTutorial(Ref* sender)
{

}

