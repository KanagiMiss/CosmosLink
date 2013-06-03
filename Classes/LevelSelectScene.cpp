#include "LevelSelectScene.h"
#include "CosLogic.h"
#include "CosResource.h"
#include "VisibleRect.h"

using namespace cocos2d;

CCLayer* NextAction();
CCLayer* BackAction();
CCLayer* RestartAction();

static int s_nActionIdx = -1;

CCLayer* CreateLayer(int nIndex)
{
    CCLayer * pLayer = NULL;

    switch (nIndex)
    {
	case 0:
		pLayer = new LevelSelectLayer(rcLevel0Capture);
		break;
	case 1:
		pLayer = new LevelSelectLayer(rcLevel1Capture);
		break;
	case 2:
		pLayer = new LevelSelectLayer(rcLevel2Capture);
		break;
	case 3:
		pLayer = new LevelSelectLayer(rcLevel3Capture);
		break;
	case 4:
		pLayer = new LevelSelectLayer(rcLevel4Capture);
		break;
	case 5:
		pLayer = new LevelSelectLayer(rcLevel5Capture);
		break;
	case 6:
		pLayer = new LevelSelectLayer(rcLevel6Capture);
		break;
	case 7:
		pLayer = new LevelSelectLayer(rcLevel7Capture);
		break;
	case 8:
		pLayer = new LevelSelectLayer(rcLevel8Capture);
		break;
	default:break;
    }

    return pLayer;
}

CCLayer* NextAction()
{
    ++s_nActionIdx;
    s_nActionIdx = s_nActionIdx % LAYER_COUNT;

    CCLayer* pLayer = CreateLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* BackAction()
{
    --s_nActionIdx;
    if( s_nActionIdx < 0 )
        s_nActionIdx += LAYER_COUNT;    

    CCLayer* pLayer = CreateLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* RestartAction()
{
    CCLayer* pLayer = CreateLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}


void LevelSelectScene::runThisTest()
{
	s_nActionIdx = -1;
    addChild(NextAction());

    CCDirector::sharedDirector()->replaceScene(this);
}

LevelSelectLayer::LevelSelectLayer(std::string name):
	capture_name(name)
{
}

void LevelSelectLayer::onEnter()
{
	CCLayer::onEnter();

	// add menu
    CCMenuItemImage *item1 = CCMenuItemImage::create(rcLevelSelectBackNormal, rcLevelSelectBackSelect, this, menu_selector(LevelSelectLayer::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create(rcLevelSelectEnterNormal, rcLevelSelectEnterSelect, this, menu_selector(LevelSelectLayer::enterCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create(rcLevelSelectNextNormal, rcLevelSelectNextSelect, this, menu_selector(LevelSelectLayer::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition(CCPointZero);
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

    addChild(menu, 0);

	CCSprite* pSprite = CCSprite::create(capture_name.c_str());

	// Place the sprite on the center of the screen
	//pSprite->setAnchorPoint(ccp(0,0));
	pSprite->setPosition(VisibleRect::center());

	// Add the sprite to HelloWorld layer as a child layer.
	addChild(pSprite, 1);
}

void LevelSelectLayer::onExit()
{
	CCLayer::onExit();
}

void LevelSelectLayer::enterCallback(CCObject* pSender)
{

}

void LevelSelectLayer::nextCallback(CCObject* pSender)
{
	CCScene* s = new LevelSelectScene();
    s->addChild( NextAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void LevelSelectLayer::backCallback(CCObject* pSender)
{
	CCScene* s = new LevelSelectScene();
    s->addChild( BackAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}
