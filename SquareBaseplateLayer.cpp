//
//
//
//	Created by xuhua on 16/5/10
//  游戏的基板类，将方块置于基板的空格中
//
//

#include "SquareBaseplateLayer.h"
#include "Square.h"
USING_NS_CC;
int baselist[] = 
{
	1, 1, 1, 1, 1, 1,
	1, 1, 0, 1, 1, 1,
	1, 1, 0, 1, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
};


SquareBaseplateLayer::SquareBaseplateLayer()
:_baseSize(BaseSize(1,1))
{
	m_baseSquareList = new std::vector < Square * >() ;
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
    
    m_drawNode = DrawNode::create();
    addChild(m_drawNode, 1);
    
	setBaseSize(BaseSize(6,6));
	for (int i = 0; i <= getBaseSize().width * getBaseSize().height; i++)
	{
		if (baselist[i] == 1)
		{//上下翻转，因为gl坐标原点在左下。
			m_baseSquareList->push_back(
				new Square(i % getBaseSize().width, getBaseSize().height - 1 - i / getBaseSize().height, Square::SC_RED)
				);
		}
	}
    
    
    return true;
}

void SquareBaseplateLayer::drawBasesplate(Vec2 squareSize)
{
    for(auto sq : *m_baseSquareList)
    {//todo 将绘制方法放在Square类中实现，加入描边功能
        Vec2 _origin =(Vec2(squareSize.x * sq->GetX(), squareSize.y * sq->GetY()));
        Vec2 _dest =(Vec2(squareSize.x * (sq->GetX() + 1), squareSize.y * (sq->GetY() + 1)));
        
        m_drawNode->drawSolidRect(_origin, _dest, sq->getColor4F());
    }
}



