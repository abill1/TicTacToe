#include "AIPlayer.h"
#include "../GameBoard/GameBoard.h"
#include "../GameBoard/Tile/Tile.h"


//********************************************************************************//
//                        Constructors / Destructor                               //
//********************************************************************************//

ABFramework::AIPlayer::AIPlayer()
{

}

ABFramework::AIPlayer::~AIPlayer()
{

}

//********************************************************************************//
//                               Operators                                        //
//********************************************************************************//




//********************************************************************************//
//                                Utility                                         //
//********************************************************************************//

void ABFramework::AIPlayer::TakeAction(GameBoard* _pBoard)
{

}

ABFramework::TileData ABFramework::AIPlayer::MiniMax(GameBoard* _pBoard, bool _bAITurn, int _depth)
{
	TileData mData = {};
	
	return mData;
}

int ABFramework::AIPlayer::Max(int _currentMax, int _compare)
{
	int max = _currentMax;
	if (max < _compare)
		max = _compare;
	return max;
}

int ABFramework::AIPlayer::Min(int _currentMin, int _compare)
{
	int min = _currentMin;
	if (min > _compare)
		min = _compare;
	return min;
}


//********************************************************************************//
//                                Setters                                         //
//********************************************************************************//



//********************************************************************************//
//                                Getters                                         //
//********************************************************************************//



//********************************************************************************//
//                             Private Helpers                                    //
//********************************************************************************//







