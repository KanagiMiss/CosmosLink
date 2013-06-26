#include "OptionScene.h"
#include "CosLogic.h"
#include "CosResource.h"
#include "VisibleRect.h"
#include "KUtils.h"

USING_NS_CC;
USING_NS_CC_EXT;

void addBotton(CCObject *pObj, CCNode *pLayer, CCPoint ptLoc, CCLabelTTF *pDisplayValueLabel,
               void (OptionLayer::* CALL_BACK_FUN)(CCObject* sender, CCControlEvent controlEvent))
{
		
}

void OptionScene::runThisTest()
{
	OptionLayer *pLayer = OptionLayer::create();
	this->addChild(pLayer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.5f, this));
}

OptionLayer::~OptionLayer()
{
	 CC_SAFE_RELEASE(m_pDisplayValueLabel_SFX);
	 CC_SAFE_RELEASE(m_pDisplayValueLabel_MUSIC);
}

bool OptionLayer::init()
{
	if (CCLayer::init())
    {
        CCNode *layer = CCNode::create();
        layer->setPosition(VisibleRect::center());
		// Set the layer size
        layer->setContentSize(CCSizeMake(VisibleRect::center().x, VisibleRect::center().y));
        layer->setAnchorPoint(ccp (0.5f, 0.5f));
        addChild(layer, 1);
		
		CCPoint origin;
		cosmos::CosGame *pGame = cosmos::CosGame::getInstance();

		/////////////////////////////////////// Add sfx btn ///////////////////////////////////////
		// Add the black background for the text
		origin = ccp(VisibleRect::left().x,VisibleRect::left().y/2+80);
		CCLabelBMFont *pLabelSFX = CCLabelBMFont::labelWithString("SFX", rcImageFont40);
		pLabelSFX->setPosition(origin);
		layer->addChild(pLabelSFX);

		origin = ccp(VisibleRect::left().x,VisibleRect::left().y/2-30);
        CCScale9Sprite *background = CCScale9Sprite::create(rcOptionButtonBKG);
        background->setContentSize(CCSizeMake(80, 50));
		background->setPosition(ccp(origin.x, origin.y));
        layer->addChild(background);
        
        
        m_pDisplayValueLabel_SFX  = CCLabelTTF::create("#color" ,"Marker Felt" ,30);
        m_pDisplayValueLabel_SFX->retain();

        m_pDisplayValueLabel_SFX->setPosition(background->getPosition());
        layer->addChild(m_pDisplayValueLabel_SFX);
        
        // Create the switch
        CCControlSwitch *switchControl = CCControlSwitch::create
            (
                CCSprite::create(rcOptionSwitchMask),
                CCSprite::create(rcOptionSwitchOn),
                CCSprite::create(rcOptionSwitchOff),
                CCSprite::create(rcOptionSwitchThumb),
                CCLabelTTF::create("On", "Arial-BoldMT", 16),
                CCLabelTTF::create("Off", "Arial-BoldMT", 16)
            );
        switchControl->setPosition(ccp (origin.x+80, origin.y));
        layer->addChild(switchControl);

        switchControl->addTargetWithActionForControlEvents(this, cccontrol_selector(OptionLayer::valueChangedSFX), CCControlEventValueChanged);
		switchControl->setOn(pGame->getConfig().isSFXOn);

        // Update the value label
        valueChangedSFX(switchControl, CCControlEventValueChanged);


		/////////////////////////////////////// Add music btn ///////////////////////////////////////
		
		origin = ccp(VisibleRect::right().x/2-100,VisibleRect::right().y/2+80);
		CCLabelBMFont *pLabelMUSIC = CCLabelBMFont::labelWithString("MUSIC", rcImageFont40);
		pLabelMUSIC->setPosition(origin);
		layer->addChild(pLabelMUSIC);

		origin = ccp(VisibleRect::right().x/2-120,VisibleRect::right().y/2-30);
		background = CCScale9Sprite::create(rcOptionButtonBKG);
        background->setContentSize(CCSizeMake(80, 50));
		background->setPosition(ccp(origin.x, origin.y));
        layer->addChild(background);

		m_pDisplayValueLabel_MUSIC  = CCLabelTTF::create("#color" ,"Marker Felt" ,30);
        m_pDisplayValueLabel_MUSIC->retain();

        m_pDisplayValueLabel_MUSIC->setPosition(background->getPosition());
        layer->addChild(m_pDisplayValueLabel_MUSIC);
        
        // Create the switch
        switchControl = CCControlSwitch::create
            (
                CCSprite::create(rcOptionSwitchMask),
                CCSprite::create(rcOptionSwitchOn),
                CCSprite::create(rcOptionSwitchOff),
                CCSprite::create(rcOptionSwitchThumb),
                CCLabelTTF::create("On", "Arial-BoldMT", 16),
                CCLabelTTF::create("Off", "Arial-BoldMT", 16)
            );
        switchControl->setPosition(ccp (origin.x+80, origin.y));
        layer->addChild(switchControl);

        switchControl->addTargetWithActionForControlEvents(this, cccontrol_selector(OptionLayer::valueChangedMUSIC), CCControlEventValueChanged);
		switchControl->setOn(pGame->getConfig().isMusicOn);

        // Update the value label
        valueChangedMUSIC(switchControl, CCControlEventValueChanged);

		// BackGround
		CCSprite* pSprite = CCSprite::create(rcOptionBackGround);
		if(pSprite){
			// Place the sprite on the center of the screen
			//pSprite->setAnchorPoint(ccp(0,0));
			pSprite->setPosition(VisibleRect::center());

			// Add the sprite to layer as a child layer.
			this->addChild(pSprite, 0);
		}

        return true;
    }
    return false;
}

void OptionLayer::valueChangedSFX(CCObject* sender, CCControlEvent controlEvent)
{
	CCControlSwitch* pSwitch = (CCControlSwitch*)sender;
	cosmos::CosGame *pGame = cosmos::CosGame::getInstance();
	cosmos::COSCONFIG config = pGame->getConfig();
    if (pSwitch->isOn())
    {
        m_pDisplayValueLabel_SFX->setString("On");
		config.isSFXOn = true;
    } 
    else
    {
        m_pDisplayValueLabel_SFX->setString("Off");
		config.isSFXOn = false;
    }
	pGame->saveConfig(config);
}

void OptionLayer::valueChangedMUSIC(cocos2d::CCObject* sender, cocos2d::extension::CCControlEvent controlEvent)
{
	CCControlSwitch* pSwitch = (CCControlSwitch*)sender;
	cosmos::CosGame *pGame = cosmos::CosGame::getInstance();
	cosmos::COSCONFIG config = pGame->getConfig();
    if (pSwitch->isOn())
    {
        m_pDisplayValueLabel_MUSIC->setString("On");
		config.isMusicOn = true;
		KUtils::playMusic(rcSoundMainBGM);
    } 
    else
    {
        m_pDisplayValueLabel_MUSIC->setString("Off");
		config.isMusicOn = false;
		KUtils::stopMusic();
    }
	pGame->saveConfig(config);
}
