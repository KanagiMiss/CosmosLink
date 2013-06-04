#include "CosLogic.h"
#include <ctime>

#define __KDEBUG__

#ifdef __KDEBUG__
#include <iostream>
#endif

namespace cosmos{

CosGame::CosGame():
	CurrentState(READY)
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


}