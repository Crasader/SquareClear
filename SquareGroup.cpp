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

void SquareGroup::SetSquareGroup(int squareWitdh, int squareHeight, SquareGroup::SQUAREGROUP_TYPE type, Square::SQUARE_COLOR color /*= Square::SC_BLACK*/)
{
    m_squareWitdh = squareWitdh;
    m_squareHeight = squareHeight;
    SetGroupType(type,color);
    setContentSize(Size(m_squareWitdh * SquareGroup::s_Width, m_squareHeight * SquareGroup::s_Height));
}

SquareGroup::SquareGroup()
: _isSelected(false)
{
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

void SquareGroup::DrawGroup()
{
    SquareMap* sm = this->getGroupArray();

    for (auto sq : *sm)
    {
        drawOneSquare(m_squareWitdh, m_squareHeight, sq.second);
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
		//Director::getInstance()->convertToGL
		(Vec2(squareWidth * sq->GetX(), squareHeight * sq->GetY()));
	Vec2 _dest = 
		//Director::getInstance()->convertToGL
		(Vec2(squareWidth * (sq->GetX() + 1), squareHeight * (sq->GetY() + 1)));

	m_drawNode->drawSolidRect(_origin, _dest, sq->getColor4F());

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
        return false;
    }
    setIsSelected(true);
    
    
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
    pt.x -= m_squareWitdh * 2;
    //pt.y -= m_squareHeight * 2;
    setPosition(pt);
}

void SquareGroup::onTouchEnded(Touch *touch, Event *event)
{
    if(!getIsSelected())
    {
        return;
    }
    
    if(!checkTouchInSelf_Parent(touch))
    {
        return;
    }
    setIsSelected(false);
    
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
    setIsSelected(false);
    
    return;
}
