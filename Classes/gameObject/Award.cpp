#include "Award.h"
USING_NS_CC;

Award::Award(void) :	vy(8.0f),
									curState(0)
{
}


Award::~Award(void)
{
}
bool Award::init()
{
	Sprite::init();

	return true;
}
void Award::initWithAward(const std::string& file,int type)
{
	curState	=	type;
	Sprite* award	= Sprite::createWithSpriteFrameName(file);
	this->addChild(award);
};

void Award::move()
{
	float y = this->getPositionY() - vy ;

	float x = this->getPositionX() + 2 * CCRANDOM_0_1() >= Director::getInstance()->getVisibleSize().width * 3 / 4  ? 
				  this->getPositionX() - 2 * CCRANDOM_0_1() : this->getPositionX() + 2 * CCRANDOM_0_1();

	this->setPosition(x ,y);
	if (this->getPositionY() - vy < -this->getContentSize().height)
	{
		if (this->getParent())
		{
			destory();
		}
	}
}
void Award::destory()
{
	this->removeFromParent();
}
int Award::getState()const
{
	return curState;
}