//
//  AI.cpp
//  Tanks
//
//  Created by jerry on 16/7/8.
//
//

#include "AI.hpp"

bool AI::init(){
    Node::init();
    _createFlag = false;
    //调度器创建坦克
    schedule(schedule_selector(AI::createTank), TANK_CREATE_INIERVAL);
    //调度器移动坦克
    schedule(schedule_selector(AI::moveTank));
    //调度起敌军坦克发射子弹
    schedule(schedule_selector(AI::shoot), TANK_SHOOT_INIERVAL);
    //碰撞检测
    scheduleUpdate();
    return true;
}

void AI::onExit(){
    Node::onExit();
    _tankEnemyVector.clear();
    _bulletVector.clear();
}

TMXTiledMap * AI::getMap(){
    return (TMXTiledMap *)getParent();
}

void AI::createTank(float){
    TankEnemy *tankEnemy = TankEnemy::create();
    //将敌军坦克添加到地图中去
    getMap()->addChild(tankEnemy);
    //设置格子大小
    tankEnemy->setTileSize(tankEnemy->getMap()->getTileSize().width);
    
    //设置位置
    _createFlag = !_createFlag;
    if (_createFlag) {
        tankEnemy->setPosition(Common::Tile2PointLB(getMap(), Vec2(1, 0)));
    }else{
        tankEnemy->setPosition(Common::Tile2PointLB(getMap(), Vec2(25, 0)));
    }
    //将坦克添加到数组
    _tankEnemyVector.pushBack(tankEnemy);
    
}

void AI::moveTank(float){
    //随机算法
    int dir = (int)(CCRANDOM_0_1()*4);
    
    //判断能否移动，不能随机调转方向
    for (int i=0; i<_tankEnemyVector.size(); i++) {
        TankEnemy *tank = _tankEnemyVector.at(i);
        if (tank->canMove(tank->_dir)) {
            tank->doMove();
        }else{
            tank->turn((Common::DIRECTION)dir);
        }
    }
    
}

void AI::shoot(float){
    Bullet * bullet;
    
    for (int i=0; i<_tankEnemyVector.size(); i++) {
        TankEnemy *tank = _tankEnemyVector.at(i);
        bullet = tank->shoot();
        _bulletVector.pushBack(bullet);
    }
}

void AI::update(float){
    Bullet::checkBullets(getMap(), _bulletVector);
}