
#ifndef __cutfruit__GameLayer__
#define __cutfruit__GameLayer__

#include "cocos2d.h"
#include "FruitSprite.h"
USING_NS_CC;
//定义水果结构体
//struct FRUIT
//{
//    int num;//水果数量
//    int score;//获取分数
//    String fruitImage;
//    String cutImage[2];
//};
class GameLayer : public Layer
{
    virtual bool init();
    CREATE_FUNC(GameLayer);
    //声明计划任务，既定时器
    void update(float dt) override;
    //利用定时器抛水果函数
    void throwFruit();
    void throwFruitX();

};
#endif /* defined(__cutfruit__GameLayer__) */
