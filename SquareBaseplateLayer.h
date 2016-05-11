//
//
//
//	Created by xuhua on 16/5/10
//  游戏的基板类，将方块置于基板的空格中
//
//

#ifndef SquareBaseplateLayer_h
#define SquareBaseplateLayer_h

#include <stdio.h>
#include "cocos2d.h"

class Square;
struct BaseSize
{
	int width;
	int height;
	BaseSize(int x, int y)
	{
		width = x;
		height = y;
	}
};
enum SquareBaseplateState
{
	SQBS_EMPTY = 0,
	SQBS_MAP,
	SQBS_FRAME,
	SQBS_SQUARE,
	SQBS_MAX
};
struct BaseSquare
{
	SquareBaseplateState squareState;
	Square* pSquare;
	BaseSquare(SquareBaseplateState ss,Square* sq)
	{
		squareState = ss;
		pSquare = sq;
	}
};
class SquareBaseplateLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(SquareBaseplateLayer);

    SquareBaseplateLayer();
	~SquareBaseplateLayer();

	virtual bool init() override;

    void drawBasesplate(cocos2d::Vec2 squareSize);

	void drawBasesplate();
	//检查坐标点对应的基板是否为空方块
	bool CheckSquareIsEmpty(cocos2d::Vec2 point);

	CC_SYNTHESIZE(BaseSize, _baseSize, BaseSize);
	CC_SYNTHESIZE(cocos2d::Vec2, _squareSize, SquareSize);
private:
	std::vector<BaseSquare> *m_baseSquareList;
    cocos2d::DrawNode * m_drawNode;
	
};

#endif//define SquareBaseplateLayer_h