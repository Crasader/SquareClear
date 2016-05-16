#include "MapMakerScene.h"
#include "MainMenuScene.h"
#include "SquareGroup.h"
#include "SquareBaseplateLayer.h"
#include "Language.h"
USING_NS_CC;

Scene* MapMakerScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MapMakerScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

MapMakerScene::MapMakerScene()
{

}

MapMakerScene::~MapMakerScene()
{

}

bool MapMakerScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto returnToMainMenuItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MapMakerScene::returnToMainMenuCallback, this)
		);
	returnToMainMenuItem->setPosition(Vec2(origin.x + visibleSize.width - returnToMainMenuItem->getContentSize().width / 2,
		origin.y + returnToMainMenuItem->getContentSize().height / 2));
	auto menu = Menu::create(returnToMainMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
    
    auto baseplateLayer = SquareBaseplateLayer::create();
    baseplateLayer->createEmptyMap(BaseSize(10,10));
    baseplateLayer->drawBasesplate(Vec2(32,32));
    baseplateLayer->setPosition(Vec2(200,200));
    addChild(baseplateLayer);
    

    
    auto menuItemCreateGroup = MenuItemFont::create(LocalizedCStringByKey("create_group"));
    menuItemCreateGroup->setCallback(
    [=](Ref*)
    {
        auto squareGroup = SquareGroup::create();
        squareGroup->setPosition(Vec2(100,100));
        squareGroup->SetSquareGroup(Vec2(32,32),SquareGroup::SQUAREGROUP_TYPE::ST_Z,Square::SQUARE_COLOR::SC_GREEN);
        squareGroup->DrawGroup();
        this->addChild(squareGroup);
    }
    );
    auto menuItemDeleteSelectedGroup = MenuItemFont::create(LocalizedCStringByKey("delete_group"));
    menuItemDeleteSelectedGroup->setCallback(
    [=](Ref*)
    {
        for(Node* node:this->getChildren())
        {
            SquareGroup* sg = dynamic_cast<SquareGroup*>(node);
            if(sg != nullptr)
            {
                if(sg->getIsSelected())
                {
                    this->removeChild(node);
                }
            }
        }
    }
    );
    auto menuItemSaveMap = MenuItemFont::create(LocalizedCStringByKey("save_map"));
    menuItemSaveMap->setCallback(
    [=](Ref*)
    {
        //todo save map
    }
    );
    
    auto operationMenu = Menu::create(menuItemCreateGroup,menuItemDeleteSelectedGroup,menuItemSaveMap, NULL);
    operationMenu->alignItemsVerticallyWithPadding(20);
    auto s = Director::getInstance()->getWinSize();
    addChild(operationMenu);
    operationMenu->setPosition(Vec2(s.width - 100, s.height / 2));
    
    
	return true;
}

void MapMakerScene::returnToMainMenuCallback(cocos2d::Ref* pSender)
{
	auto scene = Scene::create();
	scene->addChild(MainMenuScene::create());
	Director::getInstance()->replaceScene(TransitionFlipY::create(0.5, scene));

}
