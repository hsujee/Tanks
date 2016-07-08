//
//  Common.h
//  Tanks
//
//  Created by jerry on 16/7/5.
//
//

#ifndef Common_h
#define Common_h

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
#define winSize Director::getInstance()->getWinSize()
#define TANK_SPEED 2
#define BULLET_SPEED 4

class Common{
public:
    //上下左右操作的枚举
    enum DIRECTION {UP, RIGHT, DOWN, LEFT, INVALID_DIR};
    enum TileType {NONE, BLOCK, STEEL, HOME};
    enum {ZO_LAYER_0 = 100, ZO_BULLET, ZO_TANK, ZO_LAYER_1};
    
    /** 根据Layer创建Scene */
    static Scene * createScene(Layer *layer){
        Scene *scene = Scene::create();
        scene->addChild(layer);
        return scene;
    }
    
    /** 格式化字符串 */
    static const char* formatT(int v, const char* prefix = "", const char* suffix = ""){
        static char buf[1024];
        sprintf(buf, "%s%d%s", prefix, v, suffix);
        return buf;
    }
    
    /** X移动Node */
    static void moveNodeX(Node *node, int dx){
        node->setPositionX(node->getPositionX()+dx);
    }
    
    /** Y移动Node */
    static void moveNodeY(Node *node, int dy){
        node->setPositionY(node->getPositionY()+dy);
    }
    
    /** 移动Node */
    static void moveNode(Node *node, Vec2 dv){
        node->setPosition(node->getPosition()+dv);
    }
    
    /** 将地图坐标转换成openGL坐标 */
    static const Vec2 Tile2PointLB(TMXTiledMap* map, Vec2 ptTile)
    {
        ptTile.y = map->getMapSize().height - 1 - ptTile.y;
        
        return Vec2(ptTile.x * map->getTileSize().width,
                   ptTile.y * map->getTileSize().height);
    }
    
    /** 将openGL坐标转换成地图坐标 */
    static Vec2 Point2Tile(TMXTiledMap* map, CCPoint ptMap)
    {
        int dx = map->getTileSize().width;
        int dy = map->getTileSize().height;
        
        int x = ptMap.x / dx;
        int y = ptMap.y / dy;
        y = map->getMapSize().height - 1 - y;
        
        
        return Vec2(x, y);
    }
    
    /** 获取瓦片的类型 */
    static TileType getTileType(int gid)
    {
        if (gid == 5 || gid == 6 || gid == 11 || gid == 12)
            return STEEL;
        if (gid == 13 || gid == 14 || gid == 19 || gid == 20)
            return BLOCK;
        if (gid == 17 || gid == 18 || gid == 23 || gid == 24)
            return HOME;
        
        return NONE;
    }
};

#endif /* Common_h */
