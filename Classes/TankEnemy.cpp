//
//  TankEnemy.cpp
//  Tanks
//
//  Created by jerry on 16/7/8.
//
//

#include "TankEnemy.hpp"

bool TankEnemy::init(){
    if (!Sprite::initWithFile("armor2U.png")) {
        return false;
    }
    _tilesize = 0;
    _dir = Common::UP;
    
    this->setLocalZOrder(Common::ZO_TANK);
    turn(Common::DOWN);
    return true;
}