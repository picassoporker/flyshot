#ifndef _PLAY_FLY_H_
#define _PLAY_FLY_H_
#include "cocos2d.h"
#include "gameObject/Bullet.h"
class PlayFly : public cocos2d::Sprite
{
public:
	PlayFly(void);
	~PlayFly(void);
	virtual bool init();
	virtual bool onTouchBegan(cocos2d::Touch* touch ,cocos2d::Event* evt);
	virtual void onTouchMoved(cocos2d::Touch* touch ,cocos2d::Event* evt);
	CREATE_FUNC(PlayFly);

public:
	void addEvents();
	void destory();
	void move(); 
	void fire();
	void moveAllBullets();
	void setBlueAward(bool bl);
	bool getBlueAward()const;
private:
	cocos2d::Size winSize;
	cocos2d::Point curTouchPos;
	const int LIMIT_SPEED;
	bool isTouchFly;
	float offset;
	bool isEatBlueAward;
public:
	cocos2d::Vector<Bullet*> bulletList;
	cocos2d::Vector<Bullet*> bulletListRed;
};

#endif //_PLAY_FLY_H_
