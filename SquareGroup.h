//
//  SquareGroup.h
//  SquareClear
//
//  Created by 徐徐 on 15/10/18.
//  一组方块组成形状的类
//

#ifndef __SquareClear__SquareGroup__
#define __SquareClear__SquareGroup__

#include <stdio.h>
#include "Square.h"
#include "ui/UIButton.h"

typedef std::map<int,Square*> SquareMap;
typedef std::map<int,Square*>::iterator SquareMapIterator;
class SquareGroup : public Layer
{
public:
    //方块组的类型，形状
    enum SQUAREGROUP_TYPE
    {
        ST_NONE = -1,
        ST_L,
        ST_L_TURN,
        ST_Z,
        ST_Z_TURN,
        ST_MAX
    };

	bool init() override;

	CREATE_FUNC(SquareGroup);

	SquareGroup();
	~SquareGroup();

	//设置方块组放块的大小，类型和颜色，默认黑色
    void SetSquareGroup(Vec2 squareSize,SquareGroup::SQUAREGROUP_TYPE type,Square::SQUARE_COLOR color = Square::SC_BLACK);

    //设置方块组的类型和颜色，默认黑色
    void SetGroupType(SQUAREGROUP_TYPE type, Square::SQUARE_COLOR color = Square::SC_BLACK);

	//设置放块组放块的大小
	void SetSquareSize(Vec2 size);

    SQUAREGROUP_TYPE getGroupType(){return _groupType;}

    SquareMap* getGroupArray(){return m_groupArray;}

    //绘制方块组
    void DrawGroup();

    //绘制方块组，指定长宽
	void DrawGroup(Vec2 squareSize);
	
    bool checkTouchInSelf_Parent(Touch *touch);
    
	void TurnLeft();
	void TurnRight();
	
	void setArrowButtonVisible(bool flag);
    // Overrides
    virtual bool onTouchBegan(Touch *touch, Event *event) override;
    virtual void onTouchMoved(Touch *touch, Event *event) override;
    virtual void onTouchEnded(Touch *touch, Event *event) override;
    virtual void onTouchCancelled(Touch *touch, Event *event) override;
    
    void drawArrow();
    
    static const int s_Width;
    static const int s_Height;
    
    CC_SYNTHESIZE(bool, _isSelected, IsSelected);

    
private:
    void CalcGroup(Square::SQUARE_COLOR color = Square::SC_BLACK);
    SquareMap *m_groupArray;
    SQUAREGROUP_TYPE _groupType;
	Vec2 m_squareSize;
	cocos2d::DrawNode * m_drawNode;
	cocos2d::ui::Button * m_arrowButtonLeft;
	cocos2d::ui::Button * m_arrowButtonRight;

	int* m_groupShape;
};
#endif /* defined(__SquareClear__SquareGroup__) */
