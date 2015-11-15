//
//  GamePlayLayer.h
//  SquareClear
//
//  Created by 徐徐 on 15/11/14.
//  游戏中的主要图层
//

#ifndef GamePlayLayer_h
#define GamePlayLayer_h

#include <stdio.h>
#include "cocos2d.h"
class GamePlayLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(GamePlayLayer);
    
    ~GamePlayLayer();
    virtual bool init() override;
    

    int m_gameBoardHeight;
    int m_gameBoardWidth;
    
protected:
    void drawSquare();
    
    //test 以后通过配置接口获得以下数据
    int m_squareHeight = 32;
    int m_squareWidth = 32;
    int m_squareRowCount = 20;
    int m_squareColumnCount = 20;
    
    
    //游戏板的位置
    //TODO
    int* m_BackgroundBoard;
    cocos2d::DrawNode * m_drawNode;
};
#endif /* GamePlayLayer_h */
