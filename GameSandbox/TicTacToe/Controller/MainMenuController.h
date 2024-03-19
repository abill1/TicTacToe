
#ifndef GAMESANDBOX_TIC_TAC_TOE_MAIN_MENU_CONTROLLER_H
#define GAMESANDBOX_TIC_TAC_TOE_MAIN_MENU_CONTROLLER_H

#include "../Engine/Core/Controller/PlayerController.h"

struct GLFWwindow;

namespace ABFramework
{
	class MainMenuController
	{
	public:
		static void OnClickLeft(GLFWwindow* window, int button, int action, int mods);
	};
}


#endif // !GAMESANDBOX_TIC_TAC_TOE_MAIN_MENU_CONTROLLER_H


