#ifndef _WELCOME_LYAER_H_
#define _WELCOME_LYAER_H_
#include "cocos2d.h"
class WelcomeLayer: public cocos2d::Layer
{
public:
	WelcomeLayer(void);
	~WelcomeLayer(void);
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);
	static cocos2d::Scene* createScene();
private:
	void logoAction();
	void menuCallBack(cocos2d::Ref* sender);
private:
	cocos2d::Sprite* logo;
};
#endif // !_WELCOME_LYAER_H_

