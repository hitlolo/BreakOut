#ifndef BREAK_OUT_DATA
#define BREAK_OUT_DATA

#define USING_NS_CCD                     using namespace CocosDenshion
#define USING_NS_UI                      using namespace ui

#define CC_SYNTHESIZE_SETONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual void set##funName(varType var){ varName = var; }

#define GET_BUTTON(varRoot,varName)\
varName = dynamic_cast<ui::Button*>(varRoot->getChildByName(#varName))

#define GET_CHECKBOX(varRoot,varName)\
varName = dynamic_cast<ui::CheckBox*>(varRoot->getChildByName(#varName))

#define CENTER Point(Director::getInstance()->getVisibleSize().width/2,Director::getInstance()->getVisibleSize().height/2)

#define PHYSICSBODY_MATERIAL_BREAKOUT  PhysicsMaterial(0,1,0)
typedef enum class game_state
{
	LOGO = 0,
	MENU,
	MAP,
	GAME,
	OVER
}GAME_STATE;

typedef enum class ball_state
{
	TO_BE_START = 0,
	TO_BE_BONUS,
	TO_BE_RESTART
}BALL_STATE;



#endif