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

	//������
	//SpriteFrameCache::purgeSharedSpriteFrameCache(); �ƺ�������
	//������ͼƬ
	//SpriteFrameCache::removeSpriteFrameByName("background_2.png");
	//��������û�б��ù���ͼƬ
	//SpriteFrameCache::removeUnusedSpriteFrames();
	//ɾ��ָ����plist�ļ�
	//SpriteFrameCache::removeSpriteFramesFromFile("gameArts.plist");

	Sprite* bg	=	Sprite::createWithSpriteFrameName("background_2.png");
	this->addChild(bg);
	bg->setAnchorPoint(Point::ZERO);

	//����Logo
	logo = Sprite::create("BurstAircraftLogo.png");
	this->addChild(logo,1);
	logo->setPosition(winSize.width / 2,winSize.height  + 100);

	LabelTTF* ttfStartGame = LabelTTF::create("PLAY GAME","",55);
	MenuItemLabel* itemStart = MenuItemLabel::create(ttfStartGame,CC_CALLBACK_1(WelcomeLayer::menuCallBack,this));
	Menu* startMenu = Menu::create(itemStart,NULL);
	this->addChild(startMenu,13);
	startMenu->setPosition(winSize.width / 2,winSize.height /2 );
	//���ö���
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
	//����͸����Ϊ0
	logo->setOpacity(50);
	//��ɫ�Ӻ�ɫ����ɫ
	//logo->setOpacityModifyRGB(true);
	//ת�Ƕ�
	RotateTo* mRotateTo = RotateTo::create(3.0,0);
	//RotateTo* mRotateTo = RotateTo::create(3.0,180,50);  X,Y��ת���ٶ�

	//���ж���һ����
	Spawn* mSpawn = Spawn::create(mMoveBy,mFadeIn,mRotateTo,NULL);
	//���ж�����������
	Sequence* seq = Sequence::create(mMoveBy,mFadeIn,mRotateTo,NULL);
	logo->runAction(seq);
}
void WelcomeLayer::menuCallBack(cocos2d::Ref* sender)
{
	Director::getInstance()->replaceScene(TransitionFadeTR::create(0.5f,InGameLayer::createScene()));
}


