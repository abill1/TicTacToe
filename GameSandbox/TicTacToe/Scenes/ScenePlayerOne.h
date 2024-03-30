
#ifndef GAMESANDBOX_TIC_TAC_TOE_SCENE_PLAYER_ONE_H
#define GAMESANDBOX_TIC_TAC_TOE_SCENE_PLAYER_ONE_H

#include "../Engine/Core/Scene/Scene.h"
#include "../Engine/Core/AssetManager/AssetDef/AssetDef.h"

namespace ABFramework
{
	class ScenePlayerOne : public Scene
	{
	public:
		enum class AI_State
		{
			INACTIVE,
			ACTIVE
		};

		enum class TurnPlayer : bool
		{
			ONE = true,
			TWO = false
		};

		enum class GameState : int
		{
			NONE = -2,
			WIN_PLAYER_ONE = -1,
			DRAW = 0,
			WIN_PLAYER_TWO = 1
		};

	public:

		// ----- Constructor / Destructor ----- //

		ScenePlayerOne();
		virtual ~ScenePlayerOne();

		// ----- Operators ----- //

		// ------ Utility ----- //

		void SetupScene() override;
		void CleanUpScene() override;
		void Update() override;
		void Draw() override;
		GameState UpdateGameState();

		// ----- Setters ----- //

		static void NextPlayer();
		static void ActivateAI();
		static void DisableAI();

		// ----- Getters ----- //

		static TurnPlayer GetCurrentTurn();
		static GameState GetGameState();
		static AI_State GetAIState();
		class GameBoard* GetGameBoard();
		class Sprite* GetMainMenuBtn();

	private:
		bool privTestRowWin();
		bool privTestColWin();
		bool privTestDiagonalWin();
		bool privTestDraw();
		void privSetState(int _state);

	private:
		static TurnPlayer s_PlayerTurn;
		static GameState s_GameState;
		static AI_State s_AIState;
		const AssetDef defaultTexture = { "..\\Engine\\Assets\\DefaultTexture.tga","DefaultAsset" };
		const AssetDef EmptySquare = { "..\\GameSandbox\\Assets\\Textures\\Empty.tga","Empty" };
		const AssetDef XSquare = { "..\\GameSandbox\\Assets\\Textures\\xsquare.tga","XSquare" };
		const AssetDef OSquare = { "..\\GameSandbox\\Assets\\Textures\\osquare.tga","OSquare" };
		const AssetDef MainMenuBtn = { "..\\GameSandbox\\Assets\\Textures\\MainMenuBtn.tga","MainMenuBtn", true };
		const AssetDef PlayerOneWins = { "..\\GameSandbox\\Assets\\Textures\\Player1Wins.tga","PlayerOneWins", true };
		const AssetDef PlayerTwoWins = { "..\\GameSandbox\\Assets\\Textures\\Player2Wins.tga","PlayerTwoWins", true };
		const AssetDef PlayersDraw = { "..\\GameSandbox\\Assets\\Textures\\Draw.tga","PlayersDraw", true };
		class GameBoard* pBoard;
		class CurrentPlayerIcon* pCurrentPlayerIcon;
		class Sprite* pMainMenuBtn;
		class Sprite* pGameResult;
		class AIPlayer* pAIplayer;
		t_handle h_Draw;
		t_handle h_PlayerOneWin;
		t_handle h_PlayerTwoWin;

	};
}

#endif // !GAMESANDBOX_TIC_TAC_TOE_SCENE_PLAYER_ONE_H



