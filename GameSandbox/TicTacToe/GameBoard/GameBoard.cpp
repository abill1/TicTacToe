
#include "GameBoard.h"
#include "../Engine/Core/GameObject/Sprite/Sprite.h"
#include "../Engine/Renderer/OpenGL/SimpleMeshes/SquareMesh/SquareMesh.h"
#include "../Engine/Core/AssetManager/AssetManager.h"
#include "../Engine/Core/Camera/Camera.h"
#include "../Engine/Core/Input/Input.h"
#include "../Engine/Core/Collision/Collision.h"

//********************************************************************************//
//                        Constructors / Destructor                               //
//********************************************************************************//

ABFramework::GameBoard::GameBoard()
	:pTiles(nullptr), pData(nullptr), m_CurrentEmptyTiles(BOARD_SIZE)
{
	pTiles = new Tile[BOARD_SIZE]();
	pData = new TileData[BOARD_SIZE];
	float xpos = -120.0f;
	float xInc = 120.0f;
	float ypos0 = 120.0f;
	float ypos1 = 0.0f;
	float ypos2 = -120.0f;
	float scale = 100.0f;

	for (int i = 0; i < BOARD_SIZE; i += 3)
	{
		pTiles[i].SetPosition(Point3D(xpos, ypos0, 0.0f));
		pTiles[i].SetScale(scale);
		pTiles[i + 1].SetPosition(Point3D(xpos, ypos1, 0.0f));
		pTiles[i + 1].SetScale(scale);
		pTiles[i + 2].SetPosition(Point3D(xpos, ypos2, 0.0f));
		pTiles[i + 2].SetScale(scale);
		pData[i].m_boardPosition = i;
		pData[i].m_State = Tile::State::EMPTY;
		pData[i].m_weight = 0.0f;
		pData[i+1].m_boardPosition = i+1;
		pData[i+1].m_State = Tile::State::EMPTY;
		pData[i+1].m_weight = 0.0f;
		pData[i+2].m_boardPosition = i+2;
		pData[i+2].m_State = Tile::State::EMPTY;
		pData[i+2].m_weight = 0.0f;
		xpos += xInc;
	}
	
}

ABFramework::GameBoard::~GameBoard()
{
	delete[] pTiles;
	pTiles = nullptr;
	delete[] pData;
	pData = nullptr;
}

//********************************************************************************//
//                               Operators                                        //
//********************************************************************************//




//********************************************************************************//
//                                Utility                                         //
//********************************************************************************//

void ABFramework::GameBoard::Update()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		pTiles[i].Update();
	}
}

void ABFramework::GameBoard::Draw(const Matrix& _viewProj)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		pTiles[i].Draw(Camera::GetViewProjectionMatrix());
	}
}


void ABFramework::GameBoard::ClearBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		pTiles[i].SetTileEmpty();
		pData[i].m_State = Tile::State::EMPTY;
		pData[i].m_weight = 0;
	}
	m_CurrentEmptyTiles = BOARD_SIZE;

}

void ABFramework::GameBoard::MarkTile(GameBoard::Position _index, Tile::State _piece)
{
	if (pTiles[(int)_index].SetState(_piece))
	{
		m_CurrentEmptyTiles--;
		pData[(int)_index].m_State = _piece;
		pData[(int)_index].m_weight = 0;
	}

}

ABFramework::Tile* ABFramework::GameBoard::GetTile(int _index)
{
	CHECK_NULL(pTiles);
	return &pTiles[_index];
}

ABFramework::Tile* ABFramework::GameBoard::GetTile(GameBoard::Position _index)
{
	CHECK_NULL(pTiles);
	return &pTiles[(int)_index];
}

ABFramework::TileData* ABFramework::GameBoard::GetTileData()
{
	return pData;
}

bool ABFramework::GameBoard::IsFull()
{
	return m_CurrentEmptyTiles == 0;
}

//********************************************************************************//
//                                Setters                                         //
//********************************************************************************//



//********************************************************************************//
//                                Getters                                         //
//********************************************************************************//

ABFramework::Tile* ABFramework::GameBoard::GetTile(int _row, int _col)
{
	Tile* pTile = nullptr;

	CHECK_LESS(_col, 3);
	CHECK_LESS(_row, 3);

	int index = (_row * 3) + _col;
	pTile = &pTiles[index];

	return pTile;
}

//********************************************************************************//
//                             Private Helpers                                    //
//********************************************************************************//



