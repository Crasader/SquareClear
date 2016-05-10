//
//  GamePlayLayer.cpp
//  SquareClear
//
//  Created by 徐徐 on 15/11/14.
//
//

#include "GamePlayLayer.h"
#include "SquareGroup.h"
#include "SquareBaseplateLayer.h"
USING_NS_CC;

Vec2 GamePlayLayer::s_squareSize = Vec2(32, 32);
bool GamePlayLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
	m_gameBoardHeight = m_squareRowCount * s_squareSize.y;
	m_gameBoardWidth = m_squareColumnCount * s_squareSize.x;
    m_BackgroundBoard = new int[m_squareRowCount * m_squareColumnCount];
    //test
    for(int i = 0;i < m_squareRowCount * m_squareColumnCount; i++)
    {
        m_BackgroundBoard[i] = 0;
        if(i > 14 && i < 100)
        {
            m_BackgroundBoard[i] = 1;
        }
    }
    
    auto s = Director::getInstance()->getWinSize();
    
    m_drawNode = DrawNode::create();
    addChild(m_drawNode, 10);

    //m_drawNode->drawSolidRect(Vec2(10,10), Vec2(200,200), Color4F(1,1,0,1));
    
    //test
    //drawSquare();
	auto sgtest = SquareGroup::create();

	sgtest->SetSquareGroup(s_squareSize, SquareGroup::ST_L, Square::SC_BLUE);
	sgtest->setPosition(Vec2(100,100));
    //drawSquareGroup(sgtest, 100, 200);
	sgtest->DrawGroup();
	addChild(sgtest, 100);

	auto backGroundLayer = SquareBaseplateLayer::create();
	backGroundLayer->setPosition(Vec2(200,200));
	addChild(backGroundLayer, 90);
    backGroundLayer->drawBasesplate(s_squareSize);
    return true;
}

GamePlayLayer::~GamePlayLayer()
{
    delete[] m_BackgroundBoard;
}
void GamePlayLayer::drawSquare()
{
    for(int i = 0;i < m_squareRowCount * m_squareColumnCount; i++)
    {
		float _x = (i % m_squareColumnCount) * s_squareSize.x;
		float _y = (i / m_squareColumnCount) * s_squareSize.y;
        if(m_BackgroundBoard[i] == 0)
        {
			m_drawNode->drawSolidRect(Vec2(_x, _y), Vec2(_x + s_squareSize.x, _y + s_squareSize.y), Color4F(1, 0, 0, 1));
        }
        else
        {
			m_drawNode->drawSolidRect(Vec2(_x, _y), Vec2(_x + s_squareSize.x, _y + s_squareSize.y), Color4F(0, 1, 0, 1));
        }
    }
}


void GamePlayLayer::drawSquareGroup(SquareGroup* sg,int x,int y)
{
    SquareMap* sm = sg->getGroupArray();
    SquareMapIterator smit;
    for(smit = sm->begin(); smit!=sm->end(); smit++)
    {
        drawOneSquare(x, y, smit->second);
    }
    
}

void GamePlayLayer::drawOneSquare(int x,int y,Square* sq)
{
	Vec2 _x = Director::getInstance()->convertToGL(Vec2(x + s_squareSize.x * sq->GetX(), y + s_squareSize.y * sq->GetY()));
	Vec2 _y = Director::getInstance()->convertToGL(Vec2(x + s_squareSize.x * (sq->GetX() + 1), y + s_squareSize.y * (sq->GetY() + 1)));
    m_drawNode->drawSolidRect(_x, _y, sq->getColor4F());
}

