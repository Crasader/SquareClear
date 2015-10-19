//
//  SquareGroup.cpp
//  SquareClear
//
//  Created by 徐徐 on 15/10/18.
//
//

#include "SquareGroup.h"
int const SquareGroup::s_Width = 4;
int const SquareGroup::s_Height = 4;
int const s_shapeList[SquareGroup::ST_MAX][SquareGroup::s_Width * SquareGroup::s_Height] =
{
    {
        1,0,0,0,
        1,0,0,0,
        1,1,0,0,
        0,0,0,0
    },
    {
        0,1,0,0,
        0,1,0,0,
        1,1,0,0,
        0,0,0,0
    },
    {
        1,1,0,0,
        0,1,1,0,
        0,0,0,0,
        0,0,0,0
    },
    {
        0,1,1,0,
        1,1,0,0,
        0,0,0,0,
        0,0,0,0
    }
};
SquareGroup::SquareGroup()
{
    m_groupArray = new std::map<int,Square*>;
    _groupType = ST_NONE;

}

SquareGroup::SquareGroup(int x,int y,SquareGroup::SQUAREGROUP_TYPE type,Square::SQUARE_COLOR color /*= Square::SC_BLACK*/)
{
    m_groupArray = new std::map<int,Square*>;
    SetXY(x,y);
    SetGroupType(type,color);
    
}

SquareGroup::~SquareGroup()
{
    for(SquareMap::iterator itr = m_groupArray->begin(); itr != m_groupArray->end(); ++itr)
    {
        Square* square = itr->second;
        delete square;
        square = nullptr;
    }
    m_groupArray->clear();
    
}

void SquareGroup::SetGroupType(SquareGroup::SQUAREGROUP_TYPE type, Square::SQUARE_COLOR color /*= Square::SC_BLACK*/)
{
    _groupType = type;
    CalcGroup(color);
}

void SquareGroup::CalcGroup(Square::SQUARE_COLOR color /*= Square::SC_BLACK*/)
{
    assert(_groupType > ST_NONE && _groupType < ST_MAX);
    for(int i = 0; i < s_Width * s_Height; i++)
    {
        if(s_shapeList[_groupType][i] == 1)
        {
            m_groupArray->insert(std::pair<int,Square*>(i,new Square(i % s_Width,i / s_Height, color)));
        }
    
    }
}

