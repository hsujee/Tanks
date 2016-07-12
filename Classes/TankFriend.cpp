//
//  TankFriend.cpp
//  Tanks
//
//  Created by jerry on 16/7/6.
//
//

#include "TankFriend.hpp"

bool TankFriend::init(){
    if (!Sprite::initWithFile("armor3U.png")) {
        return false;
    }
    _tilesize = 0;
    _dir = Common::UP;
    
    this->setLocalZOrder(Common::ZO_TANK);
    
    return true;
}

void TankFriend::setTileSize(int tilesize){
    if (_tilesize == 0) {
        _tilesize = tilesize;
        setScale((tilesize*2-6) / getContentSize().width);
    }
}

TMXTiledMap *TankFriend::getMap(){
    return (TMXTiledMap *)this->getParent();
}

bool TankFriend::canMove(Common::DIRECTION dir){
    Vec2 vec[3];
    Rect rt = getBoundingBox();
    
    TMXTiledMap* tmxTiledMap = getMap();
    
    switch (dir) {
        case Common::UP:
            vec[0] = Vec2(rt.getMinX(), rt.getMaxY()+TANK_SPEED);
            vec[1] = Vec2(rt.getMidX(), rt.getMaxY()+TANK_SPEED);
            vec[2] = Vec2(rt.getMaxX(), rt.getMaxY()+TANK_SPEED);
            break;
        case Common::DOWN:
            vec[0] = Vec2(rt.getMinX(), rt.getMinY()-TANK_SPEED);
            vec[1] = Vec2(rt.getMidX(), rt.getMinY()-TANK_SPEED);
            vec[2] = Vec2(rt.getMaxX(), rt.getMinY()-TANK_SPEED);
            break;
        case Common::LEFT:
            vec[0] = Vec2(rt.getMinX()-TANK_SPEED, rt.getMaxY());
            vec[1] = Vec2(rt.getMinX()-TANK_SPEED, rt.getMidY());
            vec[2] = Vec2(rt.getMinX()-TANK_SPEED, rt.getMaxY());
            break;
        case Common::RIGHT:
            vec[0] = Vec2(rt.getMaxX()+TANK_SPEED, rt.getMinY());
            vec[1] = Vec2(rt.getMaxX()+TANK_SPEED, rt.getMidY());
            vec[2] = Vec2(rt.getMaxX()+TANK_SPEED, rt.getMaxY());
            break;
            
        default:
            break;
    }
    
    //
    Size sizeMap = tmxTiledMap->getContentSize();
    Rect rcMap = Rect(0, 0, sizeMap.width-1, sizeMap.height-1);
    
    for (int i = 0; i < 3; i++){
        //
        if (!rcMap.containsPoint(vec[i]))
            return false;
        
        //
        Vec2 ptTile = Common::Point2Tile(tmxTiledMap, vec[i]);
        int gid = tmxTiledMap->getLayer("layer_0")->getTileGIDAt(ptTile);
        Common::TileType tt = Common::getTileType(gid);
        //
        if (tt == Common::BLOCK || tt == Common::STEEL)
            return false;
    }
    
    return true;
}

void TankFriend::move(Common::DIRECTION dir){
    if (_dir != dir) {
        turn(dir);
    }
    
    if (!canMove(dir)) {
        return;
    }
    
    SimpleAudioEngine::getInstance()->playEffect("moving.wav");
    
    doMove();
}

void TankFriend::doMove(){
    switch (_dir) {
        case Common::UP:
            Common::moveNodeY(this, TANK_SPEED);
            break;
        case Common::DOWN:
            Common::moveNodeY(this, -TANK_SPEED);
            break;
        case Common::LEFT:
            Common::moveNodeX(this, -TANK_SPEED);
            break;
        case Common::RIGHT:
            Common::moveNodeX(this, TANK_SPEED);
            break;
            
        default:
            break;
    }
}

void TankFriend::turn(Common::DIRECTION dir){
    this->setRotation(dir*90);
    _dir = dir;
}

Bullet * TankFriend::shoot(){
    SimpleAudioEngine::getInstance()->playEffect("shoot.wav");
    
    Bullet *bullet = Bullet::create();
    bullet->setImage("bullet.png");
    
    getMap()->addChild(bullet);
    bullet->setPosition(getPosition());
    
    //子弹运动
    Vec2 ptDest;
    switch (_dir) {
        case Common::UP:
            ptDest = Vec2(0, winSize.height);
            break;
        case Common::DOWN:
            ptDest = Vec2(0, -winSize.height);
            break;
        case Common::LEFT:
            ptDest = Vec2(-winSize.width, 0);
            break;
        case Common::RIGHT:
            ptDest = Vec2(winSize.width, 0);
            break;
        default:
            break;
    }
    MoveBy *by = MoveBy::create(winSize.width/(BULLET_SPEED*60), ptDest);
    bullet->runAction(by);
    
    //设置子弹的威力
//    bullet->_demage = ...;
    return bullet;
}