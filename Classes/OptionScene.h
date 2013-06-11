#ifndef __OPTIONSCENE_H__
#define __OPTIONSCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "CosScene.h"
#include "CosLogic.h"

class OptionScene: public CosScene
{
public:
	virtual void runThisTest();
};

class OptionLayer: public cocos2d::CCLayer
{
public:
	virtual ~OptionLayer();

	CREATE_FUNC(OptionLayer)
	virtual bool init();

	/** Callback for the change value. */
	void valueChangedSFX(cocos2d::CCObject* sender, cocos2d::extension::CCControlEvent controlEvent);
	void valueChangedMUSIC(cocos2d::CCObject* sender, cocos2d::extension::CCControlEvent controlEvent);
    cocos2d::CCLabelTTF *m_pDisplayValueLabel_SFX;
	cocos2d::CCLabelTTF *m_pDisplayValueLabel_MUSIC;
private:
};

#endif  // __OPTIONSCENE_H__