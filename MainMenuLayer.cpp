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
    
    return true;
}