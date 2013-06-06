#ifndef __PLAYINGGAMESCENE_H__
#define __PLAYINGGAMESCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "CosScene.h"
#include "CosLogic.h"
#include <vector>

class PlayingGameScene: public CosScene
{
public:
	virtual void runThisTest();
};

class PlayingGameLayer: public cocos2d::CCLayer, public cocos2d::CCTargetedTouchDelegate
{
public:
	virtual void onEnter();
    virtual void onExit();
	virtual void draw();

	bool loadConfigFromFile();
	bool loadAllImages();
	cocos2d::CCPoint convertoBoardPoint(const cocos2d::CCPoint &p);
	void updateAndRender(const cocos2d::CCPoint &p);
	void selectLink(int nIndex);
	void unSelectLink(int nIndex);

	//touch
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	/*virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);*/
	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();

private:
	std::vector<cocos2d::CCSprite *> m_pAllImages;//�洢����������ͼ��ָ��
	int m_nVerNum;//��������������
	int m_nHorNum;//��������������
	int m_nImageSizeDraw;//����ͼ��ʱ�Ĵ�С
	int m_nImageSizeReal;//������ͼ����ʵ��С
	int m_nImageNum;//����������
	int m_nNumPerCouple;//����������

	int m_nBoardWidth;//�����������
	int m_nBoradHeight;//���������߶�
	int m_nOriginX; //������������Ļ�ϵ�ԭʼ����x
	int m_nOriginY; //������������Ļ�ϵ�ԭʼ����y

	bool m_bFirstClick; //�Ƿ��һ�ε��
	//bool m_bSecondClick;
	bool m_bFirstSelect; //�Ƿ�ѡ����һ������������
	bool m_bSecondSelect;//�Ƿ�ѡ���ڶ�������������
	cocos2d::CCPoint m_ptFirstClick;//ѡ���ĵ�һ��������������Board�ϵ�����
	cocos2d::CCPoint m_ptSecondClick;//ѡ���ĵڶ���������������Board�ϵ�����
};

class GameEndLayer: public cocos2d::CCLayer
{
public:
	virtual void onEnter();
    virtual void onExit();

private:
};

#endif  // __PLAYINGGAMESCENE_H__