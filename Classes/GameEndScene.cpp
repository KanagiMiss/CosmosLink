#include "GameEndScene.h"
#include "MainMenuScene.h"
#include "PlayingGameScene.h"
#include "CosResource.h"
#include "CosLogic.h"
#include "VisibleRect.h"
#include "KUtils.h"

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

	pRestartItem->setAnchorPoint(ccp(0.5,0));
	pBackItem->setAnchorPoint(ccp(0.5,0));

	pRestartItem->setPosition(ccp(VisibleRect::center().x,VisibleRect::bottom().y+75));
	pBackItem->setPosition(ccp(VisibleRect::center().x,VisibleRect::bottom().y+10));

	CCMenu* pMenu = CCMenu::create(pRestartItem, pBackItem, NULL);
	pMenu->setPosition(CCPointZero);

	this->addChild(pMenu, 1);

	//end create menu item
	CCLabelBMFont *pLabel;
	if(pGame->getGameState() == cosmos::WIN)
	{
		pLabel = CCLabelBMFont::labelWithString("You Win! :)",rcImageFont60);
		KUtils::playSound(rcSoundGameEnd);
		//CCLabelTTF::create("You Win!","Arial",100);

		//update gallery data
		bool newrec = pGame->updateGallery();

		//create score and time
		//score
		char tempStr[30];
		CCLabelBMFont *plblScore,*plblTime;
		sprintf(tempStr,"得分: %d",pGame->getGameScore());
		plblScore = CCLabelBMFont::labelWithString(tempStr,rcImageFont32);
		//time
	#ifdef __KDEBUG__
		std::cout << "time:" << pGame->getGameTime() << std::endl;
	#endif
		sprintf(tempStr,"用时: %.2lf",pGame->getGameTime());
		plblTime  = CCLabelBMFont::labelWithString(tempStr,rcImageFont32);

		plblScore->setAnchorPoint(ccp(0,0.5));
		plblTime->setAnchorPoint(ccp(0,0.5));

		plblScore->setPosition(ccp(VisibleRect::center().x-50,VisibleRect::center().y));
		plblTime->setPosition(ccp(VisibleRect::center().x-50,VisibleRect::center().y-40));
		this->addChild(plblScore,1);
		this->addChild(plblTime,1);

		//is new record
		if(newrec){
			CCLabelTTF *pLblNewRec = CCLabelTTF::create("new record!","Arial",20);
			pLblNewRec->setPosition(ccp(VisibleRect::center().x-50,VisibleRect::center().y-70));
			pLblNewRec->setAnchorPoint(ccp(0,0.5));
			this->addChild(pLblNewRec, 1);
		}
	}
	else
	{
		pLabel = CCLabelBMFont::labelWithString("You Lose...XD",rcImageFont60);
		KUtils::playSound(rcSoundGameOver);
		//CCLabelTTF::create("You Lose!","Arial",100);
	}
	pLabel->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y+80));
	this->addChild(pLabel,1);

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
	KUtils::playSound(rcSoundBTNDown);
    CCScene* pScene = CCScene::create();
	MainMenuScene* pLayer = MainMenuScene::create();

    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void GameEndScene::restartCallback(CCObject* pSender)
{
	cosmos::CosGame *pGame = cosmos::CosGame::getInstance();
	pGame->startGame();
	KUtils::playSound(rcSoundBTNDown);
	PlayingGameScene *pScene = new PlayingGameScene();
	if(pScene){
		pScene->runThisTest();
		pScene->release();
	}
}
