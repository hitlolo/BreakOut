#ifndef BREAK_OUT_MENU
#define BREAK_OUT_MENU

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameSound.h"
#include "GameController.h"
#include "OptionLayer.h"
#include "CreditLayer.h"
#include "TutorialLayer.h"

USING_NS_CC;
USING_NS_UI;

class GameMenu :public Layer
{

public:
	static Scene* createScene();
	CREATE_FUNC(GameMenu);
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	GameMenu();	
	virtual ~GameMenu();
	

private:
	//get menu items
	void addMenu();
	void getMenuRoot(Node*);
	void setTitleFontLineout();
	void getButtonsFromRoot();
	void setButtonListeners();
	//start ui animation
	void setAndStartUIAnimation();	
	

private:
	Node*          menuRoot;
	Button*        buttonStart;
	Button*        buttonOptions;
	Button*        buttonCredits;
	Button*        buttonTutorial;
	OptionLayer*   optionLayer;
	CreditLayer*   creditLayer;
	TutorialLayer* tutorLayer;
	CC_SYNTHESIZE(SoundDelegate*, soundEngine, SoundEngine);

	//button callbacks
	void startGame(Ref* sender);
	void showOptions(Ref* sender);
	void showCredits(Ref* sender);
	void showTutorial(Ref* sender);
	//sound effect
	void playClickEffect();
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;
};
#endif