//
//  Entity.h
//  cutfruit
//
//  Created by jiumiao on 15/10/3.
//
//

#ifndef __cutfruit__Entity__
#define __cutfruit__Entity__

#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;
class Entity:public Node
{
public:
    Entity();
    ~Entity();
    Sprite *getSprite();//获取精灵
    void bindSprite(Sprite*sprite);//绑定精灵
private:
    Sprite * m_sprite;//创建精灵对象
};
#endif /* defined(__cutfruit__Entity__) */
