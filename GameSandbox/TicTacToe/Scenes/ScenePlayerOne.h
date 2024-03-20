
#ifndef GAMESANDBOX_TIC_TAC_TOE_SCENE_PLAYER_ONE_H
#define GAMESANDBOX_TIC_TAC_TOE_SCENE_PLAYER_ONE_H

#include "../Engine/Core/Scene/Scene.h"
#include "../Engine/Core/AssetManager/AssetDef/AssetDef.h"

namespace ABFramework
{
	class ScenePlayerOne : public Scene
	{
	public:
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

		// ----- Getters ----- //

	private:

	};
}

#endif // !GAMESANDBOX_TIC_TAC_TOE_SCENE_PLAYER_ONE_H



