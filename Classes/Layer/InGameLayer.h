#ifndef _INGAME_LAYER_H_
#define _INGAME_LAYER_H_
#include"cocos2d.h"
#include"gameObject/BackGround.h"
#include "gameObject/PlayFly.h"
#include "gameObject/Bullet.h"
#include "gameObject/EnemyFly.h"
#include "gameObject/Award.h"
class InGameLayer: public cocos2d::Layer
{
public:
	InGameLayer(void);
	~InGameLayer(void);
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	CREATE_FUNC(InGameLayer);

public:
	static cocos2d::Scene* createScene();
	static int getScore();
	static void setScore(int num);
private:
	void gamestep(float dt);
	void createEnemy(float dt);
	void moveAllEnemy();
	void enemyHitBullet();
	void enemyHitFly();
	void SoundEffectCallBack();
	void createAward(float dt);
	void createAward(const std::string& file,int type);
	void flyEatAward();
private:
	/*������*/
	BackGround* mBackGround;
	/*��ҷɻ�*/
	PlayFly* mPlayFly;
	/*�л�����*/
	cocos2d::Vector<EnemyFly*> enemyList;
	/*����ʾ�����С*/
	cocos2d::Size winSize;
	/*�ӵ�*/
	Bullet* mBullet ;
	/*��ɻ�5�����һ�Σ���һ������*/
	int BigEnemycount;
	/*����*/
	Award* mAward;
	/*��������*/
	cocos2d::Vector<Award*>awardList;
	/*����*/
	static int score;
	char chscore[100];
	cocos2d::LabelTTF* scorettf	;
};
#endif // !_INGAME_LAYER_H_

