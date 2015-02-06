#ifndef BREAK_OUT_TOUCH_PRO
#define BREAK_OUT_TOUCH_PRO
#include "cocos2d.h"
USING_NS_CC;
class TouchProtocol
{
public:
	CC_SYNTHESIZE(bool, isStarted, Started);
	virtual void onGameStart() = 0;
	virtual void onPaddleBeginMove(const std::vector<Touch*>& touches) = 0;
	virtual void onPaddleMove(const std::vector<Touch*>& touches) = 0;
	virtual void onPaddleEndMove() = 0;
	virtual void onPaddleCancelMove() = 0;
	virtual void onReturn() = 0;

};


#endif