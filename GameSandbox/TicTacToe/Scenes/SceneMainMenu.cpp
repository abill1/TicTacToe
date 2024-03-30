#include "SceneMainMenu.h"
#include "../Engine/Core/GameObject/GameObjectManager.h"
#include "../Engine/Core/AssetManager/AssetManager.h"
#include "../Engine/Renderer/OpenGL/Texture/Texture.h"
#include "../Engine/Renderer/OpenGL/SimpleMeshes/SquareMesh/SquareMesh.h"
#include "../Engine/Core/Camera/Camera.h"
#include "../Engine/Core/Window/Window.h"
#include "../Engine/Core/AssetManager/AssetDef/AssetDef.h"
#include "../Engine/Core/GameObject/Sprite/Sprite.h"
#include "../Engine/Core/Collision/Collider/AABB.h"
#include "../Engine/Core/Input/Input.h"
#include "../Controller/MainMenuController.h"
#include "../Scenes/SceneManager.h"

//********************************************************************************//
//                        Constructors / Destructor                               //
//********************************************************************************//

ABFramework::SceneMainMenu::SceneMainMenu()
	:Scene(), pExitBtn(new Sprite()), pTwoPlayerBtn(new Sprite()), pOnePlayerBtn(new Sprite())
{
	t_handle h_exitBtn = AssetManager::AddTexture(ExitBtn);
	Square_Mesh* pMesh = AssetManager::GetSquareMesh();
	pExitBtn->SetMesh(pMesh);
	pExitBtn->SetTexture(AssetManager::FindTexture(h_exitBtn));
	pExitBtn->SetPosition(Point3D(0.0f, -100.0f, 0.0f));
	pExitBtn->SetScale(Scale(640.0f, 48.0f, 0.0f));

	t_handle h_twoPlayerBtn = AssetManager::AddTexture(TwoPlayerBtn);
	pTwoPlayerBtn->SetMesh(pMesh);
	pTwoPlayerBtn->SetTexture(AssetManager::FindTexture(h_twoPlayerBtn));
	pTwoPlayerBtn->SetPosition(Point3D(0.0f, 0.0f, 0.0f));
	pTwoPlayerBtn->SetScale(Scale(640.0f, 48.0f, 0.0f));

	t_handle h_onePlayerBtn = AssetManager::AddTexture(OnePlayerBtn);
	pOnePlayerBtn->SetMesh(pMesh);
	pOnePlayerBtn->SetTexture(AssetManager::FindTexture(h_onePlayerBtn));
	pOnePlayerBtn->SetPosition(Point3D(0.0f, 100.0f, 0.0f));
	pOnePlayerBtn->SetScale(Scale(640.0f, 48.0f, 0.0f));

}

ABFramework::SceneMainMenu::~SceneMainMenu()
{
	delete pOnePlayerBtn;
	pOnePlayerBtn = nullptr;
	delete pTwoPlayerBtn;
	pTwoPlayerBtn = nullptr;
	delete pExitBtn;
	pExitBtn = nullptr;

}

//********************************************************************************//
//                               Operators                                        //
//********************************************************************************//




//********************************************************************************//
//                                Utility                                         //
//********************************************************************************//

void ABFramework::SceneMainMenu::SetupScene()
{
	Input::BindAction(&MainMenuController::OnClickLeft);
}

void ABFramework::SceneMainMenu::CleanUpScene()
{
	Input::UnbindAction(MouseCode::BUTTON_LEFT);

}

void ABFramework::SceneMainMenu::Update()
{
	pOnePlayerBtn->Update();
	pTwoPlayerBtn->Update();
	pExitBtn->Update();
}

void ABFramework::SceneMainMenu::Draw()
{
	pOnePlayerBtn->Draw(Camera::GetViewProjectionMatrix());
	pTwoPlayerBtn->Draw(Camera::GetViewProjectionMatrix());
	pExitBtn->Draw(Camera::GetViewProjectionMatrix());
}


//********************************************************************************//
//                                Setters                                         //
//********************************************************************************//



//********************************************************************************//
//                                Getters                                         //
//********************************************************************************//

ABFramework::Sprite* ABFramework::SceneMainMenu::GetExitBtn() const
{
	return pExitBtn;
}

ABFramework::Sprite* ABFramework::SceneMainMenu::GetTwoPlayerBtn() const
{
	return pTwoPlayerBtn;
}

ABFramework::Sprite* ABFramework::SceneMainMenu::GetOnePlayerBtn() const
{
	return pOnePlayerBtn;
}

//********************************************************************************//
//                             Private Helpers                                    //
//********************************************************************************//

