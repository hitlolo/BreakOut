#ifndef  BREAK_OUT_TUTOR
#define  BREAK_OUT_TUTOR

#include  "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameSound.h"

USING_NS_CC;
USING_NS_UI;
class TutorialLayer :public Layer
{
public:
	CREATE_FUNC(TutorialLayer);
	virtual bool  init() override;
	virtual void onEnter() override;
	CC_SYNTHESIZE(SoundDelegate*, soundEngine, SoundEngine);
	void onCancel();
	void onShow();
private:
	void initSoundEngine();
	void initPageViewFromCSB();
	void setTouchListeners();
	void runInAnimation();
	void runOutAnimation();
	void playClickEffect();
	void playSwingEffect();
	bool isTouchOnPanel(Touch* touch);

private:
	void getItemsFromRoot();

private:
	Node                       *rootNode;
	PageView                   *pageView;
	EventListenerTouchOneByOne *eventListener;


	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchCancelled(Touch* touch, Event* event);

	void pageViewEvent(Ref* pSender, PageView::EventType type);
};

#endif
