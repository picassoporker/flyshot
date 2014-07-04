#include "Bullet.h"
USING_NS_CC;

Bullet::Bullet(void): type(0),vx(0.0f),vy(25.5f),offset(0),winSize()
{
}
//Bullet::Bullet(BULLET_TYPE t) : type(t),vx(0.0f),vy(25.5f),offset(0),winSize()
//{
//
//}

Bullet::~Bullet(void)
{
	
}

bool Bullet::init()
{
	Sprite::init();
	winSize	=	Director::getInstance()->getVisibleSize();
	return true;
}
//Bullet*  Bullet::create(BULLET_TYPE type)
//{
//	Bullet* pBullet = new Bullet(type);
//	if (pBullet && pBullet->init())
//	{
//		pBullet->autorelease();
//		return pBullet;
//	}
//	delete pBullet;
//	return NULL;
//}
void Bullet::initWithType(BULLET_TYPE type)
{
	char chFile[20];
	sprintf(chFile,"bullet%d.png",type);
	initWithSpriteFrameName(chFile);
}
void Bullet::move()
{
	offset	=	offset >0 ? offset : 0;
	float x = this->getPositionX() + vx ;
	float y = this->getPositionY() + vy;
	this->setPosition(x,y + offset);
	if (y + offset > winSize.height )
	{
		if (this->getParent())
		{
			this->removeFromParent();
		}
	}
	//log("ref:%d",this->getReferenceCount());
}