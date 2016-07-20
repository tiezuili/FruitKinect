//
//  GameStart.h
//  cutfruit
//
//  Created by jiumiao on 15/10/2.
//
//

#ifndef __cutfruit__GameStart__
#define __cutfruit__GameStart__

#include "cocos2d.h"
#include "FruitManager.h"
USING_NS_CC;
class GameStart:public Layer
{
public:
	void onEnter();
	void onExit();
	void kinectCallback(cocos2d::EventCustom * event);
    GameStart();
    virtual bool init();
    static Scene *scene();
    CREATE_FUNC(GameStart);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * event);//键盘监听
    Size size;
    Point _point[2];
    int index;//保存数组的下标
    int num;//保存水果的数量
    ParticleSystemQuad *kinifecolor;//创建粒子系统对象
    MotionStreak *streak;//创建拖尾效果对象
    FruitManager *fruitmanager;//创建水果管理对象
    void loadfruitmanager();//加载水果管理的方法
};

#endif /* defined(__cutfruit__GameStart__) */
