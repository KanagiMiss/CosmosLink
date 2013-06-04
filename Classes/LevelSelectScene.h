#ifndef __LEVELSELECTSCENE_H__
#define __LEVELSELECTSCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "CosScene.h"
#include "CosLogic.h"
#include <string>

class LevelSelectScene: public CosScene
{
public:
	virtual void runThisTest();
};

class LevelSelectLayer: public cocos2d::CCLayer
{
public:
	LevelSelectLayer(std::string name);

	virtual void onEnter();
    virtual void onExit();

    void enterCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);

private:
	std::string capture_name;
};

#endif  // __LEVELSELECTSCENE_H__