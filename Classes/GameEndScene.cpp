#include "GameEndScene.h"
#include "MainMenuScene.h"
#include "PlayingGameScene.h"
#include "CosResource.h"
#include "CosLogic.h"
#include "VisibleRect.h"

using namespace cocos2d;


GameEndScene::GameEndScene(void)
{
	//ctor
}


GameEndScene::~GameEndScene(void)
{
	//dctor
}

void GameEndScene::onEnter()
{
	CCLayer::onEnter();

	//create menu item
	CCMenuItemImage *pBackItem = CCMenuItemImage::create(rcGameEndItemBackNormal, rcGameEndItemBackSelected, this, menu_selector(GameEndScene::backToMenuCallback));
	CCMenuItemImage *pRestartItem = CCMenuItemImage::create(rcGameEndItemRestartNormal, rcGameEndItemRestartSelected, this, menu_selector(GameEndScene::restartCallback));   

	pRestartItem->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y));
	pBackItem->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y-50));

	CCMenu* pMenu = CCMenu::create(pRestartItem, pBackItem, NULL);
	pMenu->setPosition(CCPointZero);

	this->addChild(pMenu, 1);
	//end create menu item
	if(cosmos::CosGame::getInstance()->getGameState() == cosmos::WIN)
	{
		CCLabelTTF *pLabel = CCLabelTTF::create("You Win!","Arial",100);
		pLabel->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y+80));
		addChild(pLabel,1);
	}
}

void GameEndScene::onExit()
{
	CCLayer::onExit();
}

void GameEndScene::backToMenuCallback(CCObject* pSender)
{
	cosmos::CosGame *pGame = cosmos::CosGame::getInstance();
	pGame->endGame();

    CCScene* pScene = CCScene::create();
	MainMenuScene* pLayer = MainMenuScene::create();

    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GameEndScene::restartCallback(CCObject* pSender)
{
	cosmos::CosGame *pGame = cosmos::CosGame::getInstance();
	pGame->startGame();

	PlayingGameScene *pScene = new PlayingGameScene();
	if(pScene){
		pScene->runThisTest();
		pScene->release();
	}
}
