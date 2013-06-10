#include "GameEndScene.h"
#include "MainMenuScene.h"
#include "PlayingGameScene.h"
#include "CosResource.h"
#include "CosLogic.h"
#include "VisibleRect.h"

using namespace cocos2d;

#define __KDEBUG__

#ifdef __KDEBUG__
#include <iostream>
#endif

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

	cosmos::CosGame *pGame = cosmos::CosGame::getInstance();

	//create menu item
	CCMenuItemImage *pBackItem = CCMenuItemImage::create(rcGameEndItemBackNormal, rcGameEndItemBackSelected, this, menu_selector(GameEndScene::backToMenuCallback));
	CCMenuItemImage *pRestartItem = CCMenuItemImage::create(rcGameEndItemRestartNormal, rcGameEndItemRestartSelected, this, menu_selector(GameEndScene::restartCallback));   

	pRestartItem->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y-100));
	pBackItem->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y-150));

	CCMenu* pMenu = CCMenu::create(pRestartItem, pBackItem, NULL);
	pMenu->setPosition(CCPointZero);

	this->addChild(pMenu, 1);
	//end create menu item
	CCLabelTTF *pLabel;
	if(pGame->getGameState() == cosmos::WIN)
		pLabel = CCLabelTTF::create("You Win!","Arial",100);
	else
		pLabel = CCLabelTTF::create("You Lose!","Arial",100);
	pLabel->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y+80));
	addChild(pLabel,1);
	//create score and time
	//score
	char tempStr[30];
	CCLabelTTF *plblScore,*plblTime;
	sprintf(tempStr,"Score: %d",pGame->getGameScore());
	plblScore = CCLabelTTF::create(tempStr,"Arial",30);
	//time
#ifdef __KDEBUG__
	std::cout << "Time:" << pGame->getGameTime() << std::endl;
#endif
	sprintf(tempStr,"Time : %.2lf",pGame->getGameTime());
	plblTime  = CCLabelTTF::create(tempStr,"Arial",30);

	plblScore->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y));
	plblTime->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y-40));
	addChild(plblScore,1);
	addChild(plblTime,1);

	//load background
	CCSprite* pSprite = CCSprite::create(rcGameEndBackGround);
	if(pSprite){
		// Place the sprite on the center of the screen
		//pSprite->setAnchorPoint(ccp(0,0));
		pSprite->setPosition(VisibleRect::center());

		// Add the sprite to layer as a child layer.
		this->addChild(pSprite, 0);
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
