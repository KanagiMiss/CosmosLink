#include "PlayingGameScene.h"
#include "GameEndScene.h"
#include "CosLogic.h"
#include "CosResource.h"
#include "tinyxml.h"
#include "tinystr.h"
#include "VisibleRect.h"
#include "CosResource.h"

#include <string>
#include <cmath>

#define __KDEBUG__
#ifdef __KDEBUG__
#include <iostream>
#endif

using namespace cocos2d;

static const std::string XML_FILE = rcCosData;

void PlayingGameScene::runThisTest()
{
	CCLayer *pLayer = new PlayingGameLayer();
	pLayer->autorelease();
	addChild(pLayer);

	CCDirector::sharedDirector()->replaceScene(FadeWhiteTransition::create(0.4f,this));
}

bool PlayingGameLayer::loadConfigFromFile()
{
	TiXmlDocument *pDoc = new TiXmlDocument(XML_FILE);
	pDoc->LoadFile();
	TiXmlElement *Root = pDoc->RootElement();  //根，<Rank>
	TiXmlNode *Child = Root->FirstChild("Easy");
	switch(pGame->getDiffculty())
	{
	case cosmos::EASY:
		Child = Root->FirstChild("Easy");
		break;
	case cosmos::NORMAL:
		Child = Root->FirstChild("Normal");
		break;
	case cosmos::HARD:
		Child = Root->FirstChild("Hard");
		break;
	}
	TiXmlElement *pFirE = Child->FirstChildElement(); //叶子节点
	while(NULL != pFirE)
	{
		if (pFirE->ValueStr().compare("VerNum") == 0)
		{
			m_nVerNum = atoi(pFirE->FirstChild()->Value());
		}else if (pFirE->ValueStr().compare("HorNum") == 0)
		{
			m_nHorNum = atoi(pFirE->FirstChild()->Value());
		}else if (pFirE->ValueStr().compare("ImageSizeDraw") == 0)
		{
			m_nImageSizeDraw = atoi(pFirE->FirstChild()->Value());
		}else if (pFirE->ValueStr().compare("ImageSizeReal") == 0)
		{
			m_nImageSizeReal = atoi(pFirE->FirstChild()->Value());
		}else if (pFirE->ValueStr().compare("ImageNum") == 0)
		{
			m_nImageNum = atoi(pFirE->FirstChild()->Value());
		}else if (pFirE->ValueStr().compare("NumPerCouple") == 0)
		{
			m_nNumPerCouple = atoi(pFirE->FirstChild()->Value());
		}else if (pFirE->ValueStr().compare("GameTime") == 0)
		{
			m_lfTimeLimit = atoi(pFirE->FirstChild()->Value());
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
	m_nBoardWidth = m_nHorNum * m_nImageSizeDraw;
	m_nBoradHeight = m_nVerNum * m_nImageSizeDraw;

	m_nOriginX = VisibleRect::center().x - (m_nBoardWidth/2);
	m_nOriginY = VisibleRect::center().y - (m_nBoradHeight/2);

	int nLevelNum = static_cast<int>(pGame->getGameLevel());//游戏关卡索引值
	for (int i=1;i<m_nVerNum+1;i++)
		for (int j=1;j<m_nHorNum+1;j++)
	{
		cosmos::CosGame::link_t val = pGame->getBoardPosValue(i,j);
		sprintf(pTrName,rcLinkImages,/*nLevelNum,*/val);

		int nPointX = m_nOriginX + (j-1)*m_nImageSizeDraw;
		int nPointY = m_nOriginY + (i-1)*m_nImageSizeDraw;
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

	//load background
	sprintf(pTrName,rcPlayingGameBackGround,nLevelNum);
	CCSprite* pSprite = CCSprite::create(pTrName);
	if(pSprite){
		// Place the sprite on the center of the screen
		//pSprite->setAnchorPoint(ccp(0,0));
		pSprite->setPosition(VisibleRect::center());

		// Add the sprite to layer as a child layer.
		this->addChild(pSprite, 0);
	}

	return true;
}

void PlayingGameLayer::selectLink(int nIndex)
{
	if(nIndex == 0)
		m_bFirstSelect = true;
	else if(nIndex == 1)
		m_bSecondSelect = true;
}

void PlayingGameLayer::unSelectLink(int nIndex)
{
	if(nIndex == 0)
		m_bFirstSelect = false;
	else if(nIndex == 1)
		m_bSecondSelect = false;
}

void PlayingGameLayer::draw()
{
	int ptFirstInBoardX = static_cast<int>(m_ptFirstClick.x) - 1,
		ptFirstInBoardY = static_cast<int>(m_ptFirstClick.y) - 1,
		ptSecondInBoardX = static_cast<int>(m_ptSecondClick.x) - 1,
		ptSecondInBoardY = static_cast<int>(m_ptSecondClick.y) - 1;
	if(m_bFirstSelect)
		for(int d = 0; d < 5; ++d)
			ccDrawRect(ccp(m_nOriginX+ptFirstInBoardX*m_nImageSizeDraw-d, m_nOriginY+ptFirstInBoardY*m_nImageSizeDraw-d),
			           ccp(m_nOriginX+ptFirstInBoardX*m_nImageSizeDraw+m_nImageSizeReal+d, m_nOriginY+ptFirstInBoardY*m_nImageSizeDraw+m_nImageSizeReal+d));
			//ccDrawRect(ccp(m_nOriginX*ptFirstInBoardX+d, m_nOriginY*ptFirstInBoardY+d),
			  //         ccp(m_nOriginX*ptFirstInBoardX+m_nImageSizeDraw-d, m_nOriginY*ptFirstInBoardY+m_nImageSizeDraw-d));
	if(m_bSecondSelect)
		for(int d = 0; d < 5; ++d)
			ccDrawRect(ccp(m_nOriginX*ptSecondInBoardX+d, m_nOriginY*ptSecondInBoardY+d),
			           ccp(m_nOriginX*ptSecondInBoardX+m_nImageSizeDraw-d, m_nOriginY*ptSecondInBoardY+m_nImageSizeDraw-d));
}

void PlayingGameLayer::onEnter()
{
	CCLayer::onEnter();

	m_bFirstClick = false;
    //m_bSecondClick = false;
	m_bFirstSelect = false;
	m_bSecondSelect = false;
	m_lfRewardInc = 0;
	isChangeScore = false;
	pGame = cosmos::CosGame::getInstance();

	//make this layer to be touchable
	this->setTouchEnabled(true);
	
	//load configure
	if(!loadConfigFromFile())
		CCLOG("Error: Failed to load config file.");
	#ifdef __KDEBUG__
	std::cout << m_nImageSizeDraw << " " << m_nImageNum << std::endl;
	#endif
	//init current time (must be at here!)
	m_lfCurrTime = m_lfTimeLimit;
	//load background
	//create logical board
	cosmos::CosGame::getInstance()->createBoard(m_nHorNum,m_nVerNum,m_nImageNum,m_nNumPerCouple);
	//load all images
	if(!loadAllImages())
		CCLOG("Error: Failed to load images.");

	//set initial score
	char tempstr[20];
	_itoa(cosmos::CosGame::getInstance()->getGameTime(),tempstr,10);
	pScore = CCLabelTTF::create(tempstr, "Arial", 25);
	pScore->setPosition(VisibleRect::rightTop());
	pScore->setAnchorPoint(ccp(1,1));
	addChild(pScore,1);
	//set initial time
	sprintf(tempstr,"%.2lf",m_lfTimeLimit - pGame->getGameTime());
	pTimer = CCLabelTTF::create(tempstr, "Arial", 25);
	pTimer->setPosition(VisibleRect::leftTop());
	pTimer->setAnchorPoint(ccp(0,1));
	if(pGame->getDiffculty() == cosmos::HARD)
		addChild(pTimer,1);
	//set game loop
	this->schedule(schedule_selector(PlayingGameLayer::GameLoop),0.1f);
}

void PlayingGameLayer::onExit()
{
	CCLayer::onExit();
}

cocos2d::CCPoint PlayingGameLayer::convertoBoardPoint(const cocos2d::CCPoint &p)
{
	CCPoint point;
	point.x = static_cast<int>((p.x-m_nOriginX)/m_nImageSizeDraw + 1);
	point.y = static_cast<int>((p.y-m_nOriginY)/m_nImageSizeDraw + 1);
	return point;
}

void PlayingGameLayer::GameLoop(float f)
{
	//update logical time (real time)
	pGame->incGameTime(f);
	//update game time (include reward time)
	m_lfCurrTime -= f;
	if(pGame->getDiffculty() == cosmos::HARD)
		updateTime();
	if(m_lfCurrTime < 0 && (pGame->getDiffculty() == cosmos::HARD)){
		gotoEndGameScene(false);//failed
		return;
	}
	if(isChangeScore){
		runChangeScore();
	}
}

void PlayingGameLayer::updateTime()
{
		char tempstr[20]={};
		sprintf(tempstr,"%.2lf",m_lfCurrTime);
		pTimer->setString(tempstr);
}

void PlayingGameLayer::runChangeScore()
{
	int tempScore = atoi(pScore->getString());
	int addScore = nDstScore-tempScore;
	char tempStr[20]={};
	#ifdef __KDEBUG__
	std::cout << tempScore << " " << nDstScore <<std::endl;
	#endif
	if(abs(addScore)>10)
	{
		tempScore+=addScore/5;
		sprintf(tempStr,"%d",tempScore);
		pScore->setString(tempStr);
	}
	else if(abs(addScore)>2 && abs(addScore)<=10)
	{
		tempScore += addScore/abs(addScore);
		sprintf(tempStr,"%d",tempScore);
		pScore->setString(tempStr);
	}
	else
	{
		sprintf(tempStr,"%d",nDstScore);
		pScore->setString(tempStr);
		isChangeScore = false;
	}
}

void PlayingGameLayer::changeScoreTo(int nDstScore)
{	
	isChangeScore = true;
	this->nDstScore = nDstScore;
}

void PlayingGameLayer::updateAndRender(const cocos2d::CCPoint &p)
{
	CCPoint BoardPoint = convertoBoardPoint(p);
	bool isInLink = pGame->isInLinkArea(static_cast<int>(BoardPoint.x),static_cast<int>(BoardPoint.y));

#ifdef __KDEBUG__
	if(!isInLink)
		std::cout << "Not in link area." << std::endl;
	else{
		std::cout << "In the link area." << std::endl;

		//test begin
		//int x = static_cast<int>(BoardPoint.x) - 1,
		//	y = static_cast<int>(BoardPoint.y) - 1;
		//this->removeChild(m_pAllImages[y*m_nHorNum + x],true);
		//test end
	}
#endif

	if(!isInLink){
		if(m_bFirstClick){
			m_bFirstClick = false;
			unSelectLink(0);
		}
		return;
	}

	if(!m_bFirstClick){
		m_bFirstClick = true;
		m_ptFirstClick = BoardPoint;
		selectLink(0);
	}
	else{
		m_bFirstClick = false;
		m_ptSecondClick = BoardPoint;
		selectLink(1);
		int x1 = static_cast<int>(m_ptFirstClick.x),
			y1 = static_cast<int>(m_ptFirstClick.y),
			x2 = static_cast<int>(m_ptSecondClick.x),
			y2 = static_cast<int>(m_ptSecondClick.y);
		if(pGame->isLinkable(x1, y1, x2, y2)){
			//消去连连看方块
			pGame->setLinkNull(x1,y1);
			pGame->setLinkNull(x2,y2);
			this->removeChild(m_pAllImages[(y1-1)*m_nHorNum + (x1-1)],true);
			this->removeChild(m_pAllImages[(y2-1)*m_nHorNum + (x2-1)],true);
			//时间奖励
			m_lfRewardInc += 1;
			double incTime = 0.5+2.5*(1-exp(-m_lfRewardInc*0.2));
			incTime = ((m_lfCurrTime + incTime)>m_lfTimeLimit)?0:incTime;
			m_lfCurrTime += incTime;//inc = 0.5 + 2.5*(1-exp(-x*0.2))
			//分数奖励
			pGame->addGameScore(50+50*(1-exp(-m_lfRewardInc*0.2)));
			changeScoreTo(pGame->getGameScore());
			//检测游戏是否赢		
			if(pGame->isAllClear()){
				gotoEndGameScene(true);
				return;
			}
			//检测游戏是否能继续
			if(!pGame->isContinuable()){
				gotoEndGameScene(false);//failed
				return;
			}
		}
		else{
			m_lfRewardInc = 0;
		}
		unSelectLink(0);
		unSelectLink(1);
	}
}

void PlayingGameLayer::gotoEndGameScene(bool succeed)
{
	if(succeed)
		pGame->winGame();
	else
		pGame->loseGame();
	CCScene *pScene = CCScene::create();
	GameEndScene *pLayer = GameEndScene::create();
	pScene->addChild(pLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void PlayingGameLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* pTouch = (CCTouch*)(*it);

	CCPoint touchLocation = /*pTouch->locationInView(pTouch->view())*/pTouch->getPreviousLocationInView();
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);

#ifdef __KDEBUG__
	std::cout << "Touch point:" << "(" << touchLocation.x << "," << touchLocation.y << ")" << std::endl;
#endif

	updateAndRender(touchLocation);
}

void PlayingGameLayer::touchDelegateRetain()
{
	this->retain();
}

void PlayingGameLayer::touchDelegateRelease()
{
	this->release();
}

