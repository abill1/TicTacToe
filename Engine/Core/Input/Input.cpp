#include "Input.h"
#include "../Engine/Core/Collision/Collider/AABB.h"

ABFramework::Input* ABFramework::Input::pInstance = nullptr;

//********************************************************************************//
//                        Constructors / Destructor                                //
//********************************************************************************//

ABFramework::Input::Input()
	:pFocus(nullptr), m_MouseInputMappings(new InputMapping[(int)MouseCode::COUNT]()), m_CurrentMouseButtonState(new bool[(int)MouseCode::COUNT]), m_PreviousMoustButtonState(new bool[(int)MouseCode::COUNT]), m_KeyInputMappings(), m_KeyState(), pMouseCollider(new AABB())
{
	memset(m_CurrentMouseButtonState, 0, (int)MouseCode::COUNT);
	memset(m_PreviousMoustButtonState, 0, (int)MouseCode::COUNT);
}

ABFramework::Input::~Input()
{
	delete[] m_MouseInputMappings;
	delete[] m_CurrentMouseButtonState;
	delete[] m_PreviousMoustButtonState;
	pFocus = nullptr;
	delete pMouseCollider;

}


bool ABFramework::Input::Init()
{
	return privGetInstance() != nullptr;
}

void ABFramework::Input::Destroy()
{
	delete pInstance;
	pInstance = nullptr;
}



//********************************************************************************//
//                               Operators                                        //
//********************************************************************************//




//********************************************************************************//
//                                Utility                                         //
//********************************************************************************//

void ABFramework::Input::Process()
{
	// ----- Need to loop through all input options
	std::unordered_map<int, int>::iterator kit = privGetInstance()->m_KeyState.begin();
	std::unordered_map<int, int>::iterator kEnd = privGetInstance()->m_KeyState.end();
	while (kit != kEnd)
	{
		if (privGetInstance()->IsPressed((KeyCode)kit->first))
		{			
			privGetInstance()->CallAction((KeyCode)kit->first);
		}
		++kit;
	}

}

bool ABFramework::Input::IsPressed(ABFramework::KeyCode _key)
{
	bool bPressed = false;
	int state = glfwGetKey(privGetInstance()->pFocus->GetWindow(), Keyboard::ToInt(_key));
	if (privGetInstance()->m_KeyState[(int)_key] != GLFW_PRESS && state == GLFW_PRESS)
	{
		bPressed = true;
	}

	privGetInstance()->m_KeyState[(int)_key] = state;

	return bPressed;
}

bool ABFramework::Input::IsPressed(ABFramework::MouseCode _button)
{
	bool bPressed = false;
	return bPressed;
}

ABFramework::CursorCoord ABFramework::Input::GetCursorPosition()
{
	double x;
	double y;
	glfwGetCursorPos(privGetInstance()->pFocus->GetWindow(), &x, &y);
	Window::Resolution resolution = privGetInstance()->pFocus->GetResolution();
	return { ((float)x - (resolution.width / 2.0f)), ((float)-y + (resolution.height / 2.0f)) };
}

ABFramework::CursorCoord ABFramework::Input::GetTrueCursorPosition()
{
	double x;
	double y;
	glfwGetCursorPos(privGetInstance()->pFocus->GetWindow(), &x, &y);
	return { (float)x, (float)y };
}

void ABFramework::Input::BindAction(MouseCode _code, t_inputAction _func, PlayerController* _pObj)
{
	InputMapping tmp(_func, _pObj);
	privGetInstance()->m_MouseInputMappings[(int)_code] = tmp;
}

void ABFramework::Input::BindAction(GLFWmousebuttonfun _glfwFunc)
{
	glfwSetMouseButtonCallback(privGetInstance()->pFocus->GetWindow(), _glfwFunc);
}

void ABFramework::Input::BindAction(KeyCode _code, t_inputAction _func, PlayerController* _pObj)
{
	InputMapping tmp(_func, _pObj);
	privGetInstance()->m_KeyInputMappings[(int)_code] = tmp;
	privGetInstance()->m_KeyState[(int)_code] = GLFW_RELEASE;
}

void ABFramework::Input::UnbindAction(MouseCode _code)
{
	glfwSetMouseButtonCallback(privGetInstance()->pFocus->GetWindow(), nullptr);
}

void ABFramework::Input::UnbindAction(KeyCode _code)
{
	privGetInstance()->m_KeyInputMappings[(int)_code] = {};
	privGetInstance()->m_KeyState[(int)_code] = false;
}

void ABFramework::Input::CallAction(MouseCode _code)
{
	privGetInstance()->m_MouseInputMappings[(int)_code]();
}

void ABFramework::Input::CallAction(KeyCode _code)
{
	privGetInstance()->m_KeyInputMappings[(int)_code]();
}


//********************************************************************************//
//                                Setters                                         //
//********************************************************************************//

void ABFramework::Input::SetFocus(ABFramework::Window* const _pFocus)
{

	privGetInstance()->pFocus = _pFocus;
}

//********************************************************************************//
//                                Getters                                         //
//********************************************************************************//

ABFramework::AABB* ABFramework::Input::GetMouseCollider()
{
	CursorCoord coord = privGetInstance()->GetCursorPosition();
	privGetInstance()->pMouseCollider->Set(Point2D(coord.x, coord.y), Scale(0.0f));
	return privGetInstance()->pMouseCollider;
}

//********************************************************************************//
//                             Private Helpers                                    //
//********************************************************************************//

ABFramework::Input* ABFramework::Input::privGetInstance()
{
	if (Input::pInstance == nullptr)
		Input::pInstance = new Input();
	CHECK_NULL(Input::pInstance);
	return Input::pInstance;
}


