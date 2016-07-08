//
//  LayerMenu.hpp
//  Tanks
//
//  Created by jerry on 16/7/6.
//
//

#ifndef LayerMenu_hpp
#define LayerMenu_hpp

#include <stdio.h>
#include "Common.h"

class LayerMenu : public Layer{
public:
    CREATE_FUNC(LayerMenu);
    virtual bool init();
    
    void toggle(Ref *pSender);
    void start(Ref *pSender);
    
    unsigned int _index;
};

#endif /* LayerMenu_hpp */
