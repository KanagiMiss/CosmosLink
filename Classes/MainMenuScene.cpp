#include "MainMenuScene.h"
#include "DifficultyScene.h"
#include "OptionScene.h"
#include "GalleryScene.h"
#include "CosLogic.h"
#include "CosResource.h"
#include "VisibleRect.h"

using namespace cocos2d;

static cosmos::CosGame *createGame()
{
	return cosmos::CosGame::getInstance();
}

CCScene* MainMenuScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MainMenuScene *layer = MainMenuScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////

		CCMenuItemImage *pStartItem = CCMenuItemImage::create(rcMainMenuItemStartNormal, rcMainMenuItemStartSelected, this, menu_selector(MainMenuScene::menuStartCallback));
		CCMenuItemImage *pOptionItem = CCMenuItemImage::create(rcMainMenuItemOptionNormal, rcMainMenuItemOptionSelected, this, menu_selector(MainMenuScene::menuOptionCallback));
		CCMenuItemImage *pGalleryItem = CCMenuItemImage::create(rcMainMenuItemGalleryNormal, rcMainMenuItemGallerySelected, this, menu_selector(MainMenuScene::menuGalleryCallback));
		CCMenuItemImage *pEndItem = CCMenuItemImage::create(rcMainMenuItemEndNormal, rcMainMenuItemEndSelected, this, menu_selector(MainMenuScene::menuCloseCallback));
		//CCMenuItemImage *pCloseItem = CCMenuItemImage::create(rcMainMenuItemCloseNormal, rcMainMenuItemCloseSelected, this, menu_selector(MainMenuScene::menuCloseCallback));

		//pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
		pStartItem->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y));
		pGalleryItem->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y-50));
		pOptionItem->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y-100));
		pEndItem->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y-150));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pStartItem, pGalleryItem, pOptionItem, pEndItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		// Add the menu to layer as a child layer.
		this->addChild(pMenu, 1);

		// BackGround
		CCSprite* pSprite = CCSprite::create(rcMainMenuBackGround);
		if(pSprite){
			// Place the sprite on the center of the screen
			//pSprite->setAnchorPoint(ccp(0,0));
			pSprite->setPosition(VisibleRect::center());

			// Add the sprite to HelloWorld layer as a child layer.
			this->addChild(pSprite, 0);
		}
		createGame();	//create game logic

		bRet = true;
	} while (0);

	return bRet;
}

void MainMenuScene::menuStartCallback(CCObject* pSender)
{
	DifficultyScene *pScene = new DifficultyScene();
	if(pScene){
		pScene->runThisTest();
		pScene->release();
	}
}

void MainMenuScene::menuOptionCallback(CCObject* pSender)
{
	OptionScene *pScene = new OptionScene();
	if(pScene){
		pScene->runThisTest();
		pScene->release();
	}
}

void MainMenuScene::menuGalleryCallback(CCObject* pSender)
{
	GalleryScene *pScene = new GalleryScene();
	if(pScene){
		pScene->runThisTest();
		pScene->release();
	}
}

void MainMenuScene::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
	cosmos::CosGame::releaseInstance();
}

