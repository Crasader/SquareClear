//
//  SquareGroup.h
//  SquareClear
//
//  Created by 徐徐 on 15/10/18.
//
//

#ifndef __SquareClear__SquareGroup__
#define __SquareClear__SquareGroup__

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
    enum SQUARE_COLOR
    {
        SC_NONE = -1,
        SC_RED = 0,
        SC_GREEN,
        SC_BLUE,
        SC_BLACK,
        SC_WHITE,
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
    unsigned int _alpha;
    unsigned int _color8;
    
    unsigned int CalcColor()
    {

        assert(_color > SC_NONE && _color < SC_MAX);
        return s_squareColor[_color];

    }
    
};

typedef std::map<int,Square*> SquareMap;
class SquareGroup
{
public:
    enum SQUAREGROUP_TYPE
    {
        ST_NONE = -1,
        ST_L,
        ST_L_TURN,
        ST_Z,
        ST_Z_TURN,
        ST_MAX
    };
    SquareGroup();
    SquareGroup(int x,int y,SquareGroup::SQUAREGROUP_TYPE type,Square::SQUARE_COLOR color = Square::SC_BLACK);
    ~SquareGroup();
    void SetGroupType(SQUAREGROUP_TYPE type, Square::SQUARE_COLOR color = Square::SC_BLACK);
    SQUAREGROUP_TYPE getGroupType(){return _groupType;}
    SquareMap* getGroupArray(){return m_groupArray;}
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
    
};
#endif /* defined(__SquareClear__SquareGroup__) */
