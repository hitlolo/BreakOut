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
	virtual void  onEnter() override;
	
	//public function for menu layer
	//1.show
	//2.hide
	void onCancel();
	void onShow();

private:
	//self init functions
	//get items from csb file (cocosstudio)
	void initSoundEngine();
	void initPageViewFromCSB();
	void getItemsFromRoot();
	void setTouchListeners();

	//ui animations
	void runInAnimation();
	void runOutAnimation();
	//sound effect
	void playClickEffect();
	void playSwingEffect();
	//is touched on panel 
	bool isTouchOnPanel(Touch* touch);


private:
	Node                        *rootNode;
	PageView                    *pageView;
	EventListenerTouchOneByOne  *eventListener;
	CC_SYNTHESIZE(SoundDelegate*, soundEngine, SoundEngine);

private:
	//touch callback
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchCancelled(Touch* touch, Event* event);

	//page view widget call back
	void pageViewEvent(Ref* pSender, PageView::EventType type);

};

#endif
