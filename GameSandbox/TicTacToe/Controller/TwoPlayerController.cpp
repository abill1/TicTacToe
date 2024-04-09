
#include "TwoPlayerController.h"
#include "../GameBoard/GameBoard.h"
#include "../Engine/Core/Collision/Collision.h"
#include "../Engine/Core/Input/Input.h"
#include "../GameBoard/Tile/Tile.h"
#include "../Engine/Core/Collision/Collider/AABB.h"
#include "../GameSandbox/TicTacToe/TicTacToe.h"
#include "../Scenes/ScenePlayerTwo.h"
#include "../GameBoard/GameBoard.h"
#include "../Scenes/SceneManager.h"
#include "../Engine/Core/GameObject/Sprite/Sprite.h"
#include "../Engine/Core/Window/Window.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"


//********************************************************************************//
//                                Utility                                         //
//********************************************************************************//

void ABFramework::TwoPlayerController::GLFWOnLeftClick(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		privClickLeftPlayerOne();
		privClickLeftPlayerTwo();
		if (ScenePlayerTwo::GetGameState() != ScenePlayerTwo::GameState::NONE)
		{
			if (Collision::Check(SceneManager::GetPlayerTwoScene()->GetMainMenuBtn()->GetCollider(), Input::GetMouseCollider()))
			{
				SceneManager::SwitchScene(SceneManager::SceneName::MAIN_MENU);
			}
			
		}
	}
}


//********************************************************************************//
//                             Private Helpers                                    //
//********************************************************************************//

void ABFramework::TwoPlayerController::privClickLeftPlayerOne()
{
	if (ScenePlayerTwo::GetGameState() == ScenePlayerTwo::GameState::NONE && ScenePlayerTwo::GetCurrentTurn() == ScenePlayerTwo::TurnPlayer::ONE)
	{
		GameBoard* pBoard = SceneManager::GetPlayerTwoScene()->GetGameBoard();
		for (int i = 0; i < pBoard->GetBoardSize(); i++)
		{
			if (pBoard->GetTile(i)->GetState() == Tile::State::EMPTY && Collision::Check(pBoard->GetTile(i)->GetCollider(), Input::GetMouseCollider()))
			{
				CursorCoord coord = Input::GetCursorPosition();
				pBoard->MarkTile((GameBoard::Position)i, Tile::State::X);
				ScenePlayerTwo::NextPlayer();
				break;
			}
		}
	}
}

void ABFramework::TwoPlayerController::privClickLeftPlayerTwo()
{
	if (ScenePlayerTwo::GetAIState() == ScenePlayerTwo::AI_State::INACTIVE)
	{
		if (ScenePlayerTwo::GetGameState() == ScenePlayerTwo::GameState::NONE && ScenePlayerTwo::GetCurrentTurn() == ScenePlayerTwo::TurnPlayer::TWO)
		{
			GameBoard* pBoard = SceneManager::GetPlayerTwoScene()->GetGameBoard();
			for (int i = 0; i < pBoard->GetBoardSize(); i++)
			{
				if (pBoard->GetTile(i)->GetState() == Tile::State::EMPTY && Collision::Check(pBoard->GetTile(i)->GetCollider(), Input::GetMouseCollider()))
				{
					CursorCoord coord = Input::GetCursorPosition();
					pBoard->MarkTile((GameBoard::Position)i, Tile::State::O);
					ScenePlayerTwo::NextPlayer();
					break;
				}
			}
		}
	}
}


