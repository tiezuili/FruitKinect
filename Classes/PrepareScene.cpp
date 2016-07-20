//
//  PrepareScene.cpp
//  cutfruit
//
//  Created by jiumiao on 15/10/1.
//
//

#include "PrepareScene.h"
#include "HelloWorldScene.h"
#include "GameStart.h"
#include "SimpleAudioEngine.h"
#include "SocketHelper.h"
using namespace CocosDenshion;
float ti=0;//初始化全局变量
Scene *PrepareScene::scene()
{
    auto scene=Scene::create();
    auto layer=PrepareScene::create();
    scene->addChild(layer);
    return scene;
}
bool PrepareScene::init()
{
	//auto point=Vec2(100,100);
	
    if (!Layer::init()) {
        return false;
    }
	streak->setTag(101);
    m_fruitBrokArr = Array::create();//创建容器
    m_fruitBrokArr->retain();//释放容器
    size=Director::getInstance()->getWinSize();
    //添加背景图片
    auto backsp=Sprite::create("background.jpg");
    backsp->setPosition(Vec2(size.width/2, size.height/2));
    this->addChild(backsp,-1);
    //定义事件侦听
//    auto *touchListener=EventListenerTouchOneByOne::create();
//    touchListener->onTouchBegan=[=](Touch *touch,Event *event){
//
//        return true;
//    };
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    //1定义侦听对象
    auto listener=EventListenerTouchOneByOne::create();
    //2绑定侦听对象的回调函数
    listener->onTouchBegan=CC_CALLBACK_2(PrepareScene::onTouchBegan, this);
    listener->onTouchMoved=CC_CALLBACK_2(PrepareScene::onTouchMoved, this);
    listener->onTouchEnded=CC_CALLBACK_2(PrepareScene::onTouchEnded, this);
    //3.将侦听添加到事件分发器中
    Director::getInstance()->getEventDispatcher()
    ->addEventListenerWithSceneGraphPriority(listener, this);
    //开启键盘
    this->setKeyboardEnabled(true);
    //加载logo
    loadlogo();
    //执行计划任务
    this->scheduleUpdate();
   
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("start.mp3");
    
    return true;
}
void PrepareScene:: onKeyReleased(EventKeyboard::KeyCode keyCode,Event *event)
{
    if (keyCode==EventKeyboard::KeyCode::KEY_BACKSPACE) {
        auto * scene = HelloWorld::createScene();
        Director::getInstance()->replaceScene(scene);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
}
PrepareScene::PrepareScene()//添加构造函数
{
    index=0;
    angel=0;
    ifstart=false;
    pt=Vec2(500,500);
	//添加刀
    streak=MotionStreak::create(0.5f, 4.0f, 10.0f, Color3B(250, 100, 200),"knife2.png");
	streak->setTag(100);
    this->addChild(streak,2);
}
void PrepareScene::onEnter()
{
	Layer::onEnter();
	Director::getInstance()->getEventDispatcher()->addCustomEventListener("KinectData",CC_CALLBACK_1(PrepareScene::kinectCallback, this));  
}
void PrepareScene::onExit()
{
    Layer::onExit();	
}
//回调
void PrepareScene::kinectCallback(cocos2d::EventCustom * event)
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
    pt=next1;
    if (index>1) {
        index=0;     
    }
    _point[index++]=next1;
    //设置拖尾图形的角度
    angel=atan((_point[0].y-_point[1].y)/(_point[0].x-_point[1].x))*180/3.14;  
	//跳转之前先取消监听
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("KinectData");
    //跳转Scene开始游戏   
	this->unscheduleUpdate();
    this->cleanup();//从节点移除
    Scene *scene=GameStart::scene();
    TransitionCrossFade * pTranslateScene = TransitionCrossFade::create(0.5f,scene);
    Director::getInstance()->replaceScene(pTranslateScene);
}
bool PrepareScene::onTouchBegan(Touch *touch, Event *unused_event)
{
    Point point=touch->getLocation();
    _point[index++]=point;
    streak->setPosition(point);
    return true;
}
void PrepareScene::onTouchMoved(Touch *touch, Event *unused_event)
{
    Point point=touch->getLocation();
    streak->setPosition(point);
    pt=point;
    if (index>1) {
        index=0;     
    }
    _point[index++]=point;
    //设置拖尾图形的角度
    angel=atan((_point[0].y-_point[1].y)/(_point[0].x-_point[1].x))*180/3.14;   
}
void PrepareScene::onTouchEnded(Touch *touch, Event *unused_event)
{
    pt=Vec2(500,500);
}
//加载logo
void PrepareScene::loadlogo()
{
    ActionInterval* move = MoveTo::create(0.4f,Vec2(size.width/2,400));
    ActionInterval *action=EaseOut::create(move,2.0f);
    CallFunc *callfun=CallFunc::create(this,callfunc_selector(PrepareScene::loadtitle));
    Sequence* seque=Sequence::create(action,callfun, NULL);
    auto sprite=Sprite::create("home-mask.png");
    sprite->setPosition(Vec2(size.width/2,500));
    this->addChild(sprite);
    sprite->runAction(seque);
    
    auto splgo=Sprite::create("logo.png");
    splgo->setPosition(Vec2(150,500));
    this->addChild(splgo);
    ActionInterval *move2=MoveTo::create(0.4f, Vec2(160,410));
    ActionInterval *action2=EaseOut::create(move2, 3.0f);
    splgo->runAction(action2);
    
}
//加载标题
void PrepareScene::loadtitle()
{
    Sprite* title=Sprite::create("ninja.png");
    title->setPosition(Vec2(480,400));
    this->addChild(title);
    ActionInterval*jump=JumpTo::create(0.8f,Vec2(480, 400), 20.0f, 2);
    ActionInterval*action=EaseOut::create(jump,2.0f);
    CallFunc *callfun=CallFunc::create(this,callfunc_selector(PrepareScene::loadmenu));
    Sequence* sque=Sequence::create(action,callfun, NULL);
    title->runAction(sque);   
    auto title2=Sprite::create("home-desc.png");
    title2->setPosition(Vec2(-80,300));
    this->addChild(title2);
    ActionInterval *action2=MoveTo::create(0.5f, Vec2(100,300));
    title2->runAction(action2);
}
//加载菜单
void PrepareScene::loadmenu()
{
    Sprite* scle1_dojo = Sprite::create("dojo.png");
    Sprite* scle2_new = Sprite::create("new-game.png");
    Sprite* scle3_quit = Sprite::create("quit.png");
    Sprite* peach = Sprite::create("peach.png");
    Sprite* sandia = Sprite::create("sandia.png");
    Sprite* boom = Sprite::create("boom.png");
    
    scle1_dojo->setPosition(Vec2(120,180));
    scle1_dojo->setTag(1);
    scle2_new->setPosition(Vec2(350,180));
    scle2_new->setTag(2);
    scle3_quit->setPosition(Vec2(550,130));
    scle3_quit->setTag(3);
    peach->setPosition(Vec2(120,180));
    peach->setTag(4);
    sandia->setPosition(Vec2(350,180));
    sandia->setTag(5);
    boom->setPosition(Vec2(550,130));
    boom->setTag(6);
    
    this->addChild(scle1_dojo);
    this->addChild(scle2_new);
    this->addChild(scle3_quit);
    this->addChild(peach);
    this->addChild(sandia);
    this->addChild(boom);
    
    //旋转角度
    scle1_rotate();
    scle2_rotate();
    scle3_rotate();
    peach_rotate();
    sandia_rotate();
    boom_rotate();
    
    ifstart=true;
}

void PrepareScene::scle1_rotate()
{
    RotateBy *rotate=RotateBy::create(9.0f, 360.0f, 360.0f);
    CallFunc *callfun=CallFunc::create(this,callfunc_selector(PrepareScene::scle1_rotate));
    Sequence*seque=Sequence::create(rotate,callfun, NULL);
    this->getChildByTag(1)->runAction(seque);
}
void PrepareScene::scle2_rotate()
{
    RotateBy *rotate=RotateBy::create(12.0f, -360.0f, -360.0f);
    CallFunc *callfun=CallFunc::create(this,callfunc_selector(PrepareScene::scle2_rotate));
    Sequence*seque=Sequence::create(rotate,callfun, NULL);
    this->getChildByTag(2)->runAction(seque);

}
void PrepareScene::scle3_rotate()
{
    RotateBy *rotate=RotateBy::create(15.0f, 360.0f, 360.0f);
    CallFunc *callfun=CallFunc::create(this,callfunc_selector(PrepareScene::scle3_rotate));
    Sequence*seque=Sequence::create(rotate,callfun, NULL);
    this->getChildByTag(3)->runAction(seque);

}
void PrepareScene::peach_rotate()
{
    RotateBy *rotate=RotateBy::create(7.0f, -360.0f, -360.0f);
    CallFunc *callfun=CallFunc::create(this,callfunc_selector(PrepareScene::peach_rotate));
    Sequence*seque=Sequence::create(rotate,callfun, NULL);
    this->getChildByTag(4)->runAction(seque);

}
void PrepareScene::sandia_rotate()
{
    
    RotateBy *rotate=RotateBy::create(7.0f, 360.0f, 360.0f);
    CallFunc *callfun=CallFunc::create(this,callfunc_selector(PrepareScene::sandia_rotate));
    Sequence*seque=Sequence::create(rotate,callfun, NULL);
    this->getChildByTag(5)->runAction(seque);

}
void PrepareScene::boom_rotate()
{
    RotateBy *rotate=RotateBy::create(12.0f, -360.0f, -360.0f);
    CallFunc *callfun=CallFunc::create(this,callfunc_selector(PrepareScene::boom_rotate));
    Sequence*seque=Sequence::create(rotate,callfun, NULL);
    this->getChildByTag(6)->runAction(seque);

}
//计划任务方法
void PrepareScene::update(float delta)
{
    ti+=delta;
    if (ifstart&&ifColli(5,pt)){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect ("splatter.mp3");
        Colli(5);
    }
    if (ifstart&&ifColli(6,pt)){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect ("splatter.mp3");
        Colli(6);
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                exit(0);
            #endif
    }
    for (int i=0; i<m_fruitBrokArr->count(); i++) {
        Sprite *sp=(Sprite *)m_fruitBrokArr->objectAtIndex(i);
        if (sp->getTag()==7) {
            sp->setPositionX(sp->getPositionX()-3);
            sp->setPositionY(sp->getPositionY()-(15*ti+10*ti*ti));
        }
        if (sp->getTag()==8) {
            sp->setPositionX(sp->getPositionX()+3);
            sp->setPositionY(sp->getPositionY()-(15*ti+10*ti*ti));
        }
    }
}
//加载游戏
void PrepareScene::loadGame()
{
    this->unscheduleUpdate();
    this->cleanup();//从节点移除
    Scene *scene=GameStart::scene();
    TransitionCrossFade * pTranslateScene = TransitionCrossFade::create(0.5f,scene);
    Director::getInstance()->replaceScene(pTranslateScene);
}
bool PrepareScene::ifColli(int tag,Point point)//获取触摸后的水果和水果位置
{
    Size spriteSize=this->getChildByTag(tag)->getContentSize();
    Point entiyPos=this->getChildByTag(tag)->getPosition();
    Rect rec=CCRectMake(entiyPos.x-spriteSize.width/2,entiyPos.y-spriteSize.height/2,
                     spriteSize.width,spriteSize.height);
    return rec.containsPoint(point);
}
//获取水果
void PrepareScene::Colli(int tag)
{
    ifstart=false;
    this->removeChild(this->getChildByTag(tag));
	//切后的
    Sprite*sp1=Sprite::create("51.png");
    Sprite*sp2=Sprite::create("52.png");
    Sprite*sp3=Sprite::create("flash.png");
    sp1->setPosition(Vec2(350,180));
    sp1->setRotation(angel);
    sp2->setPosition(Vec2(350,180));
    sp2->setRotation(angel);
    sp3->setPosition(Vec2(350,180));
    sp3->setRotation(angel);
    sp1->setTag(7);
    sp2->setTag(8);
    sp3->setTag(9);
    this->addChild(sp1);
    this->addChild(sp2);
    this->addChild(sp3);
    //设置旋转角度
    ActionInterval *rotate=RotateBy::create(0.5f, 90.0f, 0);
    CallFunc *callfun=CallFunc::create(this,callfunc_selector(PrepareScene::loadGame));
    Sequence *action=Sequence::create(rotate,callfun,NULL);
    sp3->runAction(action);
    m_fruitBrokArr->addObject(sp1);//将对象sp1添加到数组
    m_fruitBrokArr->addObject(sp2);//将对象sp2添加到数组
    ti=0;
}
//绘画方法
//void PrepareScene::mydraw()
//{
//    cCommad.init(_globalZOrder);
//    cCommad.func = CC_CALLBACK_0(PrepareScene::mydraw, this);
//  // Director::getInstance()->getRenderer()->addCommnad(&cCommad);
//    
//}
void PrepareScene::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
    Node::draw(renderer,transform,flags);
    mdd_customCommand.init(1.0f);
    mdd_customCommand.func = CC_CALLBACK_0(PrepareScene::onDraw, this, transform, flags);
    renderer->addCommand(&mdd_customCommand);
}

void PrepareScene::onDraw(const Mat4 &transform, uint32_t flags )
{
}