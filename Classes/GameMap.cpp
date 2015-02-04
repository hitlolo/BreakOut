#include "GameMap.h"

GameMap::GameMap()
	: rootNode(nullptr)
	, levelLayer(nullptr)
	, buttonPanel(nullptr)
{
	setAnchorPoint(Point(0.5, 0.5));
	soundEngine = GameSound::getInstance();
}

GameMap::~GameMap()
{
	buttonVector.clear();
}

Scene* GameMap::createScene()
{
	auto scene = Scene::create();
	auto layer = GameMap::create();
	scene->addChild(layer);
	return scene;
}

bool GameMap::init()
{
	if (!Layer::init())
	{
		return false;
	}
	setKeyboardEnabled(true);
	initFromCSBFile();
	GameMap::getButtonsFromRoot();
	return true;
}


void GameMap::initFromCSBFile()
{
	rootNode = CSLoader::createNode("mapLayer.csb");

	this->addChild(rootNode);
}

void GameMap::getButtonsFromRoot()
{
	buttonPanel = rootNode->getChildByName("buttonPanel");
	String *filename;
	for (int i = 1; i <= 6; i++)
	{
		filename = String::createWithFormat("levelButton_%d", i);
		auto button = dynamic_cast<ui::Button*>(buttonPanel->getChildByName(filename->getCString()));
		button->setTag(i);
		button->addClickEventListener(CC_CALLBACK_1(GameMap::onClickButton, this));
		buttonVector.push_back(button);
		
	}
	
}

void GameMap::onClickButton(Ref* sender)
{
	CCLOG("clicked");
}

void GameMap::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		GameController::getInstance()->popScene();

	}
}