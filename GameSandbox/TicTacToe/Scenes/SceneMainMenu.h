
#ifndef GAMESANDBOX_TIC_TAC_TOE_SCENE_MAIN_MENU_H
#define GAMESANDBOX_TIC_TAC_TOE_SCENE_MAIN_MENU_H

#include "../Engine/Core/Scene/Scene.h"
#include "../Engine/Core/AssetManager/AssetDef/AssetDef.h"

namespace ABFramework
{
	class SceneMainMenu : public Scene 
	{
	public:
		// ----- Constructor / Destructor ----- //

		SceneMainMenu();
		virtual ~SceneMainMenu();

		// ----- Operators ----- //

		// ------ Utility ----- //

		void SetupScene() override;
		void CleanUpScene() override;
		void Update() override;
		void Draw() override;

		// ----- Setters ----- //

		// ----- Getters ----- //

		class Sprite* GetExitBtn() const;
		class Sprite* GetTwoPlayerBtn() const;
		class Sprite* GetOnePlayerBtn() const;

	private:
		const AssetDef TwoPlayerBtn = { "TwoPlayerBtn.tga","TwoPlayerBtn", true };
		const AssetDef OnePlayerBtn = { "OnePlayerBtn.tga","OnePlayerBtn", true };
		const AssetDef ExitBtn = { "ExitBtn.tga","ExitBtn", true };
		class Sprite* pExitBtn;
		class Sprite* pTwoPlayerBtn;
		class Sprite* pOnePlayerBtn;

	};
}

#endif // !GAMESANDBOX_TIC_TAC_TOE_SCENE_MAIN_MENU_H

