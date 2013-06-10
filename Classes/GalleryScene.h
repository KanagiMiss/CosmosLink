#ifndef __GALLERYSCENE_H__
#define __GALLERYSCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "CosScene.h"
#include "CosLogic.h"

class GalleryScene: public CosScene
{
public:
	virtual void runThisTest();
};

class GalleryLayer: public cocos2d::CCLayer
{
public:
	virtual void onEnter();
    virtual void onExit();

private:
};

#endif  // __GALLERYSCENE_H__