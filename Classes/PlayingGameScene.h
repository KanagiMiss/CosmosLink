#ifndef __PLAYINGGAMESCENE_H__
#define __PLAYINGGAMESCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "CosScene.h"
#include "CosLogic.h"
#include <vector>

class PlayingGameScene: public CosScene
{
public:
	virtual void runThisTest();
};

class PlayingGameLayer: public cocos2d::CCLayer, public cocos2d::CCTargetedTouchDelegate
{
public:
	virtual void onEnter();
    virtual void onExit();
	virtual void draw();

	bool loadConfigFromFile();
	bool loadAllImages();
	cocos2d::CCPoint convertoBoardPoint(const cocos2d::CCPoint &p);
	void updateAndRender(const cocos2d::CCPoint &p);
	void selectLink(int nIndex);
	void unSelectLink(int nIndex);

	//touch
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	/*virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);*/
	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();

private:
	std::vector<cocos2d::CCSprite *> m_pAllImages;//存储所有连连看图像指针
	int m_nVerNum;//纵向连连看个数
	int m_nHorNum;//横向连连看个数
	int m_nImageSizeDraw;//连连图像画时的大小
	int m_nImageSizeReal;//连连看图像真实大小
	int m_nImageNum;//连连看种数
	int m_nNumPerCouple;//连连看对数

	int m_nBoardWidth;//连连看面板宽度
	int m_nBoradHeight;//连连看面板高度
	int m_nOriginX; //连连看组在屏幕上的原始坐标x
	int m_nOriginY; //连连看组在屏幕上的原始坐标y

	bool m_bFirstClick; //是否第一次点击
	//bool m_bSecondClick;
	bool m_bFirstSelect; //是否选定第一个连连看方块
	bool m_bSecondSelect;//是否选定第二个连连看方块
	cocos2d::CCPoint m_ptFirstClick;//选定的第一个连连看方块在Board上的坐标
	cocos2d::CCPoint m_ptSecondClick;//选定的第二个连连看方块在Board上的坐标
};

class GameEndLayer: public cocos2d::CCLayer
{
public:
	virtual void onEnter();
    virtual void onExit();

private:
};

#endif  // __PLAYINGGAMESCENE_H__