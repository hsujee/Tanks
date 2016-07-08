//
//  LayerStart.cpp
//  Tanks
//
//  Created by jerry on 16/7/5.
//
//

#include "LayerStart.hpp"
#include "LayerMenu.hpp"

bool LayerStart::init(){
    if (!Layer::init()) {
        return false;
    }
    //添加开始界面背景图片
    Sprite *bg = Sprite::create("ScenceStart.png");
    bg->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->addChild(bg);
    
    //添加一个开始按钮
    MenuItemImage *item = MenuItemImage::create("playgameNormal.png", "playgameClose.png", CC_CALLBACK_1(LayerStart::startGame, this));
    Menu *menu = Menu::createWithItem(item);
    menu->setPositionY(menu->getPositionY() - 50);
    addChild(menu);
    return true;
}

void LayerStart::startGame(Ref *pSender){
    Director::getInstance()->replaceScene(Common::createScene(LayerMenu::create()));
}