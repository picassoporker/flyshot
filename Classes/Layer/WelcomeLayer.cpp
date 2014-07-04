#include "WelcomeLayer.h"
#include "InGameLayer.h"
USING_NS_CC;

WelcomeLayer::WelcomeLayer(void)
{
}


WelcomeLayer::~WelcomeLayer(void)
{
}

bool WelcomeLayer::init()
{
	Layer::init();
	Size winSize = Director::getInstance()->getVisibleSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameArts.plist");

	//清理缓存
	//SpriteFrameCache::purgeSharedSpriteFrameCache(); 似乎被弃用
	//清理单张图片
	//SpriteFrameCache::removeSpriteFrameByName("background_2.png");
	//清理缓存中没有被用过的图片
	//SpriteFrameCache::removeUnusedSpriteFrames();
	//删除指定的plist文件
	//SpriteFrameCache::removeSpriteFramesFromFile("gameArts.plist");

	Sprite* bg	=	Sprite::createWithSpriteFrameName("background_2.png");
	this->addChild(bg);
	bg->setAnchorPoint(Point::ZERO);

	//加载Logo
	logo = Sprite::create("BurstAircraftLogo.png");
	this->addChild(logo,1);
	logo->setPosition(winSize.width / 2,winSize.height  + 100);

	LabelTTF* ttfStartGame = LabelTTF::create("PLAY GAME","",55);
	MenuItemLabel* itemStart = MenuItemLabel::create(ttfStartGame,CC_CALLBACK_1(WelcomeLayer::menuCallBack,this));
	Menu* startMenu = Menu::create(itemStart,NULL);
	this->addChild(startMenu,13);
	startMenu->setPosition(winSize.width / 2,winSize.height /2 );
	//调用动画
	logoAction();
	return true;
}

Scene* WelcomeLayer::createScene()
{
	Scene* sc						= Scene::create();
	WelcomeLayer* ly		= WelcomeLayer::create();
	sc->addChild(ly);
	return sc;
}

void WelcomeLayer::logoAction()
{
	MoveBy* mMoveBy = MoveBy::create(1.0f,Point(0,-200));
	FadeIn* mFadeIn = FadeIn::create(1.0f);
	//设置透明度为0
	logo->setOpacity(50);
	//颜色从黑色到显色
	//logo->setOpacityModifyRGB(true);
	//转角度
	RotateTo* mRotateTo = RotateTo::create(3.0,0);
	//RotateTo* mRotateTo = RotateTo::create(3.0,180,50);  X,Y各转多少度

	//所有动作一起发生
	Spawn* mSpawn = Spawn::create(mMoveBy,mFadeIn,mRotateTo,NULL);
	//所有动作挨个发生
	Sequence* seq = Sequence::create(mMoveBy,mFadeIn,mRotateTo,NULL);
	logo->runAction(seq);
}
void WelcomeLayer::menuCallBack(cocos2d::Ref* sender)
{
	Director::getInstance()->replaceScene(TransitionFadeTR::create(0.5f,InGameLayer::createScene()));
}


