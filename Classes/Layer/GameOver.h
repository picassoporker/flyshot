#ifndef _GAMEOVER_H_
#define  _GAMEVOER_H_
#include "cocos2d.h"
#include "InGameLayer.h"
class GameOver : public cocos2d::Layer
{
public:
	GameOver(void);
	~GameOver(void);
	virtual bool init();
	CREATE_FUNC(GameOver);

public:
	static cocos2d::Scene* createScene();
	void closeGame(Ref* pSender);
	void reStrartGame(Ref* pSender);
};
#endif // !_GAMEOVER_H_

