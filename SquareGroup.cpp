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
bool SquareGroup::init()
{
	if (!Node::init())
	{
		return false;
	}
    m_groupArray = new std::map<int,Square*>;
    _groupType = ST_NONE;
	m_drawNode = DrawNode::create();
	addChild(m_drawNode, 1);

	return true;
}

void SquareGroup::SetSquareGroup(int x, int y, SquareGroup::SQUAREGROUP_TYPE type, Square::SQUARE_COLOR color /*= Square::SC_BLACK*/)
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

void SquareGroup::DrawGroup(int squareWidth, int squareHeight)
{
	SquareMap* sm = this->getGroupArray();
	SquareMapIterator smit;
	for (smit = sm->begin(); smit != sm->end(); smit++)
	{
		drawOneSquare(squareWidth, squareHeight, smit->second);
	}


}

void SquareGroup::drawOneSquare(int squareWidth, int squareHeight, Square* sq)
{
	Vec2 _origin = 
		Director::getInstance()->	convertToGL
		(Vec2(this->getPositionX() + squareWidth * sq->GetX(), this->getPositionY() + squareHeight * sq->GetY()));
	Vec2 _dest = 
		Director::getInstance()->convertToGL
		(Vec2(this->getPositionX() + squareWidth * (sq->GetX() + 1), this->getPositionY() + squareHeight * (sq->GetY() + 1)));
	m_drawNode->drawSolidRect(_origin, _dest, sq->getColor4F());
}