
#ifndef GAMESANDBOX_TIC_TAC_TOE_SCENE_MANAGER_H
#define GAMESANDBOX_TIC_TAC_TOE_SCENE_MANAGER_H

namespace ABFramework
{
	class SceneManager
	{
	public:
		enum class SceneName : int 
		{
			MAIN_MENU,
			PLAYER_ONE,
			PLAYER_TWO
		};

		// ----- Constructor / Destructor ----- //

	private:
		SceneManager();

	public:
		~SceneManager();

		static void Init();
		static void Destroy();

		// ----- Operators ----- //

		// ------ Utility ----- //

		static void SwitchScene(SceneName _name);
		static void NextScene();
		static void Update();
		static void Draw();

		// ----- Setters ----- //

		// ----- Getters ----- //

		static class SceneMainMenu* GetMainMenuScene();
		static class ScenePlayerTwo* GetPlayerTwoScene();
		static class ScenePlayerOne* GetPlayerOneScene();

	private:
		static SceneManager* privGetInstance();

	private:
		static SceneManager* pInstance;

		class SceneMainMenu* pMainMenu;
		class ScenePlayerTwo* pTwoPlayer;
		class ScenePlayerOne* pOnePlayer;
		class Scene* pActiveScene;

	};
}

#endif // !GAMESANDBOX_TIC_TAC_TOE_SCENE_MANAGER_H


