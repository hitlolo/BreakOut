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
	CC_SYNTHESIZE(SoundDelegate*, soundEngine, SoundEngine);
	void onCancel();
	void onShow();
private:
	void initSoundEngine();
	void addCSBRootFile();
	void setTouchListeners();
	void getItemsFromRoot();
	void setClickListenersToItems();
	void runInAnimation();
	void runOutAnimation();
	void playClickEffect();
	bool isTouchOnPanel(Touch* touch);
private:
	Node           *rootNode;
	ui::CheckBox   *soundCheck;
	ui::CheckBox   *effectCheck;
	ui::Button     *cancelButton;
	EventListenerTouchOneByOne *eventListener;
private:
	void onCancelCallBack(Ref* sender);
	void onMusicCheckBoxCallback(Ref *pSender, ui::CheckBoxEventType event_type);
	void onEffectCheckBoxCallback(Ref *pSender, ui::CheckBoxEventType event_type);

	//touch
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onTouchCancelled(Touch* touch, Event* event);


};


#endif