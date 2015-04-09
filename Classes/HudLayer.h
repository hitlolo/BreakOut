#ifndef BREAK_OUT_HUD
#define BREAK_OUT_HUD

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameSound.h"

USING_NS_CC;
USING_NS_UI;



class HudLayer :public Layer
{
public:
	CREATE_FUNC(HudLayer);
	virtual bool init() override;
	HudLayer();
	~HudLayer();
private:
	void initRootNodeFromCSB();
	void getItemsFromRoot(Node* root);

public:
	void updateScore(int score);

private:
	std::vector<Sprite*> heartVector;
	Node                *bonusPanel;
	Text                *bonusTimeText;
	Text                *scoreText;

private:
	int                 score;
};






#endif