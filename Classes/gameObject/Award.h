#ifndef _AWARD_H_
#define _AWARD_H_
#include "cocos2d.h"
enum AWARD_PRISE
{
	AWARD_BOMB	= 2,
	AWARD_DOUBLEBULLET
};
class Award : public cocos2d::Sprite
{
public:
	Award(void);
	~Award(void);
	virtual bool init();
	CREATE_FUNC(Award);

public:
	void move();
	void initWithAward(const std::string& file,int type);
	void destory();
	int getState()const;

private:
	float vy;
	int curState;
};

#endif // !_AWARD_H_
