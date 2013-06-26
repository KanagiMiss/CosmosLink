#pragma once

#ifndef __GAMEENDSCENE_H__
#define __GAMEENDSCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

class GameEndScene :
	public cocos2d::CCLayer
{
public:
	GameEndScene(void);
	virtual ~GameEndScene(void);

    virtual void onEnter();
    virtual void onExit();

	void backToMenuCallback(CCObject* pSender);
	void restartCallback(CCObject* pSender);
	void updateGallery();

    // implement the "static node()" method manually
    CREATE_FUNC(GameEndScene);

private:
};

#endif /*__GAMEENDSCENE_H__*/
