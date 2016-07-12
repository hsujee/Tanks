//
//  TankFriend.hpp
//  Tanks
//
//  Created by jerry on 16/7/6.
//
//

#ifndef TankFriend_hpp
#define TankFriend_hpp

#include <stdio.h>
#include "Common.h"
#include "Bullet.hpp"

class TankFriend : public Sprite{
public:
    CREATE_FUNC(TankFriend);
    virtual bool init();
    
    void setTileSize(int tilesize);
    int _tilesize;
    
    TMXTiledMap * getMap();
    bool canMove(Common::DIRECTION dir);
    void move(Common::DIRECTION dir);
    void doMove();
    //移动方向
    Common::DIRECTION _dir;
    
    void turn(Common::DIRECTION dir);
    Bullet * shoot();
};


#endif /* TankFriend_hpp */
