#include "PlayFly.h"

USING_NS_CC;

PlayFly::PlayFly(void):winSize(0,0),
									curTouchPos(0,0),
									LIMIT_SPEED(25),
									isTouchFly(false),
									bulletList(),
									offset(0),
									bulletListRed(),
									isEatBlueAward(false)
{
}


PlayFly::~PlayFly(void)
{
	
}

bool PlayFly::init()
{
	Sprite::init();
	winSize = Director::getInstance()->getVisibleSize();
	curTouchPos	=	Point(winSize.width/2 , 100);
	initWithSpriteFrameName("hero_fly_1.png");
	this->setPosition(winSize.width / 2 ,150);
	addEvents();
	this->setZOrder(5);
	return true;
}

bool PlayFly::onTouchBegan(Touch* touch ,Event* evt)
{
	curTouchPos = touch->getLocation();
	return true;
}

void PlayFly::onTouchMoved(Touch* touch ,Event* evt)
{
	curTouchPos = touch->getLocation();
}

void PlayFly::move()
{
	float vx = (curTouchPos.x - this->getPositionX()) / 3;
	float vy = (curTouchPos.y - this->getPositionY()) / 3;
	if (isEatBlueAward)
	{
		for(Bullet* mBullet : bulletList)
		{
			mBullet->offset = vy;
		}
	}
	for (Bullet* rBullet  : bulletListRed)
	{
	rBullet->offset = vy;
	}
	if (vx > LIMIT_SPEED)
	{
		vx = LIMIT_SPEED;
	}else if (vx < -LIMIT_SPEED)
	{
		vx = -LIMIT_SPEED;
	}
	if (vy > LIMIT_SPEED)
	{
		vy = LIMIT_SPEED;
	}else if (vy < -LIMIT_SPEED)
	{
		vy = -LIMIT_SPEED;
	}
	this->setPosition(this->getPositionX() + vx,this->getPositionY() + vy );
	
}

void PlayFly::addEvents()
{
	EventListenerTouchOneByOne* Evt = EventListenerTouchOneByOne::create();
	Evt->onTouchBegan	=	CC_CALLBACK_2(PlayFly::onTouchBegan,this);
	Evt->onTouchMoved	=	CC_CALLBACK_2(PlayFly::onTouchMoved,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(Evt,this);
}

void PlayFly::destory()
{
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
	this->removeFromParent();
}

int count = 0 ;

void PlayFly::fire()
{
	if (count <= 4)
	{
		count++;
		return ;
	}else
	{
		count = 0;
	}
	
	if (isEatBlueAward)
	{
		Bullet* mBullet	= Bullet::create();
		mBullet->initWithType(BLUE_BULLET);
		if (this->getParent())
		{
			int zOrder = this->getZOrder();
			this->getParent()->addChild(mBullet,zOrder - 1);
			bulletList.pushBack(mBullet);
			mBullet->setPosition(this->getPosition());
		}
	}
	Bullet* rBullet		 = Bullet::create();
	rBullet->initWithType(RED_BULLET);
	//this ·É»ú  getParent() ÎªIngameLayer
	if (this->getParent())
	{
		int zOrder = this->getZOrder();
		this->getParent()->addChild(rBullet,zOrder - 1);
		bulletListRed.pushBack(rBullet);
		rBullet->setPosition(this->getPosition());
	}
}

void PlayFly::moveAllBullets()
{
		
		Bullet* rBullet	=	NULL;
		if (isEatBlueAward)
		{
			Bullet* mBullet	=	NULL;
			for (int i = bulletList.size() - 1 ; i >= 0 ; i--)
			{
			mBullet = bulletList.at(i);
			mBullet->move();
			if (mBullet->getPositionY() > winSize.height)
			{
				bulletList.eraseObject(mBullet);
			}
			}
		}
	
		for (int i = bulletListRed.size() - 1 ; i >= 0 ; i--)
		{
			rBullet = bulletListRed.at(i);
			rBullet->move();
			if (rBullet->getPositionY() > winSize.height)
			{
				bulletListRed.eraseObject(rBullet);
			}
		}
}

void PlayFly::setBlueAward(bool bl)
{
	 isEatBlueAward = bl; 
}

bool PlayFly::getBlueAward()const
{
	return isEatBlueAward;
}
