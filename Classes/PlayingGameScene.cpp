#include "PlayingGameScene.h"
#include "CosLogic.h"
#include "CosResource.h"
#include "tinyxml.h"
#include "tinystr.h"
#include "VisibleRect.h"

#include <string>

#define __KDEBUG__
#ifdef __KDEBUG__
#include <iostream>
#endif

using namespace cocos2d;

static const std::string XML_FILE = "Setting.xml";

void PlayingGameScene::runThisTest()
{
	CCLayer *pLayer = new PlayingGameLayer();
	pLayer->autorelease();
	addChild(pLayer);

	CCDirector::sharedDirector()->replaceScene(this);
}

bool PlayingGameLayer::loadConfigFromFile()
{
	TiXmlDocument *pDoc = new TiXmlDocument(XML_FILE);
	pDoc->LoadFile();
	TiXmlElement *Root = pDoc->RootElement();  //根，<Rank>
	TiXmlElement *pFirE = Root->FirstChildElement(); //叶子节点
	while(NULL != pFirE)
	{
		if (pFirE->ValueStr().compare("VerNum") == 0)
		{
			m_nVerNum = atoi(pFirE->FirstChild()->Value());
		}else if (pFirE->ValueStr().compare("HorNum") == 0)
		{
			m_nHorNum = atoi(pFirE->FirstChild()->Value());
		}else if (pFirE->ValueStr().compare("ImageSize") == 0)
		{
			m_nImageSize = atoi(pFirE->FirstChild()->Value());
		}else if (pFirE->ValueStr().compare("ImageNum") == 0)
		{
			m_nImageNum = atoi(pFirE->FirstChild()->Value());
		}else if (pFirE->ValueStr().compare("NumPerCouple") == 0)
		{
			m_nNumPerCouple = atoi(pFirE->FirstChild()->Value());
		}else
		{
			return false;
		}
		pFirE = pFirE->NextSiblingElement();		
	}
	return true;
}

bool PlayingGameLayer::loadAllImages()
{
	char *pTrName = new char[40];
	int nBoardWidth = m_nHorNum * m_nImageSize;
	int nBoradHeight = m_nVerNum * m_nImageSize;

	int nOriginX = VisibleRect::center().x - (nBoardWidth/2);
	int nOriginY = VisibleRect::center().y - (nBoradHeight/2);

	for (int i=1;i<m_nVerNum+1;i++)
		for (int j=1;j<m_nHorNum+1;j++)
	{
		cosmos::CosGame *pGame = cosmos::CosGame::getInstance();
		cosmos::CosGame::link_t val = pGame->getBoardPosValue(i,j);
		sprintf(pTrName,"elem%d.png",val);

		int nPointX = nOriginX + (j-1)*m_nImageSize;
		int nPointY = nOriginY + (i-1)*m_nImageSize;
		CCSprite* pPic = CCSprite::create(pTrName);
		pPic->retain();
		if(!pPic){
			CCLOG("Error: failed to create sprite.");
			return false;
		}
		m_pAllImages.push_back(pPic);
		pPic->setAnchorPoint(ccp(0,0));
		pPic->setPosition(ccp(nPointX,nPointY));
		addChild(pPic);
	}
	return true;
}

void PlayingGameLayer::onEnter()
{
	CCLayer::onEnter();

	if(!loadConfigFromFile())
		CCLOG("Error: Failed to load config file.");
	#ifdef __KDEBUG__
	std::cout << m_nImageSize << " " << m_nImageNum << std::endl;
	#endif
	//load background
	//create logical board
	cosmos::CosGame::getInstance()->createBoard(m_nHorNum,m_nVerNum,m_nImageNum,m_nNumPerCouple);
	//load all images
	if(!loadAllImages())
		CCLOG("Error: Failed to load images.");
}

void PlayingGameLayer::onExit()
{
	CCLayer::onExit();
}

void PlayingGameLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{

}

void PlayingGameLayer::touchDelegateRetain()
{
	this->retain();
}

void PlayingGameLayer::touchDelegateRelease()
{
	this->release();
}

