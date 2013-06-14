#include "GalleryScene.h"
#include "CosLogic.h"
#include "CosResource.h"
#include "VisibleRect.h"

USING_NS_CC;
USING_NS_CC_EXT;


void GalleryScene::runThisTest()
{
	GalleryLayer *pLayer = GalleryLayer::create();
	this->addChild(pLayer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.5f, this));
}

void CustomTableViewCell::draw()
{
	CCTableViewCell::draw();
	// draw bounding box
// 	CCPoint pos = getPosition();
// 	CCSize size = CCSizeMake(178, 200);
// 	CCPoint vertices[4]={
// 		ccp(pos.x+1, pos.y+1),
// 		ccp(pos.x+size.width-1, pos.y+1),
// 		ccp(pos.x+size.width-1, pos.y+size.height-1),
// 		ccp(pos.x+1, pos.y+size.height-1),
// 	};
// 	ccDrawColor4B(0, 0, 255, 255);
// 	ccDrawPoly(vertices, 4, true);
}

bool GalleryLayer::init()
{
	if ( !CCLayer::init() )
    {
        return false;
    }

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	/*
    CCTableView* tableView = CCTableView::create(this, CCSizeMake(250, 60));
    tableView->setDirection(kCCScrollViewDirectionHorizontal);
    tableView->setPosition(ccp(20,winSize.height/2-30));
    tableView->setDelegate(this);
    this->addChild(tableView);
    tableView->reloadData();
	*/

	float height = (VisibleRect::top().y-VisibleRect::bottom().y)*(2.0/3.0);
	CCTableView* tableView = CCTableView::create(this, CCSizeMake(70, height));
	tableView->setDirection(kCCScrollViewDirectionVertical);
	tableView->setPosition(ccp(VisibleRect::left().x+50,VisibleRect::left().y-height/2));
	//tableView->setAnchorPoint(ccp(1,1));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	this->addChild(tableView,1);
	tableView->reloadData();

	// BackGround
	CCSprite* pSprite = CCSprite::create(rcGalleryBackGround);
	if(pSprite){
		// Place the sprite on the center of the screen
		//pSprite->setAnchorPoint(ccp(0,0));
		pSprite->setPosition(VisibleRect::center());

		// Add the sprite to layer as a child layer.
		this->addChild(pSprite, 0);
	}

    return true;
}

void GalleryLayer::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
	CCLOG("cell touched at index: %i", cell->getIdx());
}

cocos2d::CCSize GalleryLayer::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return CCSizeMake(70, 70);
}

cocos2d::extension::CCTableViewCell* GalleryLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	 CCString *string = CCString::createWithFormat("%d", idx);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CustomTableViewCell();
        cell->autorelease();
        CCSprite *sprite = CCSprite::create("images/LinkObject/elem0-0.png");
        sprite->setAnchorPoint(CCPointZero);
        sprite->setPosition(ccp(0, 0));
        cell->addChild(sprite);

        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
        label->setPosition(CCPointZero);
		label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        cell->addChild(label);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }


    return cell;
}

unsigned int GalleryLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	return 20;
}

