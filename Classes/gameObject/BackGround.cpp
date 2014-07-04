#include "BackGround.h"
USING_NS_CC;

BackGround::BackGround(void):vy(0),bgOne(NULL),bgTwo(NULL),winSize(0,0),height(0)
{
}


BackGround::~BackGround(void)
{
}
bool BackGround::init()
{
	Layer::init();
	
	bgOne	= Sprite::createWithSpriteFrameName("background_2.png");
	this->addChild(bgOne);
	bgOne->setAnchorPoint(Point::ZERO);
	bgOne->setPosition(0,0);
	height = bgOne->getContentSize().height;
	winSize = Director::getInstance()->getVisibleSize();
	vy = 15;
	bgTwo	= Sprite::createWithSpriteFrameName("background_2.png");
	this->addChild(bgTwo);
	bgTwo->setAnchorPoint(Point::ZERO);
	bgTwo->setPositionY(bgOne->getPositionY() + height);
	return true;
}
void BackGround::move()
{

	bgOne->setPositionY(bgOne->getPositionY() - vy );
	bgTwo->setPositionY(bgTwo->getPositionY() - vy );
	if (bgOne->getPositionY() < -height)
	{
		bgOne->setPositionY(bgTwo->getPositionY() + height);
	}
	else if (bgTwo->getPositionY()  < -height)
	{
		bgTwo->setPositionY(bgOne->getPositionY() + height);
	}
	//float top		= bgOne->getPositionY() - vy  ;
	//float bottom = bgTwo->getPositionY() - vy;
	//bgOne->setPositionY(top);
	//bgTwo->setPositionY(bottom);
	//if (top < -height)
	//{
	//	bgOne->setPositionY(bottom + height);
	//}
	//else if (bottom < -height)
	//{
	//	bgTwo->setPositionY(top + height);
	//}
}
