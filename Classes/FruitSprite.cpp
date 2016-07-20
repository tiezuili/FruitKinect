//
//  FruitSprite.cpp
//  cutfruit
//
//  Created by jiumiao on 15/11/3.
//
//

#include "FruitSprite.h"
bool FruitSprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    this->num=0;
    return true;
}
//重写精灵创建方法
FruitSprite *FruitSprite::createFruit(int type,String name)
{
    FruitSprite *ret=FruitSprite::create();
    ret->initWithSpriteFrameName(name.getCString());
    ret->setNum(type);
    return ret;
}

