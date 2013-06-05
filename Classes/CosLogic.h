/*

	This header contains game's data and logic.

*/
#pragma once

#ifndef __COSLOGIC_H__
#define __COSLOGIC_H__

#include "cocos2d.h"
#include <vector>
#include <queue>
#define LAYER_COUNT 9

namespace cosmos{

enum Game_Level{
	MERCURY = 0,	//水星
	VENUS,			//金星
	EARTH,			//地球
	MARS,			//火星 
	JUPITER,		//木星
	SATURN,			//土星
	URANUS,			//天王星
	NEPTUNE,		//海王星
	PLUTO,			//冥王星
	SUN
};

enum Game_State{
	READY = 0,
	RUN,
	PAUSE
};

static const int LINK_NULL = 15;
//static const int LINK_TYPE_COUNT = 10;

class CosGame
{
public:
	typedef unsigned int link_t;
	typedef std::vector<std::vector<link_t> > board_t;

	virtual ~CosGame();

	static CosGame *getInstance();
	static void releaseInstance(){
		if(pGame)
			delete pGame;
		pGame = nullptr;
	}

	void createBoard(int x, int y, int ltc, int lmc);//创建一个长度为x,宽度为y的连连看面板,ltc为连连看元素的种类,lmc为每个元素最多有几个
	void startGame(){reset();CurrentState = RUN;}//开始游戏
	void pauseGame(){CurrentState = PAUSE;}//暂停游戏
	void endGame(){CurrentState = READY;}//结束游戏
	void chooseLevel(Game_Level level){CurrentLevel = level;}//选择关卡
	
	bool isInLinkArea(int x, int y);//检测这个点是否在连连看图片区域内
	bool isLinkable(int x1, int y1, int x2, int y2);//检测两个连连看元素是否能够相消

	Game_State getGameState(){return CurrentState;}
	Game_Level getGameLevel(){return CurrentLevel;}
	link_t getBoardPosValue(int i, int j){return Board[i][j];}//获得面板对应点的坐标
	void setLinkNull(int x, int y){Board[y][x] = LINK_NULL;}

private:
	typedef enum Search_State{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT
	}SS;

	typedef struct Search_Point{
		int x,y;
		int cross;
	}SP;

	CosGame();
	void randArr();
	void reset();
	void expand_search_point(std::vector<SP> &searched, std::queue<SP> &opcl, std::vector<SP> &link_set,const SP &point_to_search);
	bool check_succeed(std::vector<SP> &link_set, const SP &target, const SP &origin);
	bool not_searched(std::vector<SP> &searched, const SP &point_to_add);

	static CosGame *pGame;

	Game_Level CurrentLevel;
	Game_State CurrentState;
	int BoardHor;//板的实际长度
	int BoardVer;//板的实际高度
	int HorNum;	//板的逻辑长度
	int VerNum;	//板的逻辑高度
	int link_type_count;	//连连看元素的种类
	int link_max_couple;	//每个元素最多有几个
	board_t Board;

};

}

#endif /* __COSLOGIC_H__ */
