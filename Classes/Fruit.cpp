//
//  Fruit.cpp
//  cutfruit
//
//  Created by jiumiao on 15/10/3.
//
//

#include "Fruit.h"
bool Fruit::init()
{
    return true;
}
//获取切碎的水果坐标
bool Fruit::IsCollideWithPoint(Point point)
{
    Size spriteSize=getSprite()->getContentSize();
    Point entityPos=getPosition();
    Rect rec=CCRectMake(entityPos.x-spriteSize.width/2, entityPos.y-spriteSize.height/2, spriteSize.width, spriteSize.height);
    return rec.containsPoint(point);
}