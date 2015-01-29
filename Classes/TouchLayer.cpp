#include "TouchLayer.h"

bool TouchLayer::init()
{

	if (!Layer::init()){
		return false;
	}

	this->setTouchEnabled(true);
	this->setSwallowsTouches(true);

	return true;

}

void TouchLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	getDelegator()->onPaddleBeginMove(touches);
	
}

void TouchLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
	getDelegator()->onPaddleMove(touches);
}

void TouchLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
	if (!(getDelegator()->getStarted()))
	{
		getDelegator()->onGameStart();
	}
	getDelegator()->onPaddleEndMove();
}

void TouchLayer::onTouchesCancelled(const std::vector<Touch*>& touches, Event *unused_event)
{
	getDelegator()->onPaddleEndMove();
}