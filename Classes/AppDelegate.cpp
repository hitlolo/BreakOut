#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameController.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director

	setResouseSearchPath();
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Break out");
        director->setOpenGLView(glview);
		glview->setFrameSize(288, 512);
    }

    // turn on display FPS
    director->setDisplayStats(true);
	glview->setDesignResolutionSize(288, 512, ResolutionPolicy::SHOW_ALL);
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	GameController::getInstance()->goState(GAME_STATE::LOGO);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::setResouseSearchPath()
{
	std::vector<std::string> paths;
	paths.push_back("fonts");
	paths.push_back("images");
	paths.push_back("sounds");
	paths.push_back("ui");
	paths.push_back("res");
	FileUtils::getInstance()->setSearchPaths(paths);
}
