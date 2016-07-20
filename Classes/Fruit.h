//
//  Fruit.h
//  cutfruit
//
//  Created by jiumiao on 15/10/3.
//
//

#ifndef __cutfruit__Fruit__
#define __cutfruit__Fruit__

#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;
class Fruit:public Entity
{
public:
    CREATE_FUNC(Fruit);
    virtual bool init();
    bool IsCollideWithPoint(Point point);//获取碰撞坐标点
};
#endif /* defined(__cutfruit__Fruit__) */
