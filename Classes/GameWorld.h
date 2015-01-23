#ifndef BREAK_OUT_WORLD
#define BREAK_OUT_WORLD

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameSound.h"
#include "GameData.h"
#include "GameBall.h"
#include "GamePaddle.h"
#include "Box2D\Box2D.h"
#include "GLES-Render.h"


USING_NS_CC;
USING_NS_UI;

class GameWorld :public Layer
{
public:
	static GameWorld* create(int);

	bool init(int);

	GameWorld();

	~GameWorld();
	//update the physics world  too
	virtual void update(float dt) override;
	//draw physics debug draw
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);

	virtual void onEnter() override;

private:
	void addBackground();

	void createPhysicsWorld();

	void createEdgeBox();
	//init with the TMX level data
	bool initLevelData(int);

private:
	//win SIZE
	Size          visibleSize;
	Point         originPoint;
	//Physics
	b2World       *_world;
	GLESDebugDraw *_debugDraw;

};

#endif