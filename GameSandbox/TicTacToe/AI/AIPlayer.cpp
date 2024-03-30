#include "AIPlayer.h"
#include "../GameBoard/GameBoard.h"
#include "../GameBoard/Tile/Tile.h"
#include "../Scenes/ScenePlayerOne.h"


//********************************************************************************//
//                        Constructors / Destructor                               //
//********************************************************************************//

ABFramework::AIPlayer::AIPlayer()
	:pData(nullptr)
{
	pData = new TileData[9];
}

ABFramework::AIPlayer::~AIPlayer()
{
	delete[] pData;
	pData = nullptr;
}

//********************************************************************************//
//                               Operators                                        //
//********************************************************************************//




//********************************************************************************//
//                                Utility                                         //
//********************************************************************************//

void ABFramework::AIPlayer::TakeAction(GameBoard* _pBoard)
{
	TileData* pActiveBoard = _pBoard->GetTileData();
	int boardSize = 9 * sizeof(TileData);
	memset(pData, 0, boardSize);
	memcpy_s(pData, boardSize, _pBoard->GetTileData(), boardSize);
	TileData data = MiniMax(pData, true, 1);
	_pBoard->MarkTile((GameBoard::Position)data.m_boardPosition, Tile::State::O);
	ScenePlayerOne::NextPlayer();
}

ABFramework::TileData ABFramework::AIPlayer::MiniMax(TileData* _pData, bool _bAITurn, int _depth)
{
	TileData mData = {};
	bool bWin = privCheckForWin();
	bool bDraw = privTestDraw();

	// ----- Check the base case 
	if (bWin)
	{
		if (_bAITurn)
		{
			mData.m_weight = HUMAN_WIN;
		}
		else
		{
			mData.m_weight = AI_WIN;
		}
		return mData;
	}
	else if(bDraw)
	{
		mData.m_weight = DRAW;
		return mData;
	}

	_depth++;

	// Max pl
	if (_bAITurn)
	{
		TileData mTemp;
		mData.m_weight = INT_MIN;

		for (int i = 0; i < 9; i++)
		{
			mTemp.m_boardPosition = i;
			if (pData[mTemp.m_boardPosition].m_State == (int)Tile::State::EMPTY)
			{
				pData[mTemp.m_boardPosition].m_State = (int)Tile::State::O;

				mTemp.m_weight = MiniMax(pData, false, _depth).m_weight;
				mTemp.m_weight += _depth;
				pData[mTemp.m_boardPosition].m_State = (int)Tile::State::EMPTY;
				if (mTemp.m_weight > mData.m_weight)
				{
					mData.m_boardPosition = mTemp.m_boardPosition;
					mData.m_weight = mTemp.m_weight;
				}

			}
		}
	}

	// Min pl
	if(_bAITurn == false)
	{
		TileData mTemp;
		mData.m_weight = INT_MAX;

		for (int i = 0; i < 9; i++)
		{
			mTemp.m_boardPosition = i;
			if (pData[mTemp.m_boardPosition].m_State == (int)Tile::State::EMPTY)
			{
				pData[mTemp.m_boardPosition].m_State = (int)Tile::State::X;
				mTemp.m_weight = MiniMax(pData, true, _depth).m_weight;
				pData[mTemp.m_boardPosition].m_State = (int)Tile::State::EMPTY;
				if (mTemp.m_weight < mData.m_weight)
				{
					mData.m_boardPosition = mTemp.m_boardPosition;
					mData.m_weight = mTemp.m_weight;
				}
				
			}
		}

	}
	
	
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

bool ABFramework::AIPlayer::privCheckForWin()
{
	return privTestRowWin() || privTestColWin() || privTestDiagonalWin();
}

bool ABFramework::AIPlayer::privTestRowWin()
{
	bool bOver = false;
	CHECK_NULL(pData);

	for (int i = 0; i < 9; i += 3)
	{
		Tile::State tileState = (Tile::State)pData[(int)GameBoard::Position::TOP_LEFT + i].m_State;
		if (tileState != Tile::State::EMPTY && tileState == (Tile::State)pData[(int)GameBoard::Position::TOP_CENTER + i].m_State && tileState == (Tile::State)pData[((int)GameBoard::Position::TOP_RIGHT + i)].m_State)
		{
			bOver = true;
			break;

		}
	}

	return bOver;
}

bool ABFramework::AIPlayer::privTestColWin()
{
	bool bOver = false;
	CHECK_NULL(pData);

	for (int i = 0; i < 3; i++)
	{
		Tile::State tileState = (Tile::State)pData[(int)GameBoard::Position::TOP_LEFT + i].m_State;
		if (tileState != Tile::State::EMPTY && tileState == (Tile::State)pData[(int)GameBoard::Position::MID_LEFT + i].m_State && tileState == (Tile::State)pData[(int)GameBoard::Position::BOTTOM_LEFT + i].m_State)
		{
			bOver = true;
			break;

		}
	}

	return bOver;
}

bool ABFramework::AIPlayer::privTestDiagonalWin()
{
	bool bOver = false;
	CHECK_NULL(pData);

	Tile::State centerState = (Tile::State)pData[(int)GameBoard::Position::MID_CENTER].m_State;
	Tile::State topLeftCorner = (Tile::State)pData[(int)GameBoard::Position::TOP_LEFT].m_State;
	Tile::State topRightCorner = (Tile::State)pData[(int)GameBoard::Position::TOP_RIGHT].m_State;
	Tile::State bottomLeftCorner = (Tile::State)pData[(int)GameBoard::Position::BOTTOM_LEFT].m_State;
	Tile::State bottomRightCorner = (Tile::State)pData[(int)GameBoard::Position::BOTTOM_RIGHT].m_State;

	if (centerState != Tile::State::EMPTY && centerState == topLeftCorner && centerState == bottomRightCorner)
	{
		bOver = true;
	}
	else if (centerState != Tile::State::EMPTY && centerState == topRightCorner && centerState == bottomLeftCorner)
	{
		bOver = true;
	}

	return bOver;
}

bool ABFramework::AIPlayer::privTestDraw()
{
	CHECK_NULL(pData);
	bool bOver = true;

	for (int i = 0; i < 9; i++)
	{
		if (pData[i].m_State == (int)Tile::State::EMPTY)
		{
			bOver = false;
			break;
		}

	}

	return bOver;
}





