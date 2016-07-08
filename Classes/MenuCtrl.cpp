//
//  MenuCtrl.cpp
//  Tanks
//
//  Created by jerry on 16/7/6.
//
//

#include "MenuCtrl.hpp"

bool MenuCtrl::init(){
    if (!Menu::init()) {
        return false;
    }
    
    schedule(schedule_selector(MenuCtrl::checkAction));
    
    return true;
}

void MenuCtrl::checkAction(float dt){
    if (this->_selectedItem && _state == Menu::State::TRACKING_TOUCH) {
        _selectedItem->activate();
    }
}

