#ifndef __COSSCENE_H__
#define __COSSCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

class CosScene: public cocos2d::CCScene
{
public: 
    CosScene(bool bPortrait = false);
    virtual void onEnter();

    virtual void runThisTest() = 0;

    // The CallBack for back to the main menu scene
    virtual void MainMenuCallback(CCObject* pSender);
};

#endif  // __COSSCENE_H__