#ifndef _ENEMY_FLY_H_
#define _ENEMY_FLY_H_
#include "cocos2d.h"
enum ENEMY_ACTION
{
	ENEMY_HURT	=	1, //之后改hit
	ENEMY_FLY,
	ENEMY_BLOWUP
};
class EnemyFly : public cocos2d::Sprite
{
public:
	EnemyFly(void);
	~EnemyFly(void);

	virtual bool init();
	CREATE_FUNC(EnemyFly);

public:
	//类型，飞行，爆炸，受伤
	void init(int type,int fly ,int blowup,int hit);  
	//敌机移动
	void move();
	//敌机爆炸
	void explode();
	//敌机受伤
	void hurt(float dmg);
	//敌机销毁
	void destory();
	//敌机与子弹碰撞检测
	bool hitTest(Node* hitNode);
	//获取当前的状态
	float getIsDead() const;

private:
	//创建动画
	cocos2d::Animation* createAnimation(const std::string& head,const std::string& mid,int num);
	//播放何种类型动画
	void playActionWithType(int actionType ,bool loop = false, bool del = false);

private:
	/*移动速度*/
	float vy;
	/*生命*/
	float hp;
	/*敌机类型*/
	int typeNum;
	/*飞行数字*/
	int flyNum;
	/*爆炸数字*/
	int blowupNum;
	/*受伤数字*/
	int hitNum;


};

#endif	//_ENEMY_FLY_H_
