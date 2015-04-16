#ifndef BREAK_OUT_LOGO
#define BREAK_OUT_LOGO

#include "cocos2d.h"
#include "GameController.h"
#include "GameSound.h"

USING_NS_CC;

class GameLogo :public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(GameLogo);
	virtual bool init() override;

private:
	void startLoading();
	void addLogoAndLoad();
	void loadRes();
	void loadPngAndShapes();
	void loadSpriteFramesAfterPNGOver(Texture2D* texture);	void loadMusicAndEffects();
	void overLoading();

	//GameController goto menu state
	void startGame();
};

#endif