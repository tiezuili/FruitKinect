//
//  FruitManager.h
//  cutfruit
//
//  Created by jiumiao on 15/10/3.
//
//

#ifndef __cutfruit__FruitManager__
#define __cutfruit__FruitManager__

#include "cocos2d.h"
USING_NS_CC;
class FruitManager :public Node
{
public:
    FruitManager();
    virtual bool init();
    int score;
    CREATE_FUNC(FruitManager);
    Action *createAction(Point point);//水果的坐标管理
    Point pt;//坐标设置
    float angel;
    void setPt(Point p);//设置坐标点
    void setAngel(float ang);//角度
    void createFruit(float dt);
    Array *m_fruitArr;
    Array *m_fruitBrokenArr;
    Array *m_systemArr;
    void actionEnd(Node *sender);//动作结束处理
    void CollisionWithPoint(int tag);//切中后水果的坐标管理
    virtual void update(float dt);//执行计划任务
private:
    int notCutnum;//没有被切水果的数量
    void notCut();//没有被切的水果管理
    void gameOver();//游戏结束判断
};

#endif /* defined(__cutfruit__FruitManager__) */
