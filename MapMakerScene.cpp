#include "MapMakerScene.h"
#include "MainMenuScene.h"
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



	return true;
}

void MapMakerScene::returnToMainMenuCallback(cocos2d::Ref* pSender)
{
	auto scene = Scene::create();
	scene->addChild(MainMenuScene::create());
	Director::getInstance()->replaceScene(TransitionFlipY::create(0.5, scene));

}
