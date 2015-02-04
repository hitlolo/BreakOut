#ifndef BREAK_OUT_MENU
#define BREAK_OUT_MENU

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameSound.h"
#include "GameController.h"
#include "OptionLayer.h"
#include "CreditLayer.h"

USING_NS_CC;
USING_NS_UI;

class GameMenu :public Layer
{

public:
	static Scene* createScene();

	CREATE_FUNC(GameMenu);

	virtual bool init() override;

	virtual void onEnter() override;

	GameMenu();
	
	~GameMenu();

	CC_SYNTHESIZE(SoundDelegate*, soundEngine, SoundEngine);

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;

private:
	void addMenu();

	void getMenuRoot(Node*);

	void setTitleFontLineout();

	void getButtonsFromRoot();

	void addButtonListeners();

	void setAndStartUIAnimation();

private:
	Node*     menuRoot;

	Button*   buttonStart;

	Button*   buttonOptions;

	Button*   buttonCredits;

	Button*   buttonTutorial;

	void startGame(Ref* sender);

	void showOptions(Ref* sender);

	void showCredits(Ref* sender);

	void showTutorial(Ref* sender);



	void playClickEffect();
};
#endif