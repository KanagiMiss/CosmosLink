#ifndef __DIFFICULTYSCENE_H__
#define __DIFFICULTYSCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "CosScene.h"
#include "CosLogic.h"

class DifficultyScene: public CosScene
{
public:
	virtual void runThisTest();
};

class DifficultyLayer: public cocos2d::CCLayer
{
public:
	virtual void onEnter();
    virtual void onExit();

	void EasyCallback(CCObject* pSender);
	void NormalCallback(CCObject* pSender);
	void HardCallback(CCObject* pSender);

	void goToNextScene();

private:
};

#endif  // __DIFFICULTYSCENE_H__