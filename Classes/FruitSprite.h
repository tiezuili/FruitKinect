//
//  FruitSprite.h
//  cutfruit
//
//  Created by jiumiao on 15/11/3.
//
//

#ifndef __cutfruit__FruitSprite__
#define __cutfruit__FruitSprite__

#include "cocos2d.h"
USING_NS_CC;
class FruitSprite: public Sprite
{
public:
    static FruitSprite *createFruit(int type,String name);
    virtual bool init();
    CREATE_FUNC(FruitSprite);
    CC_SYNTHESIZE(int, num, Num);
};
#endif /* defined(__cutfruit__FruitSprite__) */
