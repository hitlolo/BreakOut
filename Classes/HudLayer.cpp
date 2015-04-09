#include "HudLayer.h"


bool HudLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->initRootNodeFromCSB();

	return true;
}

HudLayer::HudLayer()
	:score(0)
	,scoreText(nullptr)
	, bonusPanel(nullptr)
	, bonusTimeText(nullptr)

{

}

HudLayer::~HudLayer()
{

}


void HudLayer::initRootNodeFromCSB()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->setAnchorPoint(Point(0.5, 0.5));
	auto rootNode = CSLoader::createNode("HudNode.csb");
	rootNode->setPosition(Point(0, 50));
	this->addChild(rootNode);

	getItemsFromRoot(rootNode);
}


void HudLayer::getItemsFromRoot(Node* root)
{
	Node *mainPanel = root->getChildByName("mainPanel");
	this->scoreText = (Text*)mainPanel->getChildByName("scoreText");
	this->bonusPanel = mainPanel->getChildByName("bonusPanel");
	this->bonusTimeText = (Text*)bonusPanel->getChildByName("bonusText");
	for (int i = 1; i <= 3; i++)
	{
		String *filename = String::createWithFormat("lifeSprite_%d", i);
		Sprite *sprite = (Sprite*)mainPanel->getChildByName(filename->getCString());
		this->heartVector.push_back(sprite);
	}

	this->bonusPanel->setVisible(false);
}


void HudLayer::updateScore(int score)
{
	
	//auto retain = CallFunc::create(CC_CALLBACK_0(Text::retain, scoreText));
	auto scaleup = ScaleTo::create(0.02f, 2.0f);
	auto scaledown = ScaleTo::create(0.2f, 1.0f);
	//	auto release = CallFunc::create(CC_CALLBACK_0(Text::release, scoreText));
	auto scoreAction = Sequence::create(scaleup, scaledown,nullptr);

		
	

	this->score += score;
	String *s_score = String::createWithFormat("%d", this->score);
	this->scoreText->setText(s_score->getCString());
	
	scoreText->runAction(scoreAction);
	
	
	
}