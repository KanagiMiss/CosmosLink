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

	bool loadConfigFromFile();
	bool loadAllImages();

	//touch
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	/*virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);*/
	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();

private:
	std::vector<cocos2d::CCSprite *> m_pAllImages;
	int m_nVerNum;
	int m_nHorNum;
	int m_nImageSize;
	int m_nImageNum;
	int m_nNumPerCouple;
};

#endif  // __PLAYINGGAMESCENE_H__