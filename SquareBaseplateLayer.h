//
//
//
//	Created by xuhua on 16/5/10
//  ��Ϸ�Ļ��壬���������������Ϻ��ʵ�λ��
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

	~SquareBaseplateLayer();

	virtual bool init() override;

	CC_SYNTHESIZE(BaseSize, _baseSize, BaseSize);
private:
	std::vector<Square*> *m_baseSquareList;

};

#endif//define SquareBaseplateLayer_h