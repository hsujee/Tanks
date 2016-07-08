//
//  Bullet.hpp
//  Tanks
//
//  Created by jerry on 16/7/7.
//
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "Common.h"

class Bullet : public Sprite{
public:
    CREATE_FUNC(Bullet);
    virtual bool init();
    
    void setImage(const char *filename);
    //杀伤力
    int _demage;
};

#endif /* Bullet_hpp */
