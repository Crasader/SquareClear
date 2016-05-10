//
//  SquareGroup.cpp
//  SquareClear
//
//  Created by 徐徐 on 15/10/18.
//
//

#include "SquareGroup.h"
#include "ui/UIButton.h"
#include "GamePlayLayer.h"

int const SquareGroup::s_Width = 4;
int const SquareGroup::s_Height = 4;
int const s_shapeList[SquareGroup::ST_MAX][SquareGroup::s_Width * SquareGroup::s_Height] =
{
    {
        0,1,0,0,
        0,1,0,0,
        0,1,1,0,
        0,0,0,0
    },
    {
        0,0,1,0,
        0,0,1,0,
        0,1,1,0,
        0,0,0,0
    },
    {
        0,0,0,0,
        1,1,0,0,
        0,1,1,0,
        0,0,0,0
    },
    {
        0,0,0,0,
        0,1,1,0,
        1,1,0,0,
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

	//左箭头
	m_arrowButtonLeft = cocos2d::ui::Button::create("ButtonArrowOrangeLeft.png");
	m_arrowButtonLeft->setAnchorPoint(Vec2(1,0.5));
	m_arrowButtonLeft->setPosition(Vec2(-m_squareSize.x,m_squareSize.y * 2));
	m_arrowButtonLeft->addTouchEventListener(
		[=](Ref*, cocos2d::ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
			{
				TurnLeft();
				m_drawNode->clear();
				DrawGroup();
			}
				break;
			case cocos2d::ui::Widget::TouchEventType::MOVED:

				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
			case cocos2d::ui::Widget::TouchEventType::CANCELED:

				break;
			default:
				break;
			}
		}
	);
	addChild(m_arrowButtonLeft);
	//m_arrowButtonLeft->setVisible(true);
	//右箭头
	m_arrowButtonRight = cocos2d::ui::Button::create("ButtonArrowOrangeRight.png");
	m_arrowButtonRight->setAnchorPoint(Vec2(0,0.5));
	m_arrowButtonRight->setPosition(Vec2(m_squareSize.x * (s_Width + 1), m_squareSize.y * 2));
	m_arrowButtonRight->addTouchEventListener(
		[=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
		{
			TurnRight();
			m_drawNode->clear();
			DrawGroup();
		}
		break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:

			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
		case cocos2d::ui::Widget::TouchEventType::CANCELED:

			break;
		default:
			break;
		}
	}
	);
	addChild(m_arrowButtonRight);
	//m_arrowButtonRight->setVisible(true);
	setArrowButtonVisible(false);

	return true;
}


SquareGroup::SquareGroup()
: _isSelected(false)
{
	m_squareSize = GamePlayLayer::s_squareSize;
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(SquareGroup::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SquareGroup::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SquareGroup::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(SquareGroup::onTouchCancelled, this);
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
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

void SquareGroup::SetSquareGroup(Vec2 squareSize, SquareGroup::SQUAREGROUP_TYPE type, Square::SQUARE_COLOR color /*= Square::SC_BLACK*/)
{
	SetSquareSize(squareSize);
	SetGroupType(type, color);
	
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
        {//上下翻转，因为gl坐标原点在左下。
            m_groupArray->insert(std::pair<int,Square*>(i,new Square(i % s_Width, s_Height - 1 - i / s_Height, color)));
        }   
    }
}

void SquareGroup::DrawGroup()
{
    SquareMap* sm = this->getGroupArray();

    for (auto sq : *sm)
    {
		drawOneSquare(m_squareSize, sq.second);
    }
}

void SquareGroup::DrawGroup(Vec2 squareSize)
{
	SetSquareSize(squareSize);
    DrawGroup();


}

void SquareGroup::drawOneSquare(Vec2 squareSize, Square* sq)
{
	Vec2 _origin = 
		//Director::getInstance()->convertToGL
		(Vec2(squareSize.x * sq->GetX(), squareSize.y * sq->GetY()));
	Vec2 _dest = 
		//Director::getInstance()->convertToGL
		(Vec2(squareSize.x * (sq->GetX() + 1), squareSize.y * (sq->GetY() + 1)));

	m_drawNode->drawSolidRect(_origin, _dest, sq->getColor4F());
	//m_drawNode->drawPoint(Vec2(0,0),5,Color4F(1,1,1,1));
	//m_drawNode->drawSolidRect(Vec2(squareWidth * sq->GetX(), squareHeight * sq->GetY())
	//	, Vec2(squareWidth * (sq->GetX() + 1), squareHeight * (sq->GetY() + 1)), sq->getColor4F());
}

bool SquareGroup::checkTouchInSelf_Parent(Touch *touch)
{
    //方案三
    //获得点击的OpenGL的世界坐标值
    Vec2 touchPoint = touch->getLocation();
    //将点击的位置转换成父元素坐标系中的相对坐标
    Vec2 pt = getParent()->convertToNodeSpace(touchPoint);
    printf("pt.x=%.1f, pt.y=%.1f\n", pt.x, pt.y);
    //得到自己在父元素坐标系中的位置范围
    Rect rect=getBoundingBox();
    printf("rect.l=%.1f, rect.b=%.1f, rect.r=%.1f, rect.t=%.1f\n",\
           rect.getMinX(), rect.getMinY(), rect.getMaxX(), rect.getMaxY());
    //判断是否点击落在自己的范围当中， 以上判断全是在父元素坐标系中进行计算
    if(rect.containsPoint(pt))
    {
        printf("ccTouchBegan x=%.1f y=%.1f\n", touchPoint.x, touchPoint.y);
        return true;
    }
    return false;
}

bool SquareGroup::onTouchBegan(Touch *touch, Event *event)
{
    if(!checkTouchInSelf_Parent(touch))
    {
        if(getIsSelected())
        {
            setIsSelected(false);
			setArrowButtonVisible(false);
        }
        return false;
    }
    setIsSelected(true);
	setArrowButtonVisible(true);
    //m_drawNode->clear();
    //DrawGroup();
    
    return true;
}

void SquareGroup::onTouchMoved(Touch *touch, Event *event)
{
    if(!getIsSelected())
    {
        return;
    }
//    if(!checkTouchInSelf_Parent(touch))
//    {
//        return;
//    }
    //获得点击的OpenGL的世界坐标值
    Vec2 touchPoint = touch->getLocation();
    //将点击的位置转换成父元素坐标系中的相对坐标
    Vec2 pt = getParent()->convertToNodeSpace(touchPoint);
	pt.x -= m_squareSize.x * 2;
    //pt.y -= m_squareHeight * 2;
    setPosition(pt);
}

void SquareGroup::onTouchEnded(Touch *touch, Event *event)
{
    if(!getIsSelected())
    {
        return;
    }
    m_drawNode->clear();
    DrawGroup();
    drawArrow();
//    if(!checkTouchInSelf_Parent(touch))
//    {
//        return;
//    }
    //setIsSelected(false);
    
    return;
}

void SquareGroup::onTouchCancelled(Touch *touch, Event *event)
{
    if(!getIsSelected())
    {
        return;
    }
    
    if(!checkTouchInSelf_Parent(touch))
    {
        return;
    }
    //setIsSelected(false);
    
    return;
}

void SquareGroup::drawArrow()
{
//    m_drawNode->drawTriangle(Vec2(-m_squareWitdh *2, m_squareHeight * 2),Vec2(-m_squareWitdh * 1, m_squareHeight * 4),Vec2(-m_squareWitdh * 1, -m_squareHeight * 0), Color4F(1,1,0,1));
//    m_drawNode->drawTriangle(Vec2(m_squareWitdh * (SquareGroup::s_Width + 2), m_squareHeight * 2),Vec2(m_squareWitdh * (SquareGroup::s_Width + 1) * 1, m_squareHeight * 4),Vec2(m_squareWitdh * (SquareGroup::s_Width + 1), -m_squareHeight * 0), Color4F(1,1,0,1));
}

void SquareGroup::TurnLeft()
{

}

void SquareGroup::TurnRight()
{
	for (auto sq : *m_groupArray)
	{
		Square* square = (Square*)(sq.second);
		square->setXYIndex(s_Width - square->GetY() - 1 , square->GetX());
	}
}

void SquareGroup::SetSquareSize(Vec2 size)
{
	m_squareSize = size;
	setContentSize(Size(m_squareSize.x * SquareGroup::s_Width, m_squareSize.y * SquareGroup::s_Height));
	m_arrowButtonLeft->setPosition(Vec2(-m_squareSize.x, m_squareSize.y * 2));
	m_arrowButtonRight->setPosition(Vec2(m_squareSize.x * (s_Width + 1), m_squareSize.y * 2));
}

void SquareGroup::setArrowButtonVisible(bool flag)
{
	m_arrowButtonLeft->setVisible(flag);
	m_arrowButtonRight->setVisible(flag);
}