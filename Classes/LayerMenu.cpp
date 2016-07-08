//
//  LayerMenu.cpp
//  Tanks
//
//  Created by jerry on 16/7/6.
//
//

#include "LayerMenu.hpp"
#include "LayerGame.hpp"

bool LayerMenu::init(){
    if (!Layer::init()) {
        return false;
    }
    
    _index = 0;
    
    //先创建子菜单
    Vector<MenuItem *> menuVec;
    for (int i=1; i<=20; i++) {
        MenuItemFont * menuItem = MenuItemFont::create(Common::formatT(i, "Round"));
        menuVec.pushBack(menuItem);
    }
    
    MenuItemToggle * itemToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LayerMenu::toggle, this), menuVec);
    
    MenuItemFont * go = MenuItemFont::create("GO", CC_CALLBACK_1(LayerMenu::start, this));
    
    Menu * menu = Menu::create(itemToggle, go, NULL);
    menu->alignItemsVerticallyWithPadding(10);
    addChild(menu);
    return true;
}

void LayerMenu::toggle(Ref *pSender){
    MenuItemToggle * toggle = (MenuItemToggle *)pSender;
    _index = toggle->getSelectedIndex();
}

void LayerMenu::start(Ref *pSender){
    //将选择结果传递过来
    Director::getInstance()->replaceScene(Common::createScene(LayerGame::create(_index)));
}