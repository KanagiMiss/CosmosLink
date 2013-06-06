#include "DifficultyScene.h"
#include "LevelSelectScene.h"
#include "CosLogic.h"
#include "CosResource.h"
#include "VisibleRect.h"

using namespace cocos2d;


void DifficultyScene::runThisTest()
{
	CCLayer *pLayer = new DifficultyLayer();
	pLayer->autorelease();
	addChild(pLayer);

	CCDirector::sharedDirector()->replaceScene(this);
}

void DifficultyLayer::onEnter()
{
	CCLayer::onEnter();

	//create menu item
	CCMenuItemImage *pEasyItem = CCMenuItemImage::create(rcDifficultyItemEasyNormal, rcDifficultyItemEasySelected, this, menu_selector(DifficultyLayer::EasyCallback));
	CCMenuItemImage *pNormalItem = CCMenuItemImage::create(rcDifficultyItemNormalNormal, rcDifficultyItemNormalSelected, this, menu_selector(DifficultyLayer::NormalCallback)); 
	CCMenuItemImage *pHardItem = CCMenuItemImage::create(rcDifficultyItemHardNormal, rcDifficultyItemHardSelected, this, menu_selector(DifficultyLayer::HardCallback)); 

	pEasyItem->setPosition(ccp(VisibleRect::center().x-250,VisibleRect::center().y));
	pNormalItem->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y));
	pHardItem->setPosition(ccp(VisibleRect::center().x+250,VisibleRect::center().y));

	CCMenu* pMenu = CCMenu::create(pEasyItem, pNormalItem, pHardItem, NULL);
	pMenu->setPosition(CCPointZero);

	this->addChild(pMenu, 1);
	//end create menu item
}

void DifficultyLayer::onExit()
{
	CCLayer::onExit();
}

void DifficultyLayer::goToNextScene()
{
	LevelSelectScene *pScene = new LevelSelectScene();
	if(pScene){
		pScene->runThisTest();
		pScene->release();
	}
}

void DifficultyLayer::EasyCallback(CCObject* pSender)
{
	cosmos::CosGame::getInstance()->chooseDifficulty(cosmos::EASY);
	goToNextScene();
}

void DifficultyLayer::NormalCallback(CCObject* pSender)
{
	cosmos::CosGame::getInstance()->chooseDifficulty(cosmos::NORMAL);
	goToNextScene();
}

void DifficultyLayer::HardCallback(CCObject* pSender)
{
	cosmos::CosGame::getInstance()->chooseDifficulty(cosmos::HARD);
	goToNextScene();
}


