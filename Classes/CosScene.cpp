#include "CosScene.h"
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
    CCLabelTTF* label = CCLabelTTF::create("MainMenu", "Arial", 20);
//#endif
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(CosScene::MainMenuCallback));

    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);

    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( ccp( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );

    addChild(pMenu, 1);
}

void CosScene::MainMenuCallback(CCObject* pSender)
{
    CCScene* pScene = CCScene::create();
	MainMenuScene* pLayer = MainMenuScene::create();

    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
}