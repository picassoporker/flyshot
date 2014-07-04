#include "InGameLayer.h"
#include "SimpleAudioEngine.h"
#include "Layer/GameOver.h"
using namespace CocosDenshion;
USING_NS_CC;
int InGameLayer::score = 0;
InGameLayer::InGameLayer(void):		    mBackGround(NULL),
															mPlayFly(NULL),
															mBullet(NULL),
															enemyList(),
															winSize(),
															BigEnemycount(0),
															mAward(NULL),
															awardList(),
															scorettf(NULL)
{
}

InGameLayer::~InGameLayer(void)
{
}

bool InGameLayer::init()
{
	Layer::init();
	 winSize		=	Director::getInstance()->getVisibleSize();
	//创建背景
	mBackGround = BackGround::create();
	this->addChild(mBackGround,0);
	//创建飞机
	mPlayFly = PlayFly::create();
	this->addChild(mPlayFly,1);
	mPlayFly->setPosition(100,-100);
	//分数显示
	sprintf(chscore,"score:0");
	scorettf	=	LabelTTF::create(chscore,"WRYH",28);
	this->addChild(scorettf,4);
	scorettf->setPosition(winSize.width / 10 ,winSize.height - 10);
	scorettf->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	//创建子弹 debug:
	//*Bullet* mBullet = Bullet::create(BLUE_BULLET);
	//this->addChild(mBullet);
	//mBullet->setPosition(200,200);
	//使用initWithType创建子弹
	//mBullet = Bullet::create();
	//mBullet->initWithType(BLUE_BULLET);
	//this->addChild(mBullet);
	//mBullet->setPosition(mPlayFly->getPosition());
	return true;
}

Scene* InGameLayer::createScene()
{
	Scene* sc = Scene::create();
	InGameLayer* ly= InGameLayer::create();
	sc->addChild(ly);
	return sc;
}

void InGameLayer::gamestep(float dt)
{
	mBackGround->move();
	mPlayFly->move();
	mPlayFly->fire();
	mPlayFly->moveAllBullets();
	moveAllEnemy();
	enemyHitBullet();
	enemyHitFly();
	flyEatAward();
	for (int i = 0; i < awardList.size() ; i++)
	{
		awardList.at(i)->move();
	}
	sprintf(chscore,"score:%d",score);
	scorettf->setString(chscore);
}

void InGameLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	//背景音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/music_youngforyou.mp3",1);
	
	this->schedule(SEL_SCHEDULE(&InGameLayer::createEnemy),0.5f);
	this->schedule(SEL_SCHEDULE(&InGameLayer::createAward),(float)(CCRANDOM_0_1() * 20 + 30));
	this->schedule(SEL_SCHEDULE(&InGameLayer::gamestep),0.05f);
	FiniteTimeAction* ac	=	CallFunc::create(CC_CALLBACK_0(InGameLayer::SoundEffectCallBack,this));
	this->runAction(ac);
}

void InGameLayer::createEnemy(float dt)
{
	int enemyData[3][4]	=	{
											{1,1,4,0},	
											{2,2,7,1},
											{3,1,4,2}	
										};
	int index					=	CCRANDOM_0_1() * 3;
	EnemyFly* mEnemy	=	EnemyFly::create();
	this->addChild(mEnemy,1);
	if (index == 0||index	== 2||index	== 1 && BigEnemycount%2== 0)
	{
		BigEnemycount++;
		mEnemy->init(	enemyData[index][0],
								enemyData[index][1],
								enemyData[index][2],
								enemyData[index][3]);
	}
	float x				=	 CCRANDOM_0_1() * (winSize.width  -	mEnemy->getContentSize().width) +
								 mEnemy->getContentSize().width / 2;
	float y				=	winSize.height + mEnemy->getContentSize().height;
	mEnemy->setPosition(x,y);
	enemyList.pushBack(mEnemy);
}

void InGameLayer::moveAllEnemy()
{
	EnemyFly* mEnemy	=	NULL;
	for (int i = enemyList.size() - 1; i >= 0; i--)
	{
		mEnemy			=	enemyList.at(i);
		mEnemy->move();
		if(mEnemy->getPositionY() <=  -this->getContentSize().height)
			enemyList.erase(i);
	}
}

void InGameLayer::enemyHitBullet()
{
	EnemyFly* mEnemy					=	NULL;
	Vector<Bullet*>& mBulletList	=	mPlayFly->bulletListRed;
	if (mPlayFly->getBlueAward())
	{
		Vector<Bullet*>& bBulletList		=	mPlayFly->bulletList;
		Bullet* bBullet								=	NULL;
		for (int i = enemyList.size() - 1; i >= 0 ; i--)
		{
			mEnemy		=	enemyList.at(i);
			for (int k = bBulletList.size() - 1; k >= 0; k--)
			{
				bBullet	=	bBulletList.at(k);
				bool	res	=	mEnemy->hitTest(bBullet);
				if(res)
				{					
					//碰撞：飞机受伤，子弹消失。
					mEnemy->hurt(10.0f);
					SimpleAudioEngine::getInstance()->playEffect("music/enemy2_down.mp3");
					bBullet->removeFromParent();
					bBulletList.erase(k);
					//实时获取飞机的生命值并判断HP的状态。
					if(mEnemy->getIsDead() <= 0)
					{
						score += 120;
						enemyList.erase(i);
						break;
					}
				}
			}
		}
	}
	
	
	Bullet* mBullet							=	NULL;
	for (int i = enemyList.size() - 1; i >= 0 ; i--)
	{
		mEnemy		=	enemyList.at(i);
		for (int k = mBulletList.size() - 1; k >= 0; k--)
		{
			mBullet	=	mBulletList.at(k);
			bool	res	=	mEnemy->hitTest(mBullet);
			if(res)
			{
				
				//碰撞：飞机受伤，子弹消失。
				mEnemy->hurt(10.0f);
				SimpleAudioEngine::getInstance()->playEffect("music/enemy2_down.mp3");
				mBullet->removeFromParent();
				mBulletList.erase(k);
				//实时获取飞机的生命值并判断HP的状态。
				if(mEnemy->getIsDead() <= 0)
				{
					score += 120;
					enemyList.erase(i);
					break;
				}
			 }
		}
	}

}

void InGameLayer::enemyHitFly()
{
	EnemyFly* mEnenmy = NULL;
	for (int i = enemyList.size() - 1; i>=0; i--)
	{
		mEnenmy = enemyList.at(i);
		if (mPlayFly->getBoundingBox().intersectsRect(mEnenmy->getBoundingBox()))
		{
			//SimpleAudioEngine::getInstance()->playEffect("music/game_over.mp3");
			this->stopAllActions();
			this->unscheduleAllSelectors();
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
			Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.8f,GameOver::createScene()));
		}
	}
}

void InGameLayer::SoundEffectCallBack()
{
	//播放一次音效
	SimpleAudioEngine::getInstance()->playEffect("music/enemy2_out.mp3");
}

void InGameLayer::createAward(float dt)
{
	int	index		=  CCRANDOM_0_1() * 3 + 1;
	if (index == AWARD_BOMB)
	{
		createAward("enemy4_fly_1.png",index);
	}
	else if (index == AWARD_DOUBLEBULLET)
	{
		createAward("enemy5_fly_1.png",index);
	}
}

void InGameLayer::createAward(const std::string& file,int type)
{
	mAward	=	Award::create();
	mAward->initWithAward(file,type);
	float x				= CCRANDOM_0_1() * (winSize.width - mAward->getContentSize().width) + mAward->getContentSize().width / 2;
	float y				= winSize.height + mAward->getContentSize().height;
	this->addChild(mAward,1);
	mAward->setPosition(x,y);
	awardList.pushBack(mAward);
}

void InGameLayer::flyEatAward()
{
	Award* mAward = NULL;
	for (int i  = awardList.size() - 1; i >= 0  ; i --)
	{
		mAward	=	awardList.at(i);
		if (mPlayFly->getBoundingBox().intersectsRect(mAward->getBoundingBox()) )
		{
			if (mAward->getState() == AWARD_BOMB)
			{
				EnemyFly* mEnemy = NULL;
				for (int i = enemyList.size() -1 ; i >= 0 ; i--)
				{
					mEnemy = enemyList.at(i);
					mEnemy->stopAllActions();
					mEnemy->explode();
					score += 10;
					enemyList.erase(i);
				}
				mAward->destory();
				awardList.erase(i);
			}else if (mAward->getState()  == AWARD_DOUBLEBULLET)
			{
				mPlayFly->setBlueAward(true);
				mAward->destory();
				awardList.erase(i);
			}
		}
	}
}

int InGameLayer::getScore()
{
	return score;
}

void  InGameLayer::setScore(int num)
{
	score = num;
}