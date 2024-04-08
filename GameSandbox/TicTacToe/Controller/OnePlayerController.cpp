
#include "OnePlayerController.h"
#include "../GameBoard/GameBoard.h"
#include "../Engine/Core/Collision/Collision.h"
#include "../Engine/Core/Input/Input.h"
#include "../GameBoard/Tile/Tile.h"
#include "../Engine/Core/Collision/Collider/AABB.h"
#include "../GameSandbox/TicTacToe/TicTacToe.h"
#include "../Scenes/ScenePlayerOne.h"
#include "../GameBoard/GameBoard.h"
#include "../Scenes/SceneManager.h"
#include "../Engine/Core/GameObject/Sprite/Sprite.h"
#include "../Engine/Core/Window/Window.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"


//********************************************************************************//
//                                Utility                                         //
//********************************************************************************//

void ABFramework::OnePlayerController::GLFWOnLeftClick(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		privClickLeftPlayerOne();
		privClickLeftPlayerTwo();
		if (ScenePlayerOne::GetGameState() != ScenePlayerOne::GameState::NONE)
		{
			if (Collision::Check(SceneManager::GetPlayerOneScene()->GetMainMenuBtn()->GetCollider(), Input::GetMouseCollider()))
			{
				SceneManager::SwitchScene(SceneManager::SceneName::MAIN_MENU);
			}

		}
	}
}


//********************************************************************************//
//                             Private Helpers                                    //
//********************************************************************************//

void ABFramework::OnePlayerController::privClickLeftPlayerOne()
{
	if (ScenePlayerOne::GetGameState() == ScenePlayerOne::GameState::NONE && ScenePlayerOne::GetCurrentTurn() == ScenePlayerOne::TurnPlayer::ONE)
	{
		GameBoard* pBoard = SceneManager::GetPlayerOneScene()->GetGameBoard();
		for (int i = 0; i < pBoard->GetBoardSize(); i++)
		{
			if (pBoard->GetTile(i)->GetState() == Tile::State::EMPTY && Collision::Check(pBoard->GetTile(i)->GetCollider(), Input::GetMouseCollider()))
			{
				CursorCoord coord = Input::GetCursorPosition();
				printf("[Mouse Coord] X: %f, Y: %f\n", coord.x, coord.y);
				pBoard->MarkTile((GameBoard::Position)i, Tile::State::X);
				ScenePlayerOne::NextPlayer();
				break;
			}
		}
	}
}

void ABFramework::OnePlayerController::privClickLeftPlayerTwo()
{
	if (ScenePlayerOne::GetAIState() == ScenePlayerOne::AI_State::INACTIVE)
	{
		if (ScenePlayerOne::GetCurrentTurn() == ScenePlayerOne::TurnPlayer::TWO)
		{
			GameBoard* pBoard = SceneManager::GetPlayerOneScene()->GetGameBoard();
			for (int i = 0; i < pBoard->GetBoardSize(); i++)
			{
				if (pBoard->GetTile(i)->GetState() == Tile::State::EMPTY && Collision::Check(pBoard->GetTile(i)->GetCollider(), Input::GetMouseCollider()))
				{
					CursorCoord coord = Input::GetCursorPosition();
					printf("[Mouse Coord] X: %f, Y: %f\n", coord.x, coord.y);
					pBoard->MarkTile((GameBoard::Position)i, Tile::State::O);
					ScenePlayerOne::NextPlayer();
					break;
				}
			}
		}
	}
}


