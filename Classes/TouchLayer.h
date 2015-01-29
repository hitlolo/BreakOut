#ifndef BREAK_OUT_TOUCH
#define BREAK_OUT_TOUCH

#include "cocos2d.h"
#include "TouchProtocol.h"


USING_NS_CC;

class TouchLayer :public Layer
{

public:
	virtual bool init() override;

	CREATE_FUNC(TouchLayer);

    //virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *event) override;
	//virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
	//virtual void onTouchMoved(Touch *touch, Event *unused_event) override;
	//virtual void onTouchEnded(Touch *touch, Event *unused_event) override;
	//virtual void onTouchCancelled(Touch *touch, Event *unused_event) override;

	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event) override;
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event) override;
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event) override;
	virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event) override;

	CC_SYNTHESIZE(TouchProtocol*, touchDeleageted, Delegator);

};

#endif
