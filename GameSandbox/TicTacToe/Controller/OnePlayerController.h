
#ifndef GAMESANDBOX_TIC_TAC_TOE_PLAYERONECONTROLLER_H
#define GAMESANDBOX_TIC_TAC_TOE_PLAYERONECONTROLLER_H

#include "../Engine/Core/Controller/PlayerController.h"

namespace ABFramework
{
	class OnePlayerController : public PlayerController
	{
	public:
		// ----- Constructor / Destructor ----- //

		// ----- Operators ----- //

		// ------ Utility ----- //

		static void GLFWOnLeftClick(struct GLFWwindow* window, int button, int action, int mods);


		// ----- Setters ----- //

		// ----- Getters ----- //

	private:
		static void privClickLeftPlayerOne();
		static void privClickLeftPlayerTwo();

	private:

	};
}

#endif // !GAMESANDBOX_TIC_TAC_TOE_PLAYERONECONTROLLER_H


