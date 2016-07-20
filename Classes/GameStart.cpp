//
//  GameStart.cpp
//  cutfruit
//
//  Created by jiumiao on 15/10/2.
//
//

#include "GameStart.h"
#include "PrepareScene.h"
#include <math.h>
#include "SimpleAudioEngine.h"

 Scene *GameStart::scene()
{
    auto *scene=Scene::create();
    auto *layer=GameStart::create();
    scene->addChild(layer);
    return scene;
}
 void GameStart::onEnter()
{
	Layer::onEnter();
	Director::getInstance()->getEventDispatcher()->addCustomEventListener("KinectData",CC_CALLBACK_1(GameStart::kinectCallback, this));  
}
void GameStart::onExit()
{
    Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("KinectData");
}
//回调
void GameStart::kinectCallback(cocos2d::EventCustom * event)
{
    auto vecMap =*static_cast<std::map<std::string,Vec3> *>(event->getUserData());
    auto pos = vecMap["nearstHand"];   
	auto vecPre = Vec2(this->getChildByTag(101)->getPositionX(),this->getChildByTag(101)->getPositionY());
    auto vecNow = Vec2(pos.x,pos.y);
	auto offset1=Vec2(vecPre-vecNow);
	auto next1=this->getChildByTag(101)->getPosition()-offset1;
	this->getChildByTag(101)->setPosition(next1);
	if (next1.x>=630)
	{
		next1.x=630;
	}
	if (next1.x<=10)
	{
		next1.x=10;
	}
	if (next1.y<=10)
	{
		next1.y=10;
	}
	if (next1.y>=470)
	{
		next1.y=470;
	}
	this->getChildByTag(101)->setPosition(next1);
	fruitmanager->setPt(next1);
    if (index>1) {
        index=0;
    }
    //设置水果管理中旋转的角度
    _point[index++]=next1;
    float ang = atan((_point[0].y-_point[1].y)/(_point[0].x-_point[1].x))*180/3.14;
    fruitmanager->setAngel(ang);  
}
bool GameStart::init()
{
    if (!Layer::init()) {
        return false;
    }
    //Director::getInstance()->releaWse();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("menu.mp3",true);
    size=Director::getInstance()->getWinSize();
    //加载背景图片
    auto background=Sprite::create("background.jpg");
    background->setPosition(Vec2(size.width/2,size.height/2));
    this->addChild(background);
    auto * x = Sprite::create("x.png");
    auto * xx = Sprite::create("xx.png");
    auto * xxx = Sprite::create("xxx.png");   
    x->setPosition(Vec2(560,455));
    xx->setPosition(Vec2(590,455));
    xxx->setPosition(Vec2(620,455));  
    this->addChild(x);
    this->addChild(xx);
    this->addChild(xxx);   
    //1定义侦听对象
    auto listener=EventListenerTouchOneByOne::create();
    //2绑定侦听对象的回调函数
    listener->onTouchBegan=CC_CALLBACK_2(GameStart::onTouchBegan, this);
    listener->onTouchMoved=CC_CALLBACK_2(GameStart::onTouchMoved, this);
    listener->onTouchEnded=CC_CALLBACK_2(GameStart::onTouchEnded, this);
    //3.将侦听添加到事件分发器中
    Director::getInstance()->getEventDispatcher()
    ->addEventListenerWithSceneGraphPriority(listener, this);
    //4,开启触摸监听
    this->setKeyboardEnabled(true);
    //5.加载水果
    loadfruitmanager();
    return true;
}
bool GameStart::onTouchBegan(Touch *touch, Event *unused_event)
{
    //初始点
    Point point=touch->getLocation();
    kinifecolor->setPosition(point);
    kinifecolor->setVisible(true);
    _point[index++]=point;
    return true;
}
void GameStart::onTouchMoved(Touch *touch, Event *unused_event)
{
    Point point=touch->getLocation();
    streak->setPosition(point);  
    //触摸调用水果管理中的方法
    fruitmanager->setPt(point);
    if (index>1) {
        index=0;
    }
    //设置水果管理中旋转的角度
    _point[index++]=point;
    float ang = atan((_point[0].y-_point[1].y)/(_point[0].x-_point[1].x))*180/3.14;
    fruitmanager->setAngel(ang);   
}
void GameStart::onTouchEnded(Touch *touch, Event *unused_event)
{
    kinifecolor->setVisible(false);
    kinifecolor->setPosition(Vec2(500,500));
    //设置管理水果类的坐标
    fruitmanager->setPt(Vec2(500, 500));
    index=0;
}

GameStart::GameStart()
{
    index=0;
    num=0;
    streak=MotionStreak::create(0.5f, 4.0f,10.0f, Color3B(250, 50, 200), "knife.png");
	streak->setTag(101);
	streak->setPosition(Vec2(100,100));
    this->addChild(streak,2);
    //添加粒子
	kinifecolor = ParticleSystemQuad::create("watermelon_splurt.plist");
    //kinifecolor->initWithFile("watermelon_splurt.plist");
    kinifecolor->setTexture(TextureCache::sharedTextureCache()->addImage("5color.plist.png"));
    this->addChild(kinifecolor,2);
    kinifecolor->setVisible(true);
}
void GameStart::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * event)//键盘监听
{
    this->cleanup();
    Scene *scene=PrepareScene::scene();
    Director::getInstance()->replaceScene(scene);
    }
//跳转到水果管理界面
void GameStart::loadfruitmanager()
{
    fruitmanager=FruitManager::create();
    this->addChild(fruitmanager);
}