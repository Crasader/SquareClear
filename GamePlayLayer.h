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
class SquareGroup;
class Square;
class GamePlayLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(GamePlayLayer);
    
    ~GamePlayLayer();
    virtual bool init() override;
    

    int m_gameBoardHeight;
    int m_gameBoardWidth;
	static cocos2d::Vec2 s_squareSize;
protected:
    void drawSquare();
    void drawSquareGroup(SquareGroup* sg,int x,int y);
    void drawOneSquare(int x,int y,Square* sq);
	
    int m_squareRowCount = 20;
    int m_squareColumnCount = 20;
    
    
    //游戏板的位置
    //TODO
    int* m_BackgroundBoard;
    cocos2d::DrawNode * m_drawNode;
};
#endif /* GamePlayLayer_h */
