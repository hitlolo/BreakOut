#include "HudLayer.h"


bool HudLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->initRootNodeFromCSB();
	this->initFruitLabel();
	return true;
}

HudLayer::HudLayer()
	:score(0)
	,scoreText(nullptr)
	, bonusPanel(nullptr)
	, bonusTimeText(nullptr)
	, fruitLabel(nullptr)
	, bonusTime(0)

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


void HudLayer::initFruitLabel()
{
	fruitLabel = Text::create("+100", "kenpixel_future.ttf", 13);
	fruitLabel->setGlobalZOrder(100);
	this->addChild(fruitLabel);
	fruitLabel->setVisible(false);

}

void HudLayer::showBonusText(Point position, std::string text)
{
	fruitLabel->setVisible(true);
	fruitLabel->setPosition(position);
	fruitLabel->setOpacity(255);
	fruitLabel->setText(text);
	//
	auto scaleup = ScaleTo::create(0.02f, 2.0f);
	auto scaledown = ScaleTo::create(0.2f, 1.0f);
	auto scale = Sequence::create(scaleup, scaledown, nullptr);
	auto fade = FadeOut::create(1.0f);
	auto jump = JumpBy::create(1.0f, Point(0, 0), 30, 1);
	auto visibel = CallFunc::create(CC_CALLBACK_0(Label::setVisible, fruitLabel, false));
	auto action = Sequence::create(Spawn::create(scale, fade, jump, nullptr), visibel, nullptr);
	fruitLabel->runAction(action);
}

void HudLayer::updateScore(int score)
{
	
	//auto retain = CallFunc::create(CC_CALLBACK_0(Text::retain, scoreText));
	auto scaleup = ScaleTo::create(0.02f, 2.0f);
	auto scaledown = ScaleTo::create(0.2f, 1.0f);
	//	auto release = CallFunc::create(CC_CALLBACK_0(Text::release, scoreText));
	auto scoreAction = Sequence::create(scaleup, scaledown,nullptr);

		
	

	this->score += score;
	String *s_score = String::createWithFormat("%03d", this->score);
	this->scoreText->setText(s_score->getCString());
	
	scoreText->runAction(scoreAction);
	
	
	
}

//TODO
void HudLayer::showBonusTime(unsigned time)
{
	
	if (time == 0)//means stop and setvisible
	{
		if (bonusPanel->isVisible())
		{
			this->unschedule(CC_SCHEDULE_SELECTOR(HudLayer::bonusTimeCountingDown));
		}
		this->bonusTime = 0;
		this->bonusTimeText->setText("00:00");
		this->bonusPanel->setVisible(false);
		return;
	}

	else if(bonusPanel->isVisible())
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(HudLayer::bonusTimeCountingDown));
	}

	bonusTime = time;
	this->bonusPanel->setVisible(true);
	String *text = String::createWithFormat("00:%02d", bonusTime);
	this->bonusTimeText->setText(text->getCString());
	
	this->schedule(CC_SCHEDULE_SELECTOR(HudLayer::bonusTimeCountingDown), 1.0f);
}

void HudLayer::bonusTimeCountingDown(float delta)
{
	bonusTime -= 1;
	String *text = String::createWithFormat("00:%02d", bonusTime);
	this->bonusTimeText->setText(text->getCString());
	if (bonusTime <= 0)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(HudLayer::bonusTimeCountingDown));
		this->bonusPanel->setVisible(false);
	}
}