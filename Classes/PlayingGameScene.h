#ifndef __PLAYINGGAMESCENE_H__
#define __PLAYINGGAMESCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "CosScene.h"
#include "CosLogic.h"

class PlayingGameScene: public CosScene
{
	virtual void runThisTest();
};

class PlayingGameLayer: public cocos2d::CCLayer
{
public:
	virtual void onEnter();
    virtual void onExit();

private:
	Game_Level level;
};

#endif  // __PLAYINGGAMESCENE_H__