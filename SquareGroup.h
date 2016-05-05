//
//  SquareGroup.h
//  SquareClear
//
//  Created by 徐徐 on 15/10/18.
//  一组方块组成形状的类
//

#ifndef __SquareClear__SquareGroup__
#define __SquareClear__SquareGroup__

#include <stdio.h>
#include "Square.h"

typedef std::map<int,Square*> SquareMap;
typedef std::map<int,Square*>::iterator SquareMapIterator;
class SquareGroup : public Node
{
public:
    //方块组的类型，形状
    enum SQUAREGROUP_TYPE
    {
        ST_NONE = -1,
        ST_L,
        ST_L_TURN,
        ST_Z,
        ST_Z_TURN,
        ST_MAX
    };

	bool init();

	CREATE_FUNC(SquareGroup);

    void SetSquareGroup(int x,int y,SquareGroup::SQUAREGROUP_TYPE type,Square::SQUARE_COLOR color = Square::SC_BLACK);

    ~SquareGroup();

    //设置方块组的类型和颜色，默认黑色
    void SetGroupType(SQUAREGROUP_TYPE type, Square::SQUARE_COLOR color = Square::SC_BLACK);

    SQUAREGROUP_TYPE getGroupType(){return _groupType;}

    SquareMap* getGroupArray(){return m_groupArray;}

	void DrawGroup(int squareWidth,int squareHeight);

	void drawOneSquare(int squareWidth, int squareHeight,Square* sq);
    int GetX(){return m_x;}
    int GetY(){return m_y;}
    void SetXY(int x,int y){
        m_x = x;
        m_y = y;
    }
    static const int s_Width;
    static const int s_Height;
    
    
private:
    void CalcGroup(Square::SQUARE_COLOR color = Square::SC_BLACK);
    SquareMap *m_groupArray;
    SQUAREGROUP_TYPE _groupType;
    int m_x;
    int m_y;
	cocos2d::DrawNode * m_drawNode;
};
#endif /* defined(__SquareClear__SquareGroup__) */
