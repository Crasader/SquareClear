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
class SquareBaseplateLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(SquareBaseplateLayer);

    SquareBaseplateLayer();
	~SquareBaseplateLayer();

	virtual bool init() override;

    void drawBasesplate(cocos2d::Vec2 squareSize);
	CC_SYNTHESIZE(BaseSize, _baseSize, BaseSize);
private:
	std::vector<Square*> *m_baseSquareList;
    cocos2d::DrawNode * m_drawNode;

};

#endif//define SquareBaseplateLayer_h