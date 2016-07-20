#include "HelloWorldScene.h"
#include "PrepareScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}
void HelloWorld::onEnter()
{
	Layer::onEnter();
	Director::getInstance()->getEventDispatcher()->addCustomEventListener("KinectData",CC_CALLBACK_1(HelloWorld::kinectCallback, this));  
    auto sh = SocketHelper::getInstance();//初始化Socket 
    //一次就够了
    std::string jsonStr ="{\"methodId\":100,\"argId\":1007,\"argName\":\"CloestHandData\"}";//生成初始化字符串
    sh->send(jsonStr);//发送初始化命令
}
void HelloWorld::onExit()
{
    Layer::onExit();
}
//回调
void HelloWorld::kinectCallback(cocos2d::EventCustom * event)
{
    //跳转Scene开始游戏
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("KinectData");//跳转之前先取消监听
	auto *scene=PrepareScene::scene();
    Director::getInstance()->replaceScene(scene);
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //添加背景图片
    auto sprite = Sprite::create("back.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale(1);
    this->addChild(sprite, 0);
    this->setKeyboardEnabled(true);
    //添加计划任务
    this->scheduleOnce(schedule_selector(HelloWorld::loadScene), 1.5);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (_TARGET_PLATFORM == _PLATFORM_WINRT) || (_TARGET_PLATFORM == _PLATFORM_WP8)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    Scene* scene = PrepareScene::scene();
    Director::sharedDirector()->replaceScene(scene);
#if (_TARGET_PLATFORM == _PLATFORM_IOS)
    exit(0);
#endif
#endif
}
void HelloWorld::loadScene(float dt)//加载场景
{
    auto *scene=PrepareScene::scene();
    Director::getInstance()->replaceScene(scene);
}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * event)//键盘监听
{
    if (keyCode==EventKeyboard::KeyCode::KEY_BACKSPACE) {
        Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
}

