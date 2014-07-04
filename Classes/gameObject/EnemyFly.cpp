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
	//��¼���������
	typeNum = type;
	flyNum	=	fly;
	blowupNum = blowup;
	hitNum	=	hit;

	//��ʽ���л���ͷ�ļ�
	char chFileName[17];
	sprintf(chFileName,"enemy%d_fly_1.png",type);
	initWithSpriteFrameName(chFileName);   
	//SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(chFileName);
	//����֡
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
	//���涯��
	Animation* getAnimation = AnimationCache::getInstance()->getAnimation(head + mid);
	if (getAnimation != NULL)
	{
		//��������У���ô��������������һ�������ű���
		return getAnimation;
	}
	//���û�л��棬��ô���������ű�
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
		//���뵽�����У����������������ü�����һ��������һ��ָ��ָ���������
		//����CREATE�����Ķ�������new���������ڶ���
		AnimationCache::getInstance()->addAnimation(mAnimation,head + mid);
	}
	return mAnimation;
}

void EnemyFly::playActionWithType(int actionType ,bool loop, bool del)
{
	//����һ��strType ��¼�ɻ����в��ַ���
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

	char chHead[10];  //Ӧ��Ϊ7
	sprintf(chHead,"enemy%d",typeNum);
	string head(chHead);
	Animation* mAnimation	 = createAnimation(head,Mid,actionNum);
	//����������ھͲ��ţ�����ʲô������
	if (mAnimation)
	{
		Animate* mAnimate	 =  Animate::create(mAnimation);
		//�Ƴ�������
		RemoveSelf* self			 = RemoveSelf::create();
		//���϶���
		Sequence* seq				 =	Sequence::create(mAnimate,self,NULL);
		//�ж��Ƿ���Ҫѭ��
		if (loop) //����״̬
		{
			this->runAction(RepeatForever::create(mAnimate));
		}
		else if(loop == false && del)
		{
			//�������Ҫѭ���Ҷ�����Ҫ���ݻ٣���ֻѭ��һ�Σ�����ѭ���������Ƴ�������ը״̬
			this->runAction(seq);
		}
		else
		{
			//�������Ҫѭ������ֻѭ��һ�Σ�HURT��״̬
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
	//getBoundingBox() ����һ�����������
	//������������ײ
		return this->getBoundingBox().intersectsRect(hitNode->getBoundingBox());
	//����������ײ
	//return this->getBoundingBox().containsPoint(hitNode->getPosition());
}

float EnemyFly::getIsDead() const
{
	return hp;
}
