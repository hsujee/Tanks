//
//  AI.hpp
//  Tanks
//
//  Created by jerry on 16/7/8.
//
//

#ifndef AI_hpp
#define AI_hpp

#include <stdio.h>
#include "Common.h"
#include "TankEnemy.hpp"
#include "Bullet.hpp"

class AI : public Node{
public:
    CREATE_FUNC(AI);
    virtual bool init();
    void onExit();
    
    TMXTiledMap * getMap();
    
    //产生敌军坦克
    void createTank(float);
    bool _createFlag;
    Vector<TankEnemy *> _tankEnemyVector;
    Vector<Bullet *> _bulletVector;
    //让坦克移动
    void moveTank(float);
    //敌人发射子弹
    void shoot(float);
    //子弹碰撞事件监测
    void update(float);
    
};

#endif /* AI_hpp */
