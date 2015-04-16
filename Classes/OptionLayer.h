#ifndef BREAK_OUT_OPTIONS
#define BREAK_OUT_OPTIONS

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameSound.h"

USING_NS_CC;
USING_NS_UI;

class OptionLayer :public Layer
{

public:
	CREATE_FUNC(OptionLayer);
	virtual bool init() override;
	virtual void onEnter() override;

	//public function for menu layer
	//1.show
	//2.hide
	void onShow();
	void onCancel();

private:
	//self init functions
	//get items from csb file (cocosstudio)
	void initSoundEngine();
	void addCSBRootFile();
	void setTouchListeners();
	void getItemsFromRoot();
	void setClickListenersToItems();

	//ui animation
	//1.in
	//2.out
	void runInAnimation();
	void runOutAnimation();
	//sound effect when show & hide
	void playClickEffect();
	bool isTouchOnPanel(Touch* touch);

private:
	Node                       *rootNode;
	ui::CheckBox               *soundCheck;
	ui::CheckBox               *effectCheck;
	ui::Button                 *cancelButton;
	EventListenerTouchOneByOne *eventListener;
	CC_SYNTHESIZE(SoundDelegate*, soundEngine, SoundEngine);

private:
	//ui widget callbacks
	void onCancelCallBack(Ref* sender);
	void onMusicCheckBoxCallback(Ref *pSender, ui::CheckBoxEventType event_type);
	void onEffectCheckBoxCallback(Ref *pSender, ui::CheckBoxEventType event_type);

	//touch callback
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchCancelled(Touch* touch, Event* event);


};


#endif