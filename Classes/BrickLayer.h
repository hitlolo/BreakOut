#ifndef BREAK_OUT_BRICK_LAYER
#define BREAK_OUT_BRICK_LAYER

#include "cocos2d.h"
#include "GameBrick.h"

USING_NS_CC;

class BrickLayer :public Layer
{
public:
	static BrickLayer* create(int, b2World*);
	bool init(int, b2World*);
	BrickLayer(int, b2World*);
	~BrickLayer();
	std::vector<GameBrick*> getBricks();
private:
	int                          m_curLevel;
	b2World*                     m_world;
	std::vector<GameBrick*>      m_bricksVector;
	
private:
	std::string getFileName();
	void initLevelData(int level);
};





#endif