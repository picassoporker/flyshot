#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include "cocos2d.h"
class BackGround: public cocos2d::Layer
{
public:
	BackGround(void);
	~BackGround(void);
	virtual bool init();
	CREATE_FUNC(BackGround);

public:
	void move();
private:
	float vy;
	float height;
	cocos2d::Sprite* bgOne;
	cocos2d::Sprite* bgTwo;
	cocos2d::Size winSize;
};

#endif //_BACKGROUND_H_
