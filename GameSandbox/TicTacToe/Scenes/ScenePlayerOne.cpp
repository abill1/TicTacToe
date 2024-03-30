#include "ScenePlayerOne.h"

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
#include "../Controller/OnePlayerController.h"
#include "../CurrentPlayerIcon/CurrentPlayerIcon.h"
#include "../Scenes/SceneManager.h"
#include "../Engine/Core/Window/Window.h"
#include "../AI/AIPlayer.h"

ABFramework::ScenePlayerOne::TurnPlayer ABFramework::ScenePlayerOne::s_PlayerTurn = ABFramework::ScenePlayerOne::TurnPlayer::ONE;
ABFramework::ScenePlayerOne::GameState ABFramework::ScenePlayerOne::s_GameState = ABFramework::ScenePlayerOne::GameState::NONE;
ABFramework::ScenePlayerOne::AI_State ABFramework::ScenePlayerOne::s_AIState = ABFramework::ScenePlayerOne::AI_State::INACTIVE;

//********************************************************************************//
//                        Constructors / Destructor                               //
//********************************************************************************//

ABFramework::ScenePlayerOne::ScenePlayerOne()
	:Scene(), pBoard(nullptr), pCurrentPlayerIcon(nullptr), pMainMenuBtn(nullptr),
	pGameResult(nullptr), h_Draw(0), h_PlayerOneWin(0), h_PlayerTwoWin(0), pAIplayer(new AIPlayer())
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


ABFramework::ScenePlayerOne::~ScenePlayerOne()
{
	delete pAIplayer;
	pAIplayer = nullptr;
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

void ABFramework::ScenePlayerOne::SetupScene()
{
	pBoard->ClearBoard();
	ScenePlayerOne::s_GameState = GameState::NONE;
	ScenePlayerOne::s_PlayerTurn = TurnPlayer::ONE;
	ScenePlayerOne::s_AIState = AI_State::ACTIVE;
	Input::BindAction(&OnePlayerController::GLFWOnLeftClick);
}

void ABFramework::ScenePlayerOne::CleanUpScene()
{
	ScenePlayerOne::s_AIState = AI_State::INACTIVE;
	Input::UnbindAction(MouseCode::BUTTON_LEFT);
}

void ABFramework::ScenePlayerOne::Update()
{
	if (UpdateGameState() != GameState::NONE)
	{
		switch (ScenePlayerOne::s_GameState)
		{
		case GameState::WIN_PLAYER_ONE:
			ScenePlayerOne::s_GameState = GameState::WIN_PLAYER_ONE;
			pGameResult->SetTexture(h_PlayerOneWin);
			break;
		case GameState::WIN_PLAYER_TWO:
			ScenePlayerOne::s_GameState = GameState::WIN_PLAYER_TWO;
			pGameResult->SetTexture(h_PlayerTwoWin);
			break;
		case GameState::DRAW:
			ScenePlayerOne::s_GameState = GameState::DRAW;
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

	if (ScenePlayerOne::s_PlayerTurn == TurnPlayer::TWO && ScenePlayerOne::s_AIState == AI_State::ACTIVE)
	{
		pAIplayer->TakeAction(pBoard);
	}
	pBoard->Update();
	pCurrentPlayerIcon->Update();

}

void ABFramework::ScenePlayerOne::Draw()
{
	if (UpdateGameState() != GameState::NONE)
	{
		pMainMenuBtn->Draw(Camera::GetViewProjectionMatrix());
		pGameResult->Draw(Camera::GetViewProjectionMatrix());
	}
	pBoard->Draw(Camera::GetViewProjectionMatrix());
	pCurrentPlayerIcon->Draw(Camera::GetViewProjectionMatrix());

}

ABFramework::ScenePlayerOne::GameState ABFramework::ScenePlayerOne::UpdateGameState()
{
	privTestRowWin();
	privTestColWin();
	privTestDiagonalWin();
	privTestDraw();

	return ScenePlayerOne::s_GameState;
}

//********************************************************************************//
//                                Setters                                         //
//********************************************************************************//

void ABFramework::ScenePlayerOne::NextPlayer()
{
	bool state = (bool)ScenePlayerOne::s_PlayerTurn;
	state = !state;
	ScenePlayerOne::s_PlayerTurn = (TurnPlayer)state;

}

void ABFramework::ScenePlayerOne::ActivateAI()
{
	ScenePlayerOne::s_AIState = AI_State::ACTIVE;
}

void ABFramework::ScenePlayerOne::DisableAI()
{
	ScenePlayerOne::s_AIState = AI_State::INACTIVE;
}

//********************************************************************************//
//                                Getters                                         //
//********************************************************************************//

ABFramework::ScenePlayerOne::TurnPlayer ABFramework::ScenePlayerOne::GetCurrentTurn()
{
	return ScenePlayerOne::s_PlayerTurn;
}

ABFramework::ScenePlayerOne::GameState ABFramework::ScenePlayerOne::GetGameState()
{
	return ScenePlayerOne::s_GameState;
}


ABFramework::ScenePlayerOne::AI_State ABFramework::ScenePlayerOne::GetAIState()
{
	return ScenePlayerOne::s_AIState;
}

ABFramework::GameBoard* ABFramework::ScenePlayerOne::GetGameBoard()
{
	return pBoard;
}

ABFramework::Sprite* ABFramework::ScenePlayerOne::GetMainMenuBtn()
{
	return pMainMenuBtn;
}

//********************************************************************************//
//                             Private Helpers                                    //
//********************************************************************************//

bool ABFramework::ScenePlayerOne::privTestRowWin()
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

bool ABFramework::ScenePlayerOne::privTestColWin()
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

bool ABFramework::ScenePlayerOne::privTestDiagonalWin()
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

bool ABFramework::ScenePlayerOne::privTestDraw()
{
	bool bOver = false;
	CHECK_NULL(pBoard);

	if (ScenePlayerOne::s_GameState == GameState::NONE)
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
			ScenePlayerOne::s_GameState = GameState::DRAW;
		}

	}

	return bOver;
}

void ABFramework::ScenePlayerOne::privSetState(int _state)
{
	Tile::State state = (Tile::State)_state;
	switch (state)
	{
	case Tile::State::X:
		ScenePlayerOne::s_GameState = ScenePlayerOne::GameState::WIN_PLAYER_ONE;
		break;
	case Tile::State::O:
		ScenePlayerOne::s_GameState = ScenePlayerOne::GameState::WIN_PLAYER_TWO;
		break;
	case Tile::State::EMPTY:
	default:
		break;
	}

}
