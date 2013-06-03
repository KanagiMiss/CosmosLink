/*
This header contains game data and logic.
*/
#pragma once

#ifndef __COSLOGIC_H__
#define __COSLOGIC_H__

#include <vector>
#define LAYER_COUNT 9

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

class CosGame
{
public:
	CosGame();
	virtual ~CosGame();

private:

};



#endif /* __COSLOGIC_H__ */
