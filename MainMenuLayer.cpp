//
//  MainMenuLayer.cpp
//  SquareClear
//
//  Created by 徐徐 on 16/5/12.
//
//

#include "MainMenuLayer.h"
#include "ui/UIButton.h"
#include "Language.h"
#include "GamePlayScene.h"
#include "MapMakerScene.h"
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
    
	MenuItemFont::setFontName("fonts/arial.ttf");
	MenuItemFont::setFontSize(40);

	auto menuItemSelectMap = MenuItemFont::create(std::string(LocalizedCStringByKey("start_game")));
	menuItemSelectMap->setCallback(
		[](Ref*)
	{
		auto scene = Scene::create();
		scene->addChild(GamePlayScene::create());
		Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, scene));

	}
		);


	auto menuItemMapMaker = MenuItemFont::create(std::string(LocalizedCStringByKey("map_maker")));
	menuItemMapMaker->setCallback(
		[](Ref*)
	{
		auto scene = Scene::create();
		scene->addChild(MapMakerScene::create());
		Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, scene));

	}
	);


	auto menu = Menu::create(menuItemSelectMap, menuItemMapMaker, nullptr);
	menu->alignItemsVerticallyWithPadding(20);

	auto s = Director::getInstance()->getWinSize();
	addChild(menu);
	menu->setPosition(Vec2(s.width / 2, s.height / 2));
	


    return true;
}