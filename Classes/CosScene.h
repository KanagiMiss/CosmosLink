#ifndef __COSSCENE_H__
#define __COSSCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#define TRANSITION_DURATION (1.5f)

class CosScene: public cocos2d::CCScene
{
public: 
    CosScene(bool bPortrait = false);
    virtual void onEnter();

    virtual void runThisTest() = 0;

    // The CallBack for back to the main menu scene
    virtual void MainMenuCallback(CCObject* pSender);
};

class PageTransitionForward : public cocos2d::CCTransitionPageTurn
{
public:
    static cocos2d::CCTransitionScene* create(float t, cocos2d::CCScene* s)
    {
        cocos2d::CCDirector::sharedDirector()->setDepthTest(true);
        return cocos2d::CCTransitionPageTurn::create(t, s, false);
    }
};

class PageTransitionBackward : public cocos2d::CCTransitionPageTurn
{
public:
    static cocos2d::CCTransitionScene* create(float t, cocos2d::CCScene* s)
    {
        cocos2d::CCDirector::sharedDirector()->setDepthTest(true);
        return cocos2d::CCTransitionPageTurn::create(t, s, true);
    }
};

class FadeWhiteTransition : public cocos2d::CCTransitionFade 
{
public:
    static cocos2d::CCTransitionScene* create(float t, cocos2d::CCScene* s)
    {
        return cocos2d::CCTransitionFade::create(t, s, cocos2d::ccWHITE); 
    }
};


#endif  // __COSSCENE_H__