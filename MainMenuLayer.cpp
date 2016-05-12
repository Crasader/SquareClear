//
//  MainMenuLayer.cpp
//  SquareClear
//
//  Created by 徐徐 on 16/5/12.
//
//

#include "MainMenuLayer.h"
#include "ui/UIButton.h"
USING_NS_CC;
MainMenuLayer::MainMenuLayer()
{
    
}

MainMenuLayer::~MainMenuLayer()
{
    
}


bool MainMenuLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    
    ui::Button* selectMapButton = ui::Button::create();
    selectMapButton->setTitleText("开始游戏");
    //selectMapButton->setContentSize(Size(100,20));
    selectMapButton->addTouchEventListener(
        [](Ref*, ui::Widget::TouchEventType type)
        {
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                    
                    break;
                default:
                    break;
            }
        }
    );
    selectMapButton->setPosition(Vec2(200,200));
    selectMapButton->setVisible(true);
    addChild(selectMapButton);
    return true;
}