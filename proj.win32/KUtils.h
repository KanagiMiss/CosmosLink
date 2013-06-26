#pragma once

#ifndef _KUTILS_H_
#define _KUTILS_H_

#include "windows.h"
#include <string>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CosLogic.h"

using namespace cosmos;
using namespace cocos2d;
using namespace CocosDenshion;

#define SaveStringToXML cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey
#define SaveIntegerToXML cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey
#define SaveDoubleToXML cocos2d::CCUserDefault::sharedUserDefault()->setDoubleForKey
#define SaveBooleanToXML cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey
#define SaveStringToXML cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey
#define SaveIntegerToXML cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey
#define SaveBooleanToXML cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey

#define LoadStringFromXML cocos2d::CCUserDefault::sharedUserDefault()->getStringForKey
#define LoadIntegerFromXML cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey
#define LoadDoubleFromXML cocos2d::CCUserDefault::sharedUserDefault()->getDoubleForKey
#define LoadBooleanFromXML cocos2d::CCUserDefault::sharedUserDefault()->getBoolForKey
#define LoadStringFromXML cocos2d::CCUserDefault::sharedUserDefault()->getStringForKey
#define LoadIntegerFromXML cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey
#define LoadBooleanFromXML cocos2d::CCUserDefault::sharedUserDefault()->getBoolForKey


namespace KUtils{

inline bool isSFXOn()
{
	CosGame *pGame = CosGame::getInstance();
	cosmos::COSCONFIG config = pGame->getConfig();
	return config.isSFXOn;
}

inline bool isMusicOn()
{
	CosGame *pGame = CosGame::getInstance();
	cosmos::COSCONFIG config = pGame->getConfig();
	return config.isMusicOn;
}

inline void loadSound(const char *pName)
{
	SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pName) );
}

inline void playSound(const char *pName)
{
	if(isSFXOn())
		SimpleAudioEngine::sharedEngine()->playEffect(std::string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pName)).c_str());
}

inline void loadMusic(const char *pName)
{
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pName) );
}

inline void playMusic(const char *pName)
{
	if(isMusicOn())
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(std::string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pName)).c_str(), true);
}

inline void stopMusic()
{
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

inline std::string WideByte2UTF8(const std::wstring& text)
{
	int asciisize = ::WideCharToMultiByte(CP_UTF8, 0, text.c_str(), text.size(), NULL, 0, NULL, NULL);
	if (asciisize == ERROR_NO_UNICODE_TRANSLATION ||
		asciisize == 0)  
	{
		return std::string();
	}
	char* resultstring = new char[asciisize];
	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, text.c_str(), text.size(), resultstring, asciisize, NULL, NULL);
	if (convresult != asciisize)
	{  
		return std::string();
	}  
	std::string buffer(resultstring, convresult);
	delete[] resultstring;
	return buffer;
}

} /*Kanagi Utils*/

#endif /*_KUTILS_H_*/