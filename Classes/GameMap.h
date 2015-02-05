#ifndef BREAK_OUT_MAP
#define BREAK_OUT_MAP

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameSound.h"
#include "GameData.h"
#include "GameController.h"
#include "PreviewLayer.h"
#include "CreditLayer.h"

USING_NS_CC;
USING_NS_UI;

class GameMap :public Layer
{
public:
	static Scene* createScene();

	CREATE_FUNC(GameMap);

	virtual bool init() override;

	GameMap();

	~GameMap();

	CC_SYNTHESIZE(SoundDelegate*, soundEngine, SoundEngine);

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;

private:
	void initFromCSBFile();
	void getButtonsFromRoot();
	void onClickButton(Ref* sender);

private:
	
	std::vector<ui::Button*>  buttonVector;
	Node   *rootNode;
	Node   *buttonPanel;
	Node   *levelNode;
};






#endif