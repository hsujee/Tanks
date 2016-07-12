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

void Bullet::checkBullets(TMXTiledMap * map, Vector<Bullet *> bullets){
    int count = bullets.size();
    Size szMap = map->getContentSize();
    Rect rcMap = Rect(0, 0, szMap.width-1, szMap.height-1);
    
    TMXLayer *layer = map->getLayer("layer_0");
    
    for (int i=count-1; i>=0; --i) {
        
        Bullet *b = bullets.at(i);
        Vec2 vb = b->getPosition();
        
        //判断子弹飞出
        if (!rcMap.containsPoint(vb)) {
            b->removeFromParent();
            bullets.eraseObject(b);
            continue;
        }
        //判断子弹碰到转头，铁块，大本营
        Vec2 ptTile = Common::Point2Tile(map, vb);
        int gid = layer->getTileGIDAt(ptTile);
        Common::TileType tt = Common::getTileType(gid);
        if (tt == Common::BLOCK) {
            SimpleAudioEngine::getInstance()->playEffect("brickhit.wav");
            b->removeFromParentAndCleanup(true);
            bullets.eraseObject(b);
            //转头被打爆
            layer->setTileGID(0, ptTile);
            continue;
        }else if(tt == Common::STEEL){
            SimpleAudioEngine::getInstance()->playEffect("steelhit.wav");
            b->removeFromParentAndCleanup(true);
            bullets.eraseObject(b);
            continue;
        }else if (tt == Common::HOME){
            SimpleAudioEngine::getInstance()->playEffect("gameover.wav");
            b->removeFromParentAndCleanup(true);
            bullets.eraseObject(b);
//            LayerGame::gameOver(LayerGame::HOMEDESTROY);
            continue;
        }
        
        
        //判断子弹碰到敌军子弹
        
        //判断子弹碰到敌军坦克
        
    }
}