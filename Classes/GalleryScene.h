#ifndef __GALLERYSCENE_H__
#define __GALLERYSCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "CosScene.h"
#include "CosLogic.h"

class GalleryScene: public CosScene
{
public:
	virtual void runThisTest();
};

/*
class CustomTableViewCell : public cocos2d::extension::CCTableViewCell
{
public:
	virtual void draw();
};
*/

class GalleryLayer: public cocos2d::CCLayer/*, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate*/
{
public:
    virtual bool init();  
   
	//void toExtensionsMainLayer(cocos2d::CCObject *sender);

    CREATE_FUNC(GalleryLayer);
    
    //virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    //virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    //virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);//ͼ���˵������
    //virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);//ÿ��ͼ���˵��Ĵ�С
    //virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);//ÿ��ͼ���˵��ĳ�ʼ��
    //virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);//ͼ������

private:
};

#endif  // __GALLERYSCENE_H__