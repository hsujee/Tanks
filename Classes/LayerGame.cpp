//
//  LayerGame.cpp
//  Tanks
//
//  Created by jerry on 16/7/6.
//
//

#include "LayerGame.hpp"
#include "MenuCtrl.hpp"
#include "Bullet.hpp"

LayerGame * LayerGame::create(unsigned int index){
    LayerGame *Ref = new LayerGame;
    if (Ref && Ref->init(index)) {
        Ref->autorelease();
    }else{
        delete Ref;
        Ref = NULL;
    }
    
    return Ref;
}

bool LayerGame::init(unsigned int index){
    if (!Layer::init()) {
        return false;
    }
    
    _nSoundId = SimpleAudioEngine::getInstance()->playEffect("levelstarting.wav");
    
    _map = TMXTiledMap::create(Common::formatT(index+1, "Round", ".tmx"));
    //剧中显示
    Common::moveNode(_map, Vec2((winSize.width - _map->getContentSize().width)/2, (winSize.height - _map->getContentSize().height)/2));
    addChild(_map);
    
    //设置层的ZORDER
    _map->getLayer("layer_0")->setLocalZOrder(Common::ZO_LAYER_0);
    _map->getLayer("layer_1")->setLocalZOrder(Common::ZO_LAYER_1);
    
    //友军坦克和战友
    _tankFriend = TankFriend::create();
    _tankFriend->setTileSize(_map->getTileSize().width);
    _tankFriend->setPosition(Common::Tile2PointLB(_map, Vec2(10, 24)));
    _map->addChild(_tankFriend);
    
    //创建移动方向键
    MenuCtrl *menuCtrl = MenuCtrl::create();
    
    MenuItemImage *topItem = MenuItemImage::create("top.png", "top_press.png", CC_CALLBACK_1(LayerGame::DirCtrlPress, this));
    MenuItemImage *buttomItem = MenuItemImage::create("buttom.png", "buttom_press.png", CC_CALLBACK_1(LayerGame::DirCtrlPress, this));
    MenuItemImage *leftItem = MenuItemImage::create("left.png", "left_press.png", CC_CALLBACK_1(LayerGame::DirCtrlPress, this));
    MenuItemImage *rightItem = MenuItemImage::create("right.png", "right_press.png", CC_CALLBACK_1(LayerGame::DirCtrlPress, this));
    
    menuCtrl->addChild(topItem);
    menuCtrl->addChild(buttomItem);
    menuCtrl->addChild(leftItem);
    menuCtrl->addChild(rightItem);
    
    topItem->setTag(Common::UP);
    buttomItem->setTag(Common::DOWN);
    leftItem->setTag(Common::LEFT);
    rightItem->setTag(Common::RIGHT);
    
    Vec2 centerVec = Vec2(-200, -100);
    int dixt = 60;
    
    topItem->setPosition(centerVec.x, centerVec.y+dixt);
    buttomItem->setPosition(centerVec.x, centerVec.y-dixt);
    leftItem->setPosition(centerVec.x-dixt, centerVec.y);
    rightItem->setPosition(centerVec.x+dixt, centerVec.y);
    
    addChild(menuCtrl);
    
    //创建发射按钮
    Menu *menuShoot = Menu::create();
    MenuItemImage *itemShoot = MenuItemImage::create("fire.png", "fire_press.png", CC_CALLBACK_1(LayerGame::shoot, this));
    menuShoot->addChild(itemShoot);
    itemShoot->setPosition(-centerVec.x, centerVec.y);
    
    addChild(menuShoot);
    
    //做碰撞监测
    scheduleUpdate();
    //创建AI对象
    
    
    
    return true;
}

void LayerGame::DirCtrlPress(Ref *pSender){
    MenuItem *item = (MenuItem *)pSender;
    Common::DIRECTION dir = (Common::DIRECTION)item->getTag();
    _tankFriend->move(dir);
}

void LayerGame::shoot(Ref *pSender){
    Bullet *bullet = _tankFriend->shoot();
    _bulletVec.pushBack(bullet);
}

void LayerGame::update(float dt){
//    SimpleAudioEngine::getInstance()->playEffect("nmoving.wav");
    int count = _bulletVec.size();
    Size szMap = _map->getContentSize();
    Rect rcMap = Rect(0, 0, szMap.width-1, szMap.height-1);
    
    TMXLayer *layer = _map->getLayer("layer_0");
    
    for (int i=count-1; i>=0; --i) {
        
        Bullet *b = _bulletVec.at(i);
        Vec2 vb = b->getPosition();
        
        //判断子弹飞出
        if (!rcMap.containsPoint(vb)) {
            b->removeFromParentAndCleanup(true);
            _bulletVec.eraseObject(b);
            continue;
        }
        //判断子弹碰到转头，铁块，大本营
        Vec2 ptTile = Common::Point2Tile(_map, vb);
        int gid = layer->getTileGIDAt(ptTile);
        Common::TileType tt = Common::getTileType(gid);
        if (tt == Common::BLOCK) {
            SimpleAudioEngine::getInstance()->playEffect("brickhit.wav");
            b->removeFromParentAndCleanup(true);
            _bulletVec.eraseObject(b);
            //转头被打爆
            layer->setTileGID(0, ptTile);
            continue;
        }else if(tt == Common::STEEL){
            SimpleAudioEngine::getInstance()->playEffect("steelhit.wav");
            b->removeFromParentAndCleanup(true);
            _bulletVec.eraseObject(b);
            continue;
        }else if (tt == Common::HOME){
            SimpleAudioEngine::getInstance()->playEffect("gameover.wav");
            b->removeFromParentAndCleanup(true);
            _bulletVec.eraseObject(b);
//            Director::getInstance()->replaceScene(<#cocos2d::Scene *scene#>)
            continue;
        }
        
        
        //判断子弹碰到敌军子弹
        
        //判断子弹碰到敌军坦克
        
    }
}

void LayerGame::onExit(){
    Layer::onExit();
    _bulletVec.clear();
}