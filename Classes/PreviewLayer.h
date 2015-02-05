#ifndef BREAK_OUT_PRE
#define BREAK_OUT_PRE

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameData.h"
#include "PhysicsSprite.h"

USING_NS_CC;
USING_NS_UI;

class PreviewLayer :public Layer
{

public:
	static PreviewLayer* create(int level);
	virtual bool init() override;
	virtual void onEnter() override;
	PreviewLayer(int level);
	virtual ~PreviewLayer();
protected:
	void addBackground();
	void setTouchListeners();
	void initFromTMXFile(std::string &file);
	bool isTouchOnPanel(Touch* touch);
	Sprite* createBrickWithDef(Value &def);
	std::string getBrickColor(Value &def);
	std::string getLongBrickColor(Value &def);
	std::string getShortBrickColor(Value &def);

protected:
	//touch
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchCancelled(Touch* touch, Event* event);

protected:
	std::string                  tmxFileName;
	std::vector<PhysicsSprite*>  bricksVector;
	TMXTiledMap                 *brickLayer;
};







#endif