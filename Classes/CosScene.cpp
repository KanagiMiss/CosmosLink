#include "CosScene.h"
#include "CosLogic.h"
#include "MainMenuScene.h"
#include "CosResource.h"
#include "VisibleRect.h"

using namespace cocos2d;

CosScene::CosScene(bool bPortrait)
{
    CCScene::init();
}

void CosScene::onEnter()
{
    CCScene::onEnter();

    //add the menu item for back to main menu
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
//    CCLabelBMFont* label = CCLabelBMFont::create("MainMenu",  "fonts/arial16.fnt");
//#else
    //CCLabelTTF* label = CCLabelTTF::create("MainMenu", "Arial", 20);
//#endif
    //CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(CosScene::MainMenuCallback));
	CCMenuItemImage *pMMItem = CCMenuItemImage::create(rcMainMenuNormal, rcMainMenuSelected, this, menu_selector(CosScene::MainMenuCallback));
    CCMenu* pMenu =CCMenu::create(pMMItem, NULL);

    pMenu->setPosition( CCPointZero );
    pMMItem->setPosition( ccp( VisibleRect::right().x - 75, VisibleRect::bottom().y + 25) );

    addChild(pMenu, 1);
}

void CosScene::MainMenuCallback(CCObject* pSender)
{
	cosmos::CosGame *pGame = cosmos::CosGame::getInstance();
	pGame->endGame();

    CCScene* pScene = CCScene::create();
	MainMenuScene* pLayer = MainMenuScene::create();

    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
}