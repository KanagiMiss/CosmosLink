/*

	This header contains game's data and logic.

*/
#pragma once

#ifndef __COSLOGIC_H__
#define __COSLOGIC_H__

#include <vector>
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

	void createBoard(int x, int y, int ltc, int lmc);
	void startGame(){reset();CurrentState = RUN;}
	void pauseGame(){CurrentState = PAUSE;}
	void endGame(){CurrentState = READY;}
	void chooseLevel(Game_Level level){CurrentLevel = level;}

	Game_State getGameState(){return CurrentState;}
	Game_Level getGameLevel(){return CurrentLevel;}
	link_t getBoardPosValue(int i, int j){return Board[i][j];}

private:
	CosGame();
	void randArr();
	void reset();

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
