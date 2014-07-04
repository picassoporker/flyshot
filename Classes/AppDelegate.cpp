#include "AppDelegate.h"
#include "Layer/WelcomeLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director

    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    if(!glview) {
#ifdef _WIN32
		glview = GLView::createWithRect("My Game",Rect(0,0,320,480));
#else
		//获取屏幕分辨率
		auto screen	=	glview->getFrameSize();
		glview = GLView::createWithRect("My Game",Rect(0,0,screen.width,screen.height));
#endif // _WIN32
        director->setOpenGLView(glview);
    }
	glview->setDesignResolutionSize(320,568,ResolutionPolicy::EXACT_FIT);

#if  COCOS2D_DEBUG > 0
    // turn on display FPS
    director->setDisplayStats(true);
#endif // COCOS2D_DEBUG > 0

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = WelcomeLayer::createScene();

    // run
    director->runWithScene(scene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
   SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
     SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
