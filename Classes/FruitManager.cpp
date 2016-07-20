//
//  FruitManager.cpp
//  cutfruit
//
//  Created by jiumiao on 15/10/3.
//
//

#include "FruitManager.h"
#include "Fruit.h"
#include "PrepareScene.h"
#include "GameStart.h"
#include "SimpleAudioEngine.h"
float t=0;
FruitManager::FruitManager()
{
    pt=Vec2(500,500);
    angel=0;
    notCutnum=0;
}
bool FruitManager::init()
{
    if (!Node::init()) {
        return false;
    }
    //加载水果纹理图片
    SpriteFrameCache *frame=SpriteFrameCache::sharedSpriteFrameCache();
    frame->addSpriteFramesWithFile("fruit.plist","fruit.png");
    m_fruitArr=Array::create();//创建完整水果数组对象
    m_fruitArr->retain();//释放内存
    m_fruitBrokenArr=Array::create();//创建切碎水果数组对象
    m_fruitBrokenArr->retain();
    ///添加分数
    auto labelscore=Label::createWithSystemFont("score:0", "", 35);
    labelscore->setTag(1000);
    labelscore->setPosition(100,360);
    labelscore->setColor(Color3B::YELLOW);
    this->score=0;
    this->addChild(labelscore);
    /////添加生命值
    auto s1=Sprite::create("detail_star.png");
    s1->setTag(1001);
    s1->setPosition(450,360);
    this->addChild(s1);
    auto s2=Sprite::create("detail_star.png");
    s2->setTag(1002);
    s2->setPosition(490,360);
    this->addChild(s2);
    auto s3=Sprite::create("detail_star.png");
    s3->setTag(1003);
    s3->setPosition(530,360);
    this->addChild(s3);
    auto s4=Sprite::create("detail_star.png");
    s4->setTag(1004);
    s4->setPosition(570,360);
    this->addChild(s4);
    auto s5=Sprite::create("detail_star.png");
    s5->setTag(1005);
    s5->setPosition(610,360);
    this->addChild(s5);
    //添加计划任务
    this->scheduleOnce(schedule_selector(FruitManager::createFruit), 2.0f);
    this->scheduleUpdate();
    //添加音效
    
//    Director::getInstance()->resume();
   
    return true;
}
 void FruitManager::update(float dt)//执行计划任务
{
    t+=dt;
    Ref *obj=NULL;
    Fruit *fruit=NULL;
    for (int i=0; i<m_fruitArr->count(); i++) {
        fruit=(Fruit *)m_fruitArr->objectAtIndex(i);
        //移除切碎的水果
        if (fruit->IsCollideWithPoint(pt)) {
            m_fruitArr->removeObject(fruit);
            CollisionWithPoint(fruit->getTag());
            this->removeChild(fruit);
        }
    }
    for (int i=0; i<m_fruitBrokenArr->count(); i++) {
        auto sp=(Sprite*)m_fruitBrokenArr->objectAtIndex(i);
        if (sp->getPositionY()<0) {
            m_fruitBrokenArr->removeObject(sp);
            this->removeChild(sp);
            continue;
        }
        if (sp->getTag()==6) {
            sp->setPositionX(sp->getPositionX()-2);
            sp->setPositionY(sp->getPositionY()-20*t*t);
        }
        if (sp->getTag()==7) {
            sp->setPositionX(sp->getPositionX()+2);
            sp->setPositionY(sp->getPositionY()-20*t*t);
        }
    }

}
//创建水果
 void FruitManager::createFruit(float dt)
{
    if (notCutnum>=5)
        return;
    Fruit*fruit=NULL;
    for (int i=0; i<=rand()%5; i++) {
        int index=rand()%5+1;
        fruit=Fruit::create();
        fruit->bindSprite(Sprite::createWithSpriteFrameName(String::createWithFormat("%d.png",index)->getCString()));
        fruit->setTag(index);
        Point p=Vec2(rand()%640,-50);//水果抛出的位置
        fruit->setPosition(p);
        this->addChild(fruit);
        //加入音效
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("throw.mp3");
        //添加到数组
        m_fruitArr->addObject(fruit);
        fruit->runAction(createAction(p));
    }
    
}
Action *FruitManager::createAction(Point point)//水果的坐标管理
{
    if (point.x<=320) {
        ActionInterval *jump=JumpTo::create(2.0f, Vec2(rand()%200+400, -20), 380.0f, 1);
        ActionInterval *rotate=RotateBy::create(2.0f,180.0f,180.0f);
        Spawn *jumpandrotate=Spawn::create(jump,rotate, NULL);
        CallFuncN *callfun=CallFuncN::create(this,callfuncN_selector(FruitManager::actionEnd));
        Sequence*action=Sequence::create(jumpandrotate,callfun, NULL);
        return action;
    }
    if (point.x>320) {
        ActionInterval *jump=JumpTo::create(2.0f, Vec2(rand()%100, -20), 380.0f, 1);
        CallFuncN *callfun=CallFuncN::create(this,callfuncN_selector(FruitManager::actionEnd));
         ActionInterval *rotate=RotateBy::create(2.0f,180.0f,180.0f);
        Spawn*jumpandrotate=Spawn::create(jump,rotate,NULL);
        Sequence*action=Sequence::create(jumpandrotate,callfun, NULL);
        return action;
    }
}

void FruitManager::actionEnd(Node *sender)//动作结束处理
{
    Sprite*sprite=(Sprite*)sender;
    if (sprite->getTag()==10) {
        Scene *scene=PrepareScene::scene();
        Director::getInstance()->replaceScene(scene);
    }
    this->removeChild(sprite);
    if (sprite->getTag()<6) {
        notCut();
        m_fruitArr->removeObject(sprite);
        if (m_fruitArr->count()==0) {
            createFruit(0.0f);
        }
        else this->removeChild(this->getChildByTag(9));
    }
}
void FruitManager::CollisionWithPoint(int tag)//切中后水果的坐标管理
{
    auto labelscore=(Label*)this->getChildByTag(1000);
    t=0;
    //创建切中后的水果
    Sprite*broken1=Sprite::createWithSpriteFrameName(String::createWithFormat("%d1.png",tag)->getCString());
     Sprite*broken2=Sprite::createWithSpriteFrameName(String::createWithFormat("%d2.png",tag)->getCString());
    Sprite *flash=Sprite::createWithSpriteFrameName("flash.png");
    //(500,500)位置
    flash->setPosition(pt);
    //设置角度
    flash->setRotation(180-angel);
    flash->setTag(8);
    broken1->setPosition(pt);
    broken1->setTag(6);
    broken1->setRotation(-angel);
    broken2->setPosition(pt);
    broken2->setTag(7);
    broken2->setRotation(-angel);
    this->addChild(broken1);
    this->addChild(broken2);
    this->addChild(flash);
   
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect ("splatter.mp3");
    //切中后水果的动作
    ActionInterval* rotate=RotateBy::create(0.3f, 90.0f, 0);
    CallFuncN *callfun=CallFuncN::create(this,callfuncN_selector(FruitManager::actionEnd));
    Sequence*action=Sequence::create(rotate,callfun,NULL);
    flash->runAction(action);
    score+=100;
    labelscore->setString(StringUtils::format("Score:%d",score));
    //将之添加到数组
    m_fruitBrokenArr->addObject(broken1);
    m_fruitBrokenArr->addObject(broken2);
    
    //添加粒子特效
	ParticleSystemQuad *system = ParticleSystemQuad::create("daoguang.plist");
    //system->initWithFile("daoguang.plist");
    system->setTexture(TextureCache::sharedTextureCache()->addImage("LavaFlow.plist.png"));
    system->setPosition(pt);
    system->setTag(9);
    this->addChild(system);
    //判断数组是否为空
    if (m_fruitArr->count()==0) {
        this->scheduleOnce(schedule_selector(FruitManager::createFruit), 2.0f);
    }
}
void FruitManager::notCut()//没有被切的水果管理
{
    auto l=(Sprite*)this->getChildByTag(1001);
    auto ll=(Sprite*)this->getChildByTag(1002);
    auto lll=(Sprite*)this->getChildByTag(1003);
    auto llll=(Sprite*)this->getChildByTag(1004);
    auto lllll=(Sprite*)this->getChildByTag(1005);
    notCutnum++;
    //没有切中水果显示第一种类型
    if (notCutnum==1) {
            auto  *xf=Sprite::create("xf.png");
            xf->setPosition(Vec2(560,450));
            this->addChild(xf);
            l->removeFromParent();
        }
    //没有切中水果显示第二种类型
    if (notCutnum==2) {
            Sprite* xf = Sprite::create("xf.png");
            Sprite* xxf = Sprite::create("xxf.png");
            xf->setPosition(Vec2(560,455));
            xxf->setPosition(Vec2(590,455));
            this->addChild(xf);
            this->addChild(xxf);
            ll->removeFromParent();
//            if (score>1000) {
//                auto sss=Sprite::create("detail_star.png");
//                this->addChild(sss);
//                sss->setPosition(490, 360);
//            }
//            score=0;
           
        }
        //没有切中水果显示第三种类型
        if (notCutnum==3) {
            Sprite* xf = Sprite::create("xf.png");
            Sprite* xxf = Sprite::create("xxf.png");
            Sprite* xxxf = Sprite::create("xxf.png");
            xf->setPosition(Vec2(560,455));
            xxf->setPosition(Vec2(590,455));
            xxxf->setPosition(Vec2(590,455));
            this->addChild(xf);
            this->addChild(xxf);
            this->addChild(xxxf);
           
            lll->removeFromParent();
            
            Director::getInstance()->resume();
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("over.mp3",true);
            //gameOver();
    }
    //没有切中水果显示第四种类型
    if (notCutnum==4) {
        Sprite* xf = Sprite::create("xf.png");
        Sprite* xxf = Sprite::create("xxf.png");
        Sprite* xxxf = Sprite::create("xxf.png");
        xf->setPosition(Vec2(560,455));
        xxf->setPosition(Vec2(590,455));
        xxxf->setPosition(Vec2(590,455));
        this->addChild(xf);
        this->addChild(xxf);
        this->addChild(xxxf);
        
       llll->removeFromParent();
        
        Director::getInstance()->resume();
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("over.mp3",true);
       // gameOver();
    }
    //没有切中水果显示第五种类型
    if (notCutnum==5) {
        Sprite* xf = Sprite::create("xf.png");
        Sprite* xxf = Sprite::create("xxf.png");
        Sprite* xxxf = Sprite::create("xxf.png");
        xf->setPosition(Vec2(560,455));
        xxf->setPosition(Vec2(590,455));
        xxxf->setPosition(Vec2(590,455));
        this->addChild(xf);
        this->addChild(xxf);
        this->addChild(xxxf);
        
        lllll->removeFromParent();
        
        Director::getInstance()->resume();
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("over.mp3",true);
        gameOver();
    }

    
}
void FruitManager::gameOver()//游戏结束判断
{
    auto gameover=Sprite::create("game-over.png");
    gameover->setPosition(Vec2(320,240));
    gameover->setTag(10);
    this->addChild(gameover);
    //执行缩放动作
    ActionInterval *scallelarge=ScaleTo::create(1.0f, 1.5f, 1.5f);
     ActionInterval *scallesmall=ScaleTo::create(1.0f, 0.5f, 0.5f);
    CallFuncN *callFun=CallFuncN::create(this,callfuncN_selector(FruitManager::actionEnd));
    ActionInterval *actions=Sequence::create(scallelarge,scallesmall,callFun, NULL);
    gameover->runAction(actions);
    
}
void FruitManager::setPt(Point p)//设置坐标点
{
    pt=p;
}
void FruitManager::setAngel(float ang)//角度
{
    angel=ang;
}