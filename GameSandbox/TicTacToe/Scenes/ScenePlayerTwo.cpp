#include "ScenePlayerTwo.h"
#include "../Engine/Core/GameObject/GameObjectManager.h"
#include "../Engine/Core/AssetManager/AssetManager.h"
#include "../Engine/Renderer/OpenGL/Texture/Texture.h"
#include "../Engine/Renderer/OpenGL/SimpleMeshes/SquareMesh/SquareMesh.h"
#include "../Engine/Core/Camera/Camera.h"
#include "../Engine/Core/Window/Window.h"
#include "../Engine/Core/AssetManager/AssetDef/AssetDef.h"
#include "../Engine/Core/GameObject/Sprite/Sprite.h"
#include "../Engine/Core/Collision/Collider/AABB.h"
#include "../GameBoard/GameBoard.h"
#include "../Engine/Core/Input/Input.h"
#include "../GameBoard/Tile/Tile.h"
#include "../Controller/TwoPlayerController.h"
#include "../CurrentPlayerIcon/CurrentPlayerIcon.h"
#include "../Scenes/SceneManager.h"
#include "../Engine/Core/Window/Window.h"

ABFramework::ScenePlayerTwo::TurnPlayer ABFramework::ScenePlayerTwo::s_PlayerTurn = ABFramework::ScenePlayerTwo::TurnPlayer::ONE;
ABFramework::ScenePlayerTwo::GameState ABFramework::ScenePlayerTwo::s_GameState = ABFramework::ScenePlayerTwo::GameState::NONE;


//********************************************************************************//
//                        Constructors / Destructor                               //
//********************************************************************************//

ABFramework::ScenePlayerTwo::ScenePlayerTwo()
	:Scene(), pBoard(nullptr), pCurrentPlayerIcon(nullptr), pMainMenuBtn(nullptr), 
	pGameResult(nullptr), h_Draw(0), h_PlayerOneWin(0), h_PlayerTwoWin(0)
{
	AssetManager::AddTexture(defaultTexture);
	AssetManager::AddTexture(EmptySquare);
	AssetManager::AddTexture(XSquare);
	AssetManager::AddTexture(OSquare);
	pBoard = new GameBoard();
	pCurrentPlayerIcon = new CurrentPlayerIcon();
	pCurrentPlayerIcon->SetPosition(CurrentPlayerIcon::Player::ONE, Point3D(-400.0f, 400.0f, 0.0f));
	pCurrentPlayerIcon->SetScale(CurrentPlayerIcon::Player::ONE, Scale(200.0f, 200.0f, 0.0f));
	pCurrentPlayerIcon->SetPosition(CurrentPlayerIcon::Player::TWO, Point3D(400.0f, 400.0f, 0.0f));
	pCurrentPlayerIcon->SetScale(CurrentPlayerIcon::Player::TWO, Scale(200.0f, 200.0f, 0.0f));
	
	Square_Mesh* pMesh = AssetManager::GetSquareMesh();
	t_handle h_MainMenuBtn = AssetManager::AddTexture(MainMenuBtn);
	pMainMenuBtn = new Sprite();
	pMainMenuBtn->SetMesh(pMesh);
	pMainMenuBtn->SetTexture(h_MainMenuBtn);
	pMainMenuBtn->SetPosition(Point3D(0.0f, -300.0f, 0.0f));
	pMainMenuBtn->SetScale(Scale(340.0f, 100.0f, 0.0f));

	h_PlayerOneWin = AssetManager::AddTexture(PlayerOneWins);
	h_PlayerTwoWin = AssetManager::AddTexture(PlayerTwoWins);
	h_Draw = AssetManager::AddTexture(PlayersDraw);
	pGameResult = new Sprite();
	pGameResult->SetMesh(pMesh);
	pGameResult->SetTexture(h_Draw);
	pGameResult->SetPosition(Point3D(0.0f, 300.0f, 0.0f));
	pGameResult->SetScale(Scale(340.0f, 100.0f, 0.0f));

}


ABFramework::ScenePlayerTwo::~ScenePlayerTwo()
{
	delete pGameResult;
	pGameResult = nullptr;
	delete pMainMenuBtn;
	pMainMenuBtn = nullptr;
	delete pCurrentPlayerIcon;
	pCurrentPlayerIcon = nullptr;
	delete pBoard;
	pBoard = nullptr;

}

//********************************************************************************//
//                               Operators                                        //
//********************************************************************************//




//********************************************************************************//
//                                Utility                                         //
//********************************************************************************//

void ABFramework::ScenePlayerTwo::SetupScene()
{
	pBoard->ClearBoard();
	ScenePlayerTwo::s_GameState = GameState::NONE;
	ScenePlayerTwo::s_PlayerTurn = TurnPlayer::ONE;
	Input::BindAction(&TwoPlayerController::GLFWOnLeftClick);
}

void ABFramework::ScenePlayerTwo::CleanUpScene()
{
	Input::UnbindAction(MouseCode::BUTTON_LEFT);
}

void ABFramework::ScenePlayerTwo::Update()
{
	if (UpdateGameState() != GameState::NONE)
	{
		switch (ScenePlayerTwo::s_GameState)
		{
		case GameState::WIN_PLAYER_ONE:
			ScenePlayerTwo::s_GameState = GameState::WIN_PLAYER_ONE;
			pGameResult->SetTexture(h_PlayerOneWin);
			break;
		case GameState::WIN_PLAYER_TWO:
			ScenePlayerTwo::s_GameState = GameState::WIN_PLAYER_TWO;
			pGameResult->SetTexture(h_PlayerTwoWin);
			break;
		case GameState::DRAW:
			ScenePlayerTwo::s_GameState = GameState::DRAW;
			pGameResult->SetTexture(h_Draw);
			break;
		case GameState::NONE:
		default:
			printf("Error! Incorrect Game State\n");
			break;
		}
		pMainMenuBtn->Update();
		pGameResult->Update();
	}
	pBoard->Update();
	pCurrentPlayerIcon->Update();
	
}

void ABFramework::ScenePlayerTwo::Draw()
{
	if (UpdateGameState() != GameState::NONE)
	{
		pMainMenuBtn->Draw(Camera::GetViewProjectionMatrix());
		pGameResult->Draw(Camera::GetViewProjectionMatrix());
	}
	pBoard->Draw(Camera::GetViewProjectionMatrix());
	pCurrentPlayerIcon->Draw(Camera::GetViewProjectionMatrix());

}

ABFramework::ScenePlayerTwo::GameState ABFramework::ScenePlayerTwo::UpdateGameState()
{
	privTestRowWin();
	privTestColWin();
	privTestDiagonalWin();
	privTestDraw();

	return ScenePlayerTwo::s_GameState;
}

//********************************************************************************//
//                                Setters                                         //
//********************************************************************************//

void ABFramework::ScenePlayerTwo::NextPlayer()
{
	bool state = (bool)ScenePlayerTwo::s_PlayerTurn;
	state = !state;
	ScenePlayerTwo::s_PlayerTurn = (TurnPlayer)state;

}

//********************************************************************************//
//                                Getters                                         //
//********************************************************************************//

ABFramework::ScenePlayerTwo::TurnPlayer ABFramework::ScenePlayerTwo::GetCurrentTurn()
{
	return ScenePlayerTwo::s_PlayerTurn;
}

ABFramework::ScenePlayerTwo::GameState ABFramework::ScenePlayerTwo::GetGameState()
{
	return ScenePlayerTwo::s_GameState;
}

ABFramework::GameBoard* ABFramework::ScenePlayerTwo::GetGameBoard()
{
	return pBoard;
}

ABFramework::Sprite* ABFramework::ScenePlayerTwo::GetMainMenuBtn()
{
	return pMainMenuBtn;
}

//********************************************************************************//
//                             Private Helpers                                    //
//********************************************************************************//

bool ABFramework::ScenePlayerTwo::privTestRowWin()
{
	bool bOver = false;
	CHECK_NULL(pBoard);

	for (int i = 0; i < pBoard->GetBoardSize(); i += 3)
	{
		Tile::State tileState = pBoard->GetTile((int)GameBoard::Position::TOP_LEFT + i)->GetState();
		if (tileState != Tile::State::EMPTY && tileState == pBoard->GetTile((int)GameBoard::Position::TOP_CENTER + i)->GetState() && tileState == pBoard->GetTile(((int)GameBoard::Position::TOP_RIGHT + i))->GetState())
		{
			privSetState((int)tileState);
			bOver = true;
			break;

		}
	}

	return bOver;
}

bool ABFramework::ScenePlayerTwo::privTestColWin()
{
	bool bOver = false;
	CHECK_NULL(pBoard);

	for (int i = 0; i < 3; i++)
	{
		Tile::State tileState = pBoard->GetTile((int)GameBoard::Position::TOP_LEFT + i)->GetState();
		if (tileState != Tile::State::EMPTY && tileState == pBoard->GetTile((int)GameBoard::Position::MID_LEFT + i)->GetState() && tileState == pBoard->GetTile((int)GameBoard::Position::BOTTOM_LEFT + i)->GetState())
		{
			privSetState((int)tileState);
			bOver = true;
			break;

		}
	}

	return bOver;
}

bool ABFramework::ScenePlayerTwo::privTestDiagonalWin()
{
	bool bOver = false;
	CHECK_NULL(pBoard);

	Tile::State centerState = pBoard->GetTile(GameBoard::Position::MID_CENTER)->GetState();
	Tile::State topLeftCorner = pBoard->GetTile(GameBoard::Position::TOP_LEFT)->GetState();
	Tile::State topRightCorner = pBoard->GetTile(GameBoard::Position::TOP_RIGHT)->GetState();
	Tile::State bottomLeftCorner = pBoard->GetTile(GameBoard::Position::BOTTOM_LEFT)->GetState();
	Tile::State bottomRightCorner = pBoard->GetTile(GameBoard::Position::BOTTOM_RIGHT)->GetState();

	if (centerState != Tile::State::EMPTY && centerState == topLeftCorner && centerState == bottomRightCorner)
	{
		privSetState((int)centerState);
	}
	else if (centerState != Tile::State::EMPTY && centerState == topRightCorner && centerState == bottomLeftCorner)
	{
		privSetState((int)centerState);
	}

	return bOver;
}

bool ABFramework::ScenePlayerTwo::privTestDraw()
{
	bool bOver = false;
	CHECK_NULL(pBoard);

	if (ScenePlayerTwo::s_GameState == GameState::NONE)
	{
		bOver = true;
		for (int i = 0; i < pBoard->GetBoardSize(); i++)
		{
			if (pBoard->GetTile(i)->GetState() == Tile::State::EMPTY)
			{
				bOver = false;
				break;
			}

		}

		if (bOver)
		{
			ScenePlayerTwo::s_GameState = GameState::DRAW;
		}

	}

	return bOver;
}

void ABFramework::ScenePlayerTwo::privSetState(int _state)
{
	Tile::State state = (Tile::State)_state;
	switch (state)
	{
	case Tile::State::X:
		ScenePlayerTwo::s_GameState = ScenePlayerTwo::GameState::WIN_PLAYER_ONE;
		break;
	case Tile::State::O:
		ScenePlayerTwo::s_GameState = ScenePlayerTwo::GameState::WIN_PLAYER_TWO;
		break;
	case Tile::State::EMPTY:
	default:
		break;
	}

}


