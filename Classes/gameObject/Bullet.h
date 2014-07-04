#ifndef _BULLET_H_
#define _BULLET_H_
#include "cocos2d.h"
enum BULLET_TYPE
{
	RED_BULLET = 1,
	BLUE_BULLET
};
class Bullet: public cocos2d::Sprite
{
public:
	Bullet(void);
	//Bullet(BULLET_TYPE type);

	~Bullet(void);
	virtual bool init();
	CREATE_FUNC(Bullet);
public:
	//static Bullet*  create(BULLET_TYPE type);
	void initWithType(BULLET_TYPE type);
	void move();
private:
	int type;
	float vx;
	float vy;
	cocos2d::Size winSize;
public:
	float offset;
};

#endif //_BULLET_H_
