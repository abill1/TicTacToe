
#ifndef ABFRAMEWORK_INPUT_H
#define ABFRAMEWORK_INPUT_H

#include "Keyboard.h"
#include "Mouse.h"
#include "InputMapping.h"

#include "../Engine/Core/Window/Window.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace ABFramework
{
	class Input
	{
	private:
		// ----- Constructor / Destructor ----- //

		Input();

	public:
		~Input();

		// ----- Operators ----- //

		// ------ Utility ----- //

		static bool Init();
		static void Destroy();

		static void Process();

		static bool IsPressed(KeyCode _key);
		static bool IsPressed(MouseCode _button);
		static CursorCoord GetCursorPosition();
		static CursorCoord GetTrueCursorPosition();

		static void BindAction(GLFWmousebuttonfun _glfwFunc);
		static void BindAction(MouseCode _code, t_inputAction _func, PlayerController* _pObj);
		static void BindAction(KeyCode _code, t_inputAction _func, PlayerController* _pObj);
		static void UnbindAction(MouseCode _code);
		static void UnbindAction(KeyCode _code);
		static void CallAction(MouseCode _code);
		static void CallAction(KeyCode _code);

		// ----- Setters ----- //

		static void SetFocus(class Window* const _pFocus);

		// ----- Getters ----- //

		static class AABB* GetMouseCollider();

	private:
		static Input* privGetInstance();

	private:
		static Input* pInstance;

		class Window* pFocus;
		InputMapping* m_MouseInputMappings;
		bool* m_CurrentMouseButtonState;
		bool* m_PreviousMoustButtonState;
		std::unordered_map<int, InputMapping> m_KeyInputMappings;
		std::unordered_map<int, int> m_KeyState;
		class AABB* pMouseCollider;

	};
}

#endif // !ABFRAMEWORK_INPUT_H


