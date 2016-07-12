//
//  TankEnemy.hpp
//  Tanks
//
//  Created by jerry on 16/7/8.
//
//

#ifndef TankEnemy_hpp
#define TankEnemy_hpp

#include <stdio.h>
#include "Common.h"
#include "TankFriend.hpp"

class TankEnemy : public TankFriend{
public:
    CREATE_FUNC(TankEnemy);
    virtual bool init();
};

#endif /* TankEnemy_hpp */
