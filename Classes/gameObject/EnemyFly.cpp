#include "EnemyFly.h"
USING_NS_CC;
using namespace std;

EnemyFly::EnemyFly(void) :	vy(0),
												hp(0),
												typeNum(0),
												flyNum(0),
												blowupNum(0),
												hitNum(0)
												
{
}


EnemyFly::~EnemyFly(void)
{
	
}
bool EnemyFly::init()
{
	Sprite::init();
	return true;
}
/*
	type,fly,blowup,hit
	enemy1 1,1,4,0
	enemy2 2,2,7,1
	enemy3 3,1,4,2
*/
void EnemyFly::init(int type,int fly ,int blowup,int hit)
{
	//记录传入的类型
	typeNum = type;
	flyNum	=	fly;
	blowupNum = blowup;
	hitNum	=	hit;

	//格式化敌机类头文件
	char chFileName[17];
	sprintf(chFileName,"enemy%d_fly_1.png",type);
	initWithSpriteFrameName(chFileName);   
	//SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(chFileName);
	//缓存帧
	if(type == 2)
	{
		vy			=	CCRANDOM_0_1() * 2 + 2.0;
		hp			=	60;
	}
	else if(type == 3)
	{
		vy			=	CCRANDOM_0_1() * 2 + 4.0;
		hp			=	30;
	}
	else if(type == 1)
	{
		vy			=	CCRANDOM_0_1() * 2 + 5.5;
		hp			=	20;
	}
	playActionWithType(ENEMY_FLY,true);
}

Animation* EnemyFly::createAnimation(const std::string& head,const std::string& mid,int num)
{
	//缓存动画
	Animation* getAnimation = AnimationCache::getInstance()->getAnimation(head + mid);
	if (getAnimation != NULL)
	{
		//如果里面有，那么跳出函数，返回一个动作脚本。
		return getAnimation;
	}
	//如果没有缓存，那么创建动作脚本
	Vector<SpriteFrame*>actionList;
	SpriteFrame* frame = NULL;
	char chMid[14]; 
	for (int i = 1;i <= num; i++)
	{
		sprintf(chMid,mid.c_str(),i);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(head + chMid);
		actionList.pushBack(frame);
	}
	Animation* mAnimation = NULL;
	if (num > 0 )
	{
		mAnimation = Animation::createWithSpriteFrames(actionList,0.2f);
		//加入到缓存中，动画缓存起来引用计数加一。用另外一个指针指向这个对象
		//所有CREATE出来的东西都是new出来，放在堆中
		AnimationCache::getInstance()->addAnimation(mAnimation,head + mid);
	}
	return mAnimation;
}

void EnemyFly::playActionWithType(int actionType ,bool loop, bool del)
{
	//声明一个strType 记录飞机的中部字符串
	string Mid = "";
	//
	int actionNum = 0 ;
	if(actionType == ENEMY_HURT)
	{
		Mid		=	"_hit_%d.png";
		actionNum	=	hitNum;
	}
	else if(actionType == ENEMY_FLY)
	{
		Mid		=	"_fly_%d.png";
		actionNum	=	flyNum;
	}
	else if(actionType == ENEMY_BLOWUP) 
	{
		Mid		=	"_blowup_%d.png";
		actionNum	=	blowupNum;
	}

	char chHead[10];  //应该为7
	sprintf(chHead,"enemy%d",typeNum);
	string head(chHead);
	Animation* mAnimation	 = createAnimation(head,Mid,actionNum);
	//如果动画存在就播放，否则什么都不做
	if (mAnimation)
	{
		Animate* mAnimate	 =  Animate::create(mAnimation);
		//移除它自身
		RemoveSelf* self			 = RemoveSelf::create();
		//整合动画
		Sequence* seq				 =	Sequence::create(mAnimate,self,NULL);
		//判断是否需要循环
		if (loop) //飞行状态
		{
			this->runAction(RepeatForever::create(mAnimate));
		}
		else if(loop == false && del)
		{
			//如果不需要循环且对象需要被摧毁，就只循环一次，并且循环结束后移除自身，爆炸状态
			this->runAction(seq);
		}
		else
		{
			//如果不需要循环，就只循环一次，HURT的状态
			this->runAction(mAnimate);
		}
	}
}

void EnemyFly::move()
{
	float y		=	this->getPositionY() - vy;
	this->setPositionY(y);
	if(y <= -this->getContentSize().height)
		destory();
}

void EnemyFly::explode()
{
	 playActionWithType(ENEMY_BLOWUP,false,true);
}

void EnemyFly::hurt(float dmg)
{
	hp	-=	dmg;
	playActionWithType(ENEMY_HURT);
	if (hp <= 0)
	{
		this->stopAllActions();
		explode();
	}
}

void EnemyFly::destory()
{
	this->removeFromParent();
}

bool EnemyFly::hitTest(Node* hitNode)
{
	//getBoundingBox() 返回一个区域的描述
	//区域对区域的碰撞
		return this->getBoundingBox().intersectsRect(hitNode->getBoundingBox());
	//点对区域的碰撞
	//return this->getBoundingBox().containsPoint(hitNode->getPosition());
}

float EnemyFly::getIsDead() const
{
	return hp;
}
