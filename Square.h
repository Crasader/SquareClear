//
//  Square.hpp
//  SquareClear
//
//  Created by 徐徐 on 15/11/14.
//  单个方块类，包含方块的颜色和坐标信息
//

#ifndef Square_h
#define Square_h

#include "cocos2d.h"
#include <stdio.h>
USING_NS_CC;
Color4F const s_squareColor[] =
{
    Color4F(1,0,0,1),
    Color4F(0,1,0,1),
    Color4F(0,0,1,1),
    Color4F(0,0,0,1),
    Color4F(1,1,1,1)
//    0xFF0000,
//    0x00FF00,
//    0x0000FF,
//    0x000000,
//    0xFFFFFF
};

class Square
{
public:
    //方块的颜色枚举
    enum SQUARE_COLOR
    {
        SC_NONE = -1,   //没有颜色
        SC_RED = 0,     //红
        SC_GREEN,
        SC_BLUE,
        SC_BLACK,
        SC_WHITE,
        //SC_OTHER,       //自定义颜色
        SC_MAX
    };
    Square()
    {
        _x = -1;
        _y = -1;
        _colorIndex = SC_NONE;
        _color4F = Color4F(0,0,0,0);
    }
    ~Square(){};
    Square(int x,int y,SQUARE_COLOR color,float alpha = 1)
    {
        _x = x;
        _y = y;
        _colorIndex = color;
        _color4F = s_squareColor[_colorIndex];
        _color4F.a = alpha;
    }
	void setXYIndex(int x_index, int y_index)
	{
		_x = x_index;
		_y = y_index;
	}
    int GetX()
    {
        return _x;
    }
    int GetY()
    {
        return _y;
    }
    SQUARE_COLOR GetColor()
    {
        return _colorIndex;
    }
    Color4F getColor4F()
    {
        return _color4F;
    }
    void SetColor(SQUARE_COLOR color)
    {
        _colorIndex = color;
        float alpha = _color4F.a;
        _color4F = s_squareColor[_colorIndex];
        _color4F.a = alpha;
    }
    void SetAlpha(float a)
    {
        _color4F.a = a;
    }
private:
    int _x;
    int _y;
    SQUARE_COLOR _colorIndex;
    Color4F _color4F;

    
};


#endif /* Square_h */
