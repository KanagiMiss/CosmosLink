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
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(0.5f, this));
}

void DifficultyLayer::onEnter()
{
	CCLayer::onEnter();

	//create menu item
	CCMenuItemImage *pEasyItem = CCMenuItemImage::create(rcDifficultyItemEasyNormal, rcDifficultyItemEasySelected, this, menu_selector(DifficultyLayer::EasyCallback));
	CCMenuItemImage *pNormalItem = CCMenuItemImage::create(rcDifficultyItemNormalNormal, rcDifficultyItemNormalSelected, this, menu_selector(DifficultyLayer::NormalCallback)); 
	CCMenuItemImage *pHardItem = CCMenuItemImage::create(rcDifficultyItemHardNormal, rcDifficultyItemHardSelected, this, menu_selector(DifficultyLayer::HardCallback)); 

	pEasyItem->setPosition(ccp(VisibleRect::right().x*(1.0/5.0),VisibleRect::center().y));
	pNormalItem->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y));
	pHardItem->setPosition(ccp(VisibleRect::right().x*(4.0/5.0),VisibleRect::center().y));

	CCMenu* pMenu = CCMenu::create(pEasyItem, pNormalItem, pHardItem, NULL);
	pMenu->setPosition(CCPointZero);

	this->addChild(pMenu, 1);
	//end create menu item

	// BackGround
		CCSprite* pSprite = CCSprite::create(rcDifficultyBackGround);
		if(pSprite){
			// Place the sprite on the center of the screen
			//pSprite->setAnchorPoint(ccp(0,0));
			pSprite->setPosition(VisibleRect::center());

			// Add the sprite to layer as a child layer.
			this->addChild(pSprite, 0);
		}
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


