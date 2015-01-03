#ifndef BREAK_OUT_MENU
#define BREAK_OUT_MENU

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameSound.h"
#include "GameController.h"

USING_NS_CC;
USING_NS_UI;

class GameMenu :public Layer
{

public:
	static Scene* createScene();

	CREATE_FUNC(GameMenu);

	virtual bool init() override;

	GameMenu();
	
	~GameMenu();

private:
	void addMenu();

	void getMenuRoot(Node*);

	void setTitleFontLineout();

	void getButtonsFromRoot();

	void addButtonListeners();

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
};
#endif