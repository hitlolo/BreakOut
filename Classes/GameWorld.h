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
#include "PhysicsProtocol.h"
#include "GB2ShapeCache-x.h"
#include "TouchLayer.h"
#include "GameController.h"
#include "BrickLayer.h"


USING_NS_CC;
USING_NS_UI;

class GameWorld :public Layer, public PhysicsProtocol,public TouchProtocol
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
	b2World* getPhysicsWorld() const;

private:
	void addBackground();
	void createPhysicsWorld();
	void createEdgeBox();
	//init with the TMX level data
	bool initLevelData(int);
	void addBall();
	void addPaddle();
	void addTouch();

private:
	//win SIZE
	Size          visibleSize;
	Point         originPoint;
	//Physics
	b2World       *m_world;
	b2Body        *m_groundBody;
	GLESDebugDraw *m_debugDraw;
	GameBall      *m_ball;
	GamePaddle    *m_paddle;
	BrickLayer    *m_brickLayer;
	int            m_maxSpeed;

protected:
	virtual void onGameStart() override;
	virtual void onPaddleBeginMove(const std::vector<Touch*>& touches) override;
	virtual void onPaddleMove(const std::vector<Touch*>& touches) override;
	virtual void onPaddleEndMove() override;
	virtual void onPaddleCancelMove() override;
	virtual void onReturn() override;
};

#endif