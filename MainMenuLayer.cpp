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
#include "storage/local-storage/LocalStorage.h"
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
		[=](Ref*)
	{
		/*auto scene = Scene::create();
		scene->addChild(GamePlayScene::create());
		Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, scene));*/
		//static_cast<LayerMultiplex*>(_parent)->switchTo(0);
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


SelectLevelMenuLayer::SelectLevelMenuLayer()
{

}
SelectLevelMenuLayer::~SelectLevelMenuLayer()
{

}
//注意：当字符串为空时，也会返回一个空字符串  
void split(std::string& s, std::string& delim, std::vector< std::string >* ret)
{
	size_t last = 0;
	size_t index = s.find_first_of(delim, last);
	while (index != std::string::npos)
	{
		ret->push_back(s.substr(last, index - last));
		last = index + 1;
		index = s.find_first_of(delim, last);
	}
	if (index - last > 0)
	{
		ret->push_back(s.substr(last, index - last));
	}
}
bool SelectLevelMenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	localStorageInit("map");
	std::string mapNameList;
	if (localStorageGetItem("namelist", &mapNameList))
	{

	}
	std::vector< std::string >* namelist = new std::vector< std::string >();
	split(mapNameList,std::string("|"),namelist);

	namelist->clear();
	delete namelist;
	return true;
}