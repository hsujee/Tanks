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
#include "LayerMenu.hpp"

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
    
    _index = index;
    
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/bonus.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/brickhit.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/eexplosion.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/gameover.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/ice.wav");
    
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/levelstarting.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/life.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/moving.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/nmoving.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/pause.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/shieldhit.wav");
    
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/shoot.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/steelhit.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("sounds/tbonushit.wav");
    
    SimpleAudioEngine::getInstance()->playEffect("sounds/levelstarting.wav");
    
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
    //超时监测
    schedule(schedule_selector(LayerGame::timeOut), TIME_OVER);
    //做碰撞监测
    scheduleUpdate();
    //创建AI对象
    _ai = AI::create();
    _map->addChild(_ai);
    
    _vectoryCount = 10;
    _currCount = 0;
    
    _life = 3;
    _godMode = false;
    
    //预加载爆炸动画
    Vector<SpriteFrame *> frames;
    SpriteFrameCache *cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("blast.plist");
    for (int i=1; i<=8; ++i) {
        SpriteFrame *frame = cache->getSpriteFrameByName(Common::formatT(i, "blast", ".gif"));
        frames.pushBack(frame);
    }
    
    Animation *anim = Animation::createWithSpriteFrames(frames, 0.1f);
    AnimationCache::getInstance()->addAnimation(anim, TANK_BOMD);
    
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
    Bullet::checkBullets(_map, _bulletVec);
    
    //友军坦克被击中监测
    int count = _ai->_bulletVector.size();
    
    for (int i=count - 1; i>=0; --i) {
        Bullet *b = _ai->_bulletVector.at(i);
        if (b->getBoundingBox().intersectsRect(_tankFriend->getBoundingBox())) {
            b->removeFromParentAndCleanup(true);
            _ai->_bulletVector.eraseObject(b);
            
            if (!_godMode) {
                if (_life == 1) {
                    gameOver(TANKDIE);
                }else{
                    --_life;
                    _godMode = true;
                    
                    Blink *blink = Blink::create(5, 10);
                    CallFunc *func = CallFunc::create(CC_CALLBACK_0(LayerGame::unsetGodMode, this));
                    runAction(Sequence::create(blink, func, NULL));
                    
                }
            }
            
        }
    }
    
    //友军子弹射中敌军坦克
    count = _bulletVec.size();
    
    for (int i=count - 1; i>=0; --i) {
        Bullet *bullet = _bulletVec.at(i);
        int enemyCount = _ai->_tankEnemyVector.size();
        for (int j=enemyCount - 1; j>=0; --j) {
            TankEnemy *enemy = _ai->_tankEnemyVector.at(j);
            //判断敌军坦克和友军子弹矩阵相交
            if (enemy->getBoundingBox().intersectsRect(bullet->getBoundingBox())) {
                //移除敌军坦克
//                enemy->removeFromParentAndCleanup(true);
                _ai->_tankEnemyVector.eraseObject(enemy);
                //坦克爆炸
                Animate *anim = Animate::create(AnimationCache::getInstance()->getAnimation(TANK_BOMD));
                CallFunc *callFunc = CallFunc::create(CC_CALLBACK_0(TankEnemy::removeFromParent, enemy));
                
                Sequence *seq = Sequence::create(anim, callFunc, NULL);
                enemy->runAction(seq);
                
                //移除子弹
                bullet->removeFromParentAndCleanup(true);
                _bulletVec.eraseObject(bullet);
                
                //更新状态
                ++_currCount;
                if (_currCount == _vectoryCount) {
                    if (_index == 19) {
                        Director::getInstance()->replaceScene(Common::createScene(LayerMenu::create()));
                    }else{
                        Director::getInstance()->replaceScene(Common::createScene(LayerGame::create(_index + 1)));
                    }
                    
                }
                
                break;
            }
        }
    }
    
}

void LayerGame::onExit(){
    Layer::onExit();
    _bulletVec.clear();
}

void LayerGame::timeOut(float){
    log("time out");
    gameOver(FAILURE_REASON::TIMEOUT);
}

void LayerGame::gameOver(FAILURE_REASON reason){
    Director::getInstance()->replaceScene(Common::createScene(LayerMenu::create()));
}

void LayerGame::unsetGodMode(){
    
}