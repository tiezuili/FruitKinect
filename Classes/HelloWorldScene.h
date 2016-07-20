#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
	void onEnter();
	void onExit();
	void kinectCallback(cocos2d::EventCustom * event);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    void loadScene(float dt);//加载场景
    void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * event);//键盘监听
};

#endif // __HELLOWORLD_SCENE_H__
