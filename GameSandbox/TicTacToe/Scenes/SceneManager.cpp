#include "SceneManager.h"
#include "SceneMainMenu.h"
#include "ScenePlayerTwo.h"
#include "ScenePlayerOne.h"

ABFramework::SceneManager* ABFramework::SceneManager::pInstance = nullptr;

//********************************************************************************//
//                        Constructors / Destructor                               //
//********************************************************************************//

ABFramework::SceneManager::SceneManager()
	:pMainMenu(new SceneMainMenu()), pTwoPlayer(new ScenePlayerTwo()), pOnePlayer(new ScenePlayerOne()), pActiveScene(nullptr)
{
	pMainMenu->SetNextScene(pTwoPlayer);
	pTwoPlayer->SetNextScene(pMainMenu);
	pOnePlayer->SetNextScene(pMainMenu);
	pActiveScene = pMainMenu;

}

ABFramework::SceneManager::~SceneManager()
{
	pActiveScene = nullptr;

	delete pMainMenu;
	pMainMenu = nullptr;
	delete pTwoPlayer;
	pTwoPlayer = nullptr;
	delete pOnePlayer;
	pOnePlayer = nullptr;
	
}

void ABFramework::SceneManager::Init()
{
	CHECK_NULL(privGetInstance());
	privGetInstance()->pActiveScene->SetupScene();
}

void ABFramework::SceneManager::Destroy()
{
	delete SceneManager::pInstance;
	SceneManager::pInstance = nullptr;
}

void ABFramework::SceneManager::SwitchScene(SceneName _name)
{
	SceneManager* pInst = privGetInstance();

	switch (_name)
	{
	case ABFramework::SceneManager::SceneName::MAIN_MENU:
		pInst->pActiveScene = pInst->pMainMenu;
		pInst->pActiveScene->SetupScene();
		break;
	case ABFramework::SceneManager::SceneName::PLAYER_ONE:
		pInst->pActiveScene = pInst->pOnePlayer;
		pInst->pActiveScene->SetupScene();
		break;
	case ABFramework::SceneManager::SceneName::PLAYER_TWO:
		pInst->pActiveScene = pInst->pTwoPlayer;
		pInst->pActiveScene->SetupScene();
		break;
	default:
		break;
	}

}

void ABFramework::SceneManager::NextScene()
{
	SceneManager* pInst = privGetInstance();
	pInst->pActiveScene->CleanUpScene();
	pInst->pActiveScene = pInst->pActiveScene->NextScene();
	pInst->pActiveScene->SetupScene();

}

void ABFramework::SceneManager::Update()
{
	privGetInstance()->pActiveScene->Update();
}

void ABFramework::SceneManager::Draw()
{
	privGetInstance()->pActiveScene->Draw();
}

ABFramework::SceneMainMenu* ABFramework::SceneManager::GetMainMenuScene()
{
	return privGetInstance()->pMainMenu;
}

ABFramework::ScenePlayerTwo* ABFramework::SceneManager::GetPlayerTwoScene()
{
	return privGetInstance()->pTwoPlayer;
}

ABFramework::ScenePlayerOne* ABFramework::SceneManager::GetPlayerOneScene()
{
	return privGetInstance()->pOnePlayer;
}

//********************************************************************************//
//                               Operators                                        //
//********************************************************************************//




//********************************************************************************//
//                                Utility                                         //
//********************************************************************************//




//********************************************************************************//
//                                Setters                                         //
//********************************************************************************//



//********************************************************************************//
//                                Getters                                         //
//********************************************************************************//



//********************************************************************************//
//                             Private Helpers                                    //
//********************************************************************************//

ABFramework::SceneManager* ABFramework::SceneManager::privGetInstance()
{
	if (SceneManager::pInstance == nullptr)
		SceneManager::pInstance = new SceneManager();
	return SceneManager::pInstance;
}

