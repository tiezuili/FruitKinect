//
//  Entity.cpp
//  cutfruit
//
//  Created by jiumiao on 15/10/3.
//
//

#include "Entity.h"
Entity::Entity()
{
    m_sprite=NULL;
}
Entity::~Entity()
{
    
}

Sprite *Entity::getSprite()//获取精灵
{
    return this->m_sprite;
}
void Entity::bindSprite(Sprite*sprite)//绑定精灵
{
    this->m_sprite=sprite;
    this->addChild(m_sprite);
}