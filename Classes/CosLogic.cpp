#include "CosLogic.h"
#include <ctime>
#include <queue>
#include <vector>
#include <algorithm>

#define __KDEBUG__

#ifdef __KDEBUG__
#include <iostream>
#endif

namespace cosmos{

CosGame::CosGame():
	CurrentState(NOTSTART)
{
	//ctor
	srand(unsigned(time(0)));
}

CosGame::~CosGame()
{
	//dctor

}

CosGame *CosGame::pGame = nullptr;

CosGame *CosGame::getInstance()
{
	if(!pGame){
		pGame = new CosGame();
	}
	return pGame;
}

void CosGame::createBoard(int x, int y, int ltc, int lmc)
{
	int i,j;
	HorNum = x;
	VerNum = y;
	BoardHor = x+2;
	BoardVer = y+2;
	link_type_count = ltc;
	link_max_couple = lmc;
	Board.resize(BoardVer);
	for(i = 0; i < BoardVer; ++i)
		Board[i].resize(BoardHor);
	randArr();

#ifdef __KDEBUG__
	for(int k = 0; k < BoardVer; ++k){
		for(int l = 0; l < BoardHor; ++l)
			std::cout << Board[k][l] << " ";
		std::cout << std::endl;
	}
#endif
}

void CosGame::reset()
{
	BoardHor = 0;
	BoardVer = 0;
	HorNum = 0;
	VerNum = 0;
	link_type_count = 0;
	link_max_couple = 0;
	Board.clear();
}

void CosGame::randArr()
{
	//最外圈填充上15
	for (int j=0;j<BoardVer;j++)
	{
		Board[j][0] = LINK_NULL;
		Board[j][HorNum+1] = LINK_NULL;
	}
	for (int j=0;j<BoardHor;j++)
	{
		Board[0][j] = LINK_NULL;
		Board[VerNum + 1][j] = LINK_NULL;
	}
	//15表示空
	//从1-
	//随机到一个由
	//进行随机分配从0-m_nPicNum

	int NeedRanNum;
	int* NumTim;

	NumTim = new int[link_type_count];
	for (int k=0;k<link_type_count;k++)
	{
		NumTim[k] = 0;
	}

	for (int j=1;j<VerNum+1;j++)
	{
		for (int k=1;k<HorNum+1;k++)
		{
			int RandNum = rand()%link_type_count;
			while(NumTim[RandNum] >= link_max_couple)
			{
				RandNum = rand()%link_type_count;
			}
			Board[j][k] = RandNum;
			NumTim[RandNum]++;
		}
	}
}

bool CosGame::isInLinkArea(int x, int y)
{
	if((x >= 1 && x <= HorNum)
		&& (y>=1 && y <= VerNum )
		&& Board[y][x] != LINK_NULL)
		return true;
	return false;
}

bool CosGame::not_searched(std::vector<SP> &searched, const SP &point_to_add)
{
	for(std::vector<SP>::size_type i = 0; i < searched.size(); ++i)
		if((searched[i].x == point_to_add.x) && (searched[i].y == point_to_add.y))
			return false;
	return true;
}

void CosGame::expand_search_point(std::vector<SP> &searched, std::queue<SP> &opcl, std::vector<SP> &link_set,const SP &point_to_search)
{
	searched.push_back(point_to_search);
	int dx,dy;
	
	//搜索UP
	dx = point_to_search.x, dy = point_to_search.y+1;
	while(dy < BoardVer && Board[dy][dx] == LINK_NULL){
		SP p;
		p.x = dx;p.y = dy;p.cross = point_to_search.cross + 1;
		if(not_searched(searched,p))
			opcl.push(p);
		dy++;
	}
	if(dy < BoardVer && Board[dy][dx] != LINK_NULL){
		SP p;
		p.x = dx;p.y = dy;p.cross = point_to_search.cross + 1;
		link_set.push_back(p);
	}
	//搜索DOWN
	dx = point_to_search.x, dy = point_to_search.y-1;
	while(dy >= 0 && Board[dy][dx] == LINK_NULL){
		SP p;
		p.x = dx;p.y = dy;p.cross = point_to_search.cross + 1;
		if(not_searched(searched,p))
			opcl.push(p);
		dy--;
	}
	if(dy >= 0 && Board[dy][dx] != LINK_NULL){
		SP p;
		p.x = dx;p.y = dy;p.cross = point_to_search.cross + 1;
		link_set.push_back(p);
	}
	//搜索LEFT
	dx = point_to_search.x-1, dy = point_to_search.y;
	while(dx >= 0 && Board[dy][dx] == LINK_NULL){
		SP p;
		p.x = dx;p.y = dy;p.cross = point_to_search.cross + 1;
		if(not_searched(searched,p))
			opcl.push(p);
		dx--;
	}
	if(dx >= 0 && Board[dy][dx] != LINK_NULL){
		SP p;
		p.x = dx;p.y = dy;p.cross = point_to_search.cross + 1;
		link_set.push_back(p);
	}
	//搜索RIGHT
	dx = point_to_search.x+1, dy = point_to_search.y;
	while(dx < BoardHor && Board[dy][dx] == LINK_NULL){
		SP p;
		p.x = dx;p.y = dy;p.cross = point_to_search.cross + 1;
		if(not_searched(searched,p))
			opcl.push(p);
		dx++;
	}
	if(dx < BoardHor && Board[dy][dx] != LINK_NULL){
		SP p;
		p.x = dx;p.y = dy;p.cross = point_to_search.cross + 1;
		link_set.push_back(p);
	}
}

bool CosGame::check_succeed(std::vector<SP> &link_set, const SP &target, const SP &origin)
{
	for(std::vector<SP>::size_type i = 0; i < link_set.size(); ++i)
		if(((link_set[i].y == target.y) && (link_set[i].x == target.x))
			&& (Board[origin.y][origin.x] == Board[target.y][target.x]))
			return true;
	return false;
}

bool CosGame::isLinkable(int x1, int y1, int x2, int y2)
{
	/**
	检查两个连连看方块是否可以相消，使用广度优先搜寻，使用标准库中的vector和queue，方便编写程序。
	 */
	if((x1 == x2) && (y1 == y2)) return false;
	std::vector<SP> searched(BoardHor*2);//已经搜索过的点
	std::vector<SP> link_set(BoardHor*2);//从（x1,y1）可以到达的连连看方块集合
	std::queue<SP> opcl;//广度优先搜寻使用的open-close表，它是一个队列

#ifdef __KDEBUG__
	std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << std::endl
		<< BoardVer << " " << BoardHor << std::endl;
#endif

	SP target;target.x = x2;target.y = y2;target.cross = -1;
	SP origin;origin.x = x1;origin.y = y1;origin.cross = -1;
	expand_search_point(searched, opcl, link_set, origin);
	if(check_succeed(link_set, target, origin))
			return true;
	link_set.clear();
	while(!opcl.empty()){
		SP p = opcl.front();
		opcl.pop();
		if(p.cross < 2){
			expand_search_point(searched, opcl, link_set, p);
			if(check_succeed(link_set, target, origin))
				return true;
			link_set.clear();
		}
	}
	return false;
}

bool CosGame::isAllClear()
{
	for(int i = 0; i < VerNum; ++i)
		for(int j = 0; j < HorNum; ++j)
			if(Board[i][j] != LINK_NULL)
				return false;
	return true;
}

}