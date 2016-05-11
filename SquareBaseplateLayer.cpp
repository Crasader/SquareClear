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
,_squareSize(Vec2(1,1))
{
	m_baseSquareList = new std::vector < BaseSquare >();
}

SquareBaseplateLayer::~SquareBaseplateLayer()
{
	for (auto sq : *m_baseSquareList)
	{
		delete sq.pSquare;
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
		switch (baselist[i])
		{
		case 0:
			//上下翻转，因为gl坐标原点在左下。
			m_baseSquareList->push_back(BaseSquare(SquareBaseplateState::SQBS_EMPTY,
				new Square(i % getBaseSize().width, getBaseSize().height - 1 - i / getBaseSize().height, Square::SC_RED)
				));
			break;
		case 1:
			//上下翻转，因为gl坐标原点在左下。
			m_baseSquareList->push_back(BaseSquare(SquareBaseplateState::SQBS_MAP,
				new Square(i % getBaseSize().width, getBaseSize().height - 1 - i / getBaseSize().height, Square::SC_RED)
				));
			break;
		default:
			//上下翻转，因为gl坐标原点在左下。
			m_baseSquareList->push_back(BaseSquare(SquareBaseplateState::SQBS_EMPTY,
				new Square(i % getBaseSize().width, getBaseSize().height - 1 - i / getBaseSize().height, Square::SC_RED)
				));
			break;
		}
	}
    
    
    return true;
}

void SquareBaseplateLayer::drawBasesplate(Vec2 squareSize)
{
	setSquareSize(squareSize);
	m_drawNode->clear();
    for(auto sq : *m_baseSquareList)
    {//todo 将绘制方法放在Square类中实现，加入描边功能
  //      Vec2 _origin =(Vec2(squareSize.x * sq->getIndexX(), squareSize.y * sq->getIndexY()));
		//Vec2 _dest = (Vec2(squareSize.x * (sq->getIndexX() + 1), squareSize.y * (sq->getIndexY() + 1)));
  //      
  //      m_drawNode->drawSolidRect(_origin, _dest, sq->getColor4F());
		if (sq.pSquare)
		{
			switch (sq.squareState)
			{
			case SQBS_EMPTY:
				break;
			case SQBS_MAP:
				sq.pSquare->drawSquare(m_drawNode, squareSize);
				break;
			case SQBS_FRAME:
				sq.pSquare->drawFrame(m_drawNode, squareSize,Color4F::YELLOW);
				break;
			case SQBS_SQUARE:
				break;
			default:
				break;
			}
			
		}
		
    }
}

void SquareBaseplateLayer::drawBasesplate()
{
	drawBasesplate(getSquareSize());
}

bool SquareBaseplateLayer::CheckSquareIsEmpty(cocos2d::Vec2 point)
{
	Vec2 pos =  convertToNodeSpace(point);
	if (pos.x < 0 || pos.x > getBaseSize().width * getSquareSize().x)
	{
		return false;
	}
	if (pos.y < 0 || pos.y > getBaseSize().height * getSquareSize().y)
	{
		return false;
	}

	int _indexX = (int)(pos.x / getSquareSize().x);
	int _indexY = getBaseSize().height - 1 - (int)(pos.y / getSquareSize().y);
	int _index = _indexY * getBaseSize().width + _indexX;
	if (_index >= m_baseSquareList->size())
	{
		return false;
	}
	if ((*m_baseSquareList)[_index].squareState == SquareBaseplateState::SQBS_EMPTY)
	{
		(*m_baseSquareList)[_index].squareState = SquareBaseplateState::SQBS_FRAME;
		return true;
	}
	return false;
}
