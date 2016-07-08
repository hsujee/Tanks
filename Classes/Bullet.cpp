//
//  Bullet.cpp
//  Tanks
//
//  Created by jerry on 16/7/7.
//
//

#include "Bullet.hpp"

bool Bullet::init(){
    if (!Sprite::init()) {
        return false;
    }
    this->setLocalZOrder(Common::ZO_BULLET);
    return true;
}

void Bullet::setImage(const char *filename){
    this->setTexture(filename);
}