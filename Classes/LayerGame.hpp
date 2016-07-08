//
//  LayerGame.hpp
//  Tanks
//
//  Created by jerry on 16/7/6.
//
//

#ifndef LayerGame_hpp
#define LayerGame_hpp

#include <stdio.h>
#include "TankFriend.hpp"
#include "Common.h"

class LayerGame : public Layer{
public:
    static LayerGame * create(unsigned int index);
    virtual bool init(unsigned int index);
    //方向控制按钮按下动作回调
    void DirCtrlPress(Ref *pSender);
    //射击回调
    void shoot(Ref *pSender);
    void update(float dt);
    void onExit();
    
    TMXTiledMap *_map;
    TankFriend *_tankFriend;
    Vector<Bullet *> _bulletVec;
    
    int _nSoundId;
};
#endif /* LayerGame_hpp */