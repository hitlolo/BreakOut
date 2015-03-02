#ifndef BREAK_OUT_CREDIT
#define BREAK_OUT_CREDIT

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameSound.h"


class CreditLayer :public Layer
{

public:
	CREATE_FUNC(CreditLayer)
	virtual bool init() override;
	virtual void onEnter() override;
	CreditLayer();
	~CreditLayer();
	void onCancel();
public:
	CC_SYNTHESIZE(SoundDelegate*, soundEngine, SoundEngine);
private:
	void addCSBRootFile();
	void setTouchListeners();
	void runInAnimation();
	void runOutAnimation();
	void playClickEffect();
private:
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchCancelled(Touch* touch, Event* event);
};

#endif