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
#include "AI.hpp"

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
    
    AI *_ai;
    
    //胜利条件
    int _vectoryCount;
    int _currCount;
    
    void timeOut(float);
    enum FAILURE_REASON{TIMEOUT, HOMEDESTROY, TANKDIE};
    void gameOver(FAILURE_REASON reason);
    
    //记录当前关卡
    int _index;
    //友军坦克生命
    int _life;
    bool _godMode;
    
    void unsetGodMode();
    
    int _nSoundId;
};
#endif /* LayerGame_hpp */