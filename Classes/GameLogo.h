#ifndef BREAK_OUT_LOGO
#define BREAK_OUT_LOGO

#include "cocos2d.h"
#include "GameController.h"

USING_NS_CC;

class GameLogo :public Layer
{
public:
	virtual bool init() override;

	static Scene* createScene();

	CREATE_FUNC(GameLogo);

private:
	void addLogo();

	void loadRes();

	void loadImageOver(Texture2D* texture);
	void loadMusic();
	void startGame();
	void nextScene();
	virtual void onExit() override;
};

#endif