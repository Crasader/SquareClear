//
//  Square.hpp
//  SquareClear
//
//  Created by 徐徐 on 15/11/14.
//  单个方块类，包含方块的颜色和坐标信息
//

#ifndef Square_h
#define Square_h

#include <stdio.h>

int const s_squareColor[] =
{
    0xFF0000,
    0x00FF00,
    0x0000FF,
    0x000000,
    0xFFFFFF
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
        _color = SC_NONE;
        _color8 = 0x0;
        _alpha = 0xFF;
    }
    ~Square(){};
    Square(int x,int y,SQUARE_COLOR color,unsigned int alpha = 0xFF)
    {
        _x = x;
        _y = y;
        _color = color;
        _alpha = alpha;
        _color8 = (_alpha <<6) & CalcColor();
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
        return _color;
    }
    void SetColor(SQUARE_COLOR color)
    {
        _color = color;
        _color8 = (_alpha <<6) & CalcColor();
    }
    unsigned int GetColor8()
    {
        return _color8;
    }
    void SetAlpha(unsigned int alpha)
    {
        _alpha = alpha;
        _color8 = (_alpha <<6) & CalcColor();
    }
    void SetColor8(unsigned int color8)
    {
        _color8 = color8;
    }
private:
    int _x;
    int _y;
    SQUARE_COLOR _color;
    //alpha 0~255
    unsigned int _alpha;
    //颜色
    unsigned int _color8;
    //通过颜色枚举返回对应颜色
    unsigned int CalcColor()
    {
        
        assert(_color > SC_NONE && _color < SC_MAX);
        return s_squareColor[_color];
        
    }
    
};


#endif /* Square_h */
