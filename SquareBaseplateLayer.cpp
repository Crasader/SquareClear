//
//
//
//	Created by xuhua on 16/5/10
//  游戏的基板，将方块放置入基板上合适的位置
//
//

#include "SquareBaseplateLayer.h"
#include "Square.h"
USING_NS_CC;
int baselist[] = 
{
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
};


SquareBaseplateLayer::SquareBaseplateLayer()
{
	m_baseSquareList = new std::vector < Square * > ;
}

SquareBaseplateLayer::~SquareBaseplateLayer()
{
	for (auto sq : *m_baseSquareList)
	{
		delete sq;
	}
	m_baseSquareList->clear();
	delete m_baseSquareList;
}

bool SquareBaseplateLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	setBaseSize(BaseSize(6,6));
	for (int i = 0; i <= getBaseSize().width * getBaseSize().height; i++)
	{
		if (baselist[i] == 1)
		{
			m_baseSquareList->push_back(
				new Square(i % getBaseSize().width, i / getBaseSize().height, Square::SC_RED)
				);
		}
	}
}