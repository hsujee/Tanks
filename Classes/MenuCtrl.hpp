//
//  MenuCtrl.hpp
//  Tanks
//
//  Created by jerry on 16/7/6.
//
//

#ifndef MenuCtrl_hpp
#define MenuCtrl_hpp

#include <stdio.h>
#include "Common.h"

class MenuCtrl : public Menu{
public:
    CREATE_FUNC(MenuCtrl);
    virtual bool init();
    
    void checkAction(float dt);
};

#endif /* MenuCtrl_hpp */
