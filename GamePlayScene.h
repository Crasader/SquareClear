//
//  GamePlayScene.h
//  SquareClear
//
//  Created by 徐徐 on 15/10/19.
//
//

#ifndef __SquareClear__GamePlayScene__
#define __SquareClear__GamePlayScene__

#include <stdio.h>
#include "cocos2d.h"

class GamePlayScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlayScene);
    
    
};
#endif /* defined(__SquareClear__GamePlayScene__) */
