#include "GameOver.h"
USING_NS_CC;

GameOver::GameOver(void)
{
}


GameOver::~GameOver(void)
{
}
bool GameOver::init()
{
	Layer::init();
	Size winSize = Director::getInstance()->getVisibleSize();
	Sprite* bg = Sprite::createWithSpriteFrameName("background_2.png");
	this->addChild(bg);
	bg->setAnchorPoint(Point::ZERO);
	Sprite* showScore = Sprite::create("BurstAircraftTopScores@2x.png");
	this->addChild(showScore);
	showScore->setPosition(winSize.width/2 ,winSize.height/2 + 50);
	int res = InGameLayer::getScore();
	char chres[100];
	sprintf(chres,"%d  ",res);
	LabelTTF* scorettf = LabelTTF::create(chres,"WRYH",48);
	this->addChild(scorettf);
	scorettf->setPosition(showScore->getPosition() - Point(0,50));

	//退出游戏按钮
	Sprite* closeSprite = Sprite::create("gameover.png");
	MenuItemSprite *closed = MenuItemSprite::create(closeSprite,NULL,NULL,
																			CC_CALLBACK_1(GameOver::closeGame,this));
	Menu* closeMenu = Menu::create(closed,NULL);
	this->addChild(closeMenu);
	closeMenu->setPosition(winSize.width*2/3,winSize.height/3);
	//重新开始游戏按钮
	Sprite* reStrart = Sprite::create("reStrart.png");
	MenuItemSprite *reStrartSprite = MenuItemSprite::create(reStrart,NULL,NULL,
																		CC_CALLBACK_1(GameOver::reStrartGame,this));
	Menu* reStrartMenu = Menu::create(reStrartSprite,NULL);
	this->addChild(reStrartMenu);
	reStrartMenu->setPosition(winSize.width/3,winSize.height/3);
	return true;
}
Scene* GameOver::createScene()
{
	auto sc = Scene::create();
	auto ly = GameOver::create();
	sc->addChild(ly);
	return sc;
}
void GameOver::closeGame(Ref* pSender)
{
	Director::getInstance()->end();	
}
void GameOver::reStrartGame(Ref* pSender)
{
	InGameLayer::setScore(0);
	Director::getInstance()->replaceScene(TransitionMoveInT::create(0.5f,InGameLayer::createScene()));
}
