//
//  LayerStart.hpp
//  Tanks
//
//  Created by jerry on 16/7/5.
//
//

#ifndef LayerStart_hpp
#define LayerStart_hpp

#include <stdio.h>
#include "Common.h"

class LayerStart : public Layer{
public:
    CREATE_FUNC(LayerStart);
    virtual bool init();
    
    void startGame(Ref *pSender);
};

#endif /* LayerStart_hpp */
