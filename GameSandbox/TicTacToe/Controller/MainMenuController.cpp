#include "MainMenuController.h"
#include "../Engine/Core/Collision/Collision.h"
#include "../Engine/Core/Input/Input.h"
#include "../Engine/Core/Collision/Collider/AABB.h"
#include "../Engine/Core/GameObject/Sprite/Sprite.h"
#include "../Scenes/SceneMainMenu.h"
#include "../Scenes/SceneManager.h"
#include "../Engine/Core/Window/Window.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

//********************************************************************************//
//                                Utility                                         //
//********************************************************************************//

void ABFramework::MainMenuController::OnClickLeft(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		if (Collision::Check(SceneManager::GetMainMenuScene()->GetExitBtn()->GetCollider(), Input::GetMouseCollider()))
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		else if (Collision::Check(SceneManager::GetMainMenuScene()->GetTwoPlayerBtn()->GetCollider(), Input::GetMouseCollider()))
		{
			SceneManager::NextScene();
		}
	}
}


