#include "MainMenuScene.h"
#include "LevelSelectScene.h"
#include "OptionScene.h"
#include "CosResource.h"
#include "VisibleRect.h"

using namespace cocos2d;

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
		CCMenuItemImage *pEndItem = CCMenuItemImage::create(rcMainMenuItemEndNormal, rcMainMenuItemEndSelected, this, menu_selector(MainMenuScene::menuCloseCallback));
		//CCMenuItemImage *pCloseItem = CCMenuItemImage::create(rcMainMenuItemCloseNormal, rcMainMenuItemCloseSelected, this, menu_selector(MainMenuScene::menuCloseCallback));

		//pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
		pStartItem->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y+50));
		pOptionItem->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y));
		pEndItem->setPosition(ccp(VisibleRect::center().x,VisibleRect::center().y-50));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pStartItem, pOptionItem, pEndItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu, 1);

		// BackGround
		CCSprite* pSprite = CCSprite::create(rcMainMenuBackGround);
		CC_BREAK_IF(! pSprite);

		// Place the sprite on the center of the screen
		//pSprite->setAnchorPoint(ccp(0,0));
		pSprite->setPosition(VisibleRect::center());

		// Add the sprite to HelloWorld layer as a child layer.
		//this->addChild(pSprite, 0);

		bRet = true;
	} while (0);

	return bRet;
}

void MainMenuScene::menuStartCallback(CCObject* pSender)
{
	LevelSelectScene *pScene = new LevelSelectScene();
	if(pScene){
		pScene->runThisTest();
		pScene->release();
	}
}

void MainMenuScene::menuOptionCallback(CCObject* pSender)
{

}

void MainMenuScene::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}

