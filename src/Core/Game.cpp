#pragma once
#include "Game.h"

#include "GLFW/glfw3.h"
#include "EventHandle.h"

#include "Camera.h"
#include <windows.h>

#include "Scenes/MainScene.h"
#include "Scenes/Light&ModelScene.h"
#include "Scenes/AdvanceOpenGLScene.h"
#include "Scenes/FaceCullingScene.h"
#include "Scenes/Textures_FrameBufferScene.h"

//FOR TESTING: Remove later
#include "External Libs/imgui/imgui.h"


void Game::OnStart()
{
	TimeTaken InitGame("Init Game");

	m_Time.Init(100);


	m_WindowProp.width = 1000;
	m_WindowProp.height = 700;

	if (m_UseFullScreen)
		m_WindowProp.width = GetSystemMetrics(SM_CXSCREEN), m_WindowProp.height = GetSystemMetrics(SM_CYSCREEN);



	m_Window = new Window(m_WindowProp);


	//Register scenes
	m_SceneManager = new SceneManager();
	m_SceneManager->RegisterNewScene<MainScene>("Main Scene");
	m_SceneManager->RegisterNewScene<Texture_FrameBufferScene>("Texture_FrameBufferScene");
	m_SceneManager->RegisterNewScene<Light_ModelScene>("Light Model");
	m_SceneManager->RegisterNewScene<AdvanceOpenGLScene>("Advance Scene");
	m_SceneManager->RegisterNewScene<FaceCullingScene>("Face Culling");

	//Load
	//m_CurrentScene = m_SceneManager->LoadScene("Texture_FrameBufferScene", m_Window);
	//m_CurrentScene = m_SceneManager->CreateScene("Texture_FrameBufferScene");





	if (m_Window)
	{
		
		//UIManager
		m_UI = new UIManager(*m_Window);
		//m_UI->OnInit(*m_Window);

		m_Running = true;
		m_GameState = State::LOADSCENE;

		if (m_CurrentScene)
		{
			m_CurrentScene->OnInit(m_Window);
			m_GameState = State::RUNNINGSCENE;
		}

		return;
	}
	std::cout << "Failed to init window &/ Scene!!!!!\n";
}

void Game::OnLoadSceneUI(const char* label, bool can_load)
{
	/////////////////////////////////////////////
	// UI - ImGui
	// Later create a sub ui panel, to abstract out ImGui function from Game.
	/////////////////////////////////////////////
	ImGui::Begin(label);

	static int cur_sel = 0;
	ImGui::Combo("Scenes", &cur_sel, m_SceneManager->ScenesByNamePtr(), m_SceneManager->SceneCount());

	if (ImGui::Button(label))
	{
		if (!can_load)
		{
			m_CurrentScene->OnDestroy();
			m_CurrentScene = nullptr;
		}

		//m_CurrentScene = m_SceneManager->LoadScene(m_SceneManager->ScenesByName()[cur_sel], m_Window);
		m_CurrentScene = m_SceneManager->LoadScene(m_SceneManager->ScenesByNamePtr()[cur_sel], m_Window);
		if (m_CurrentScene)
			m_GameState = State::RUNNINGSCENE;

	}


	ImGui::End();



	
}


void Game::Run()
{



	while (m_Running)
	{

		m_Time.Update();

		Input();

		switch (m_GameState)
		{
		case LOADSCENE:

			m_Window->OnWaitUpdate();

			m_UI->OnStartFrame();
			OnLoadSceneUI("load scene", true);
			m_UI->OnEndFrame();
			//m_Window->OnUpdate();
			//std::cout << "Loading scene\n";

			break;
		case RUNNINGSCENE:

			m_CurrentScene->OnUpdate(m_Time.DeltaTime());

			//std::cout << "running scene\n";
			m_UI->OnStartFrame();
			m_CurrentScene->OnRenderUI();
			OnLoadSceneUI("switch scene", false);
			m_UI->OnEndFrame();

			m_Window->OnUpdate();

			break;
		}

	}

	OnEnd();
}

void Game::OnEnd()
{
	TimeTaken ShuttingDown("Shutting down program");

	if (m_CurrentScene)
	{
		m_CurrentScene->OnDestroy();
		delete m_CurrentScene;
		m_CurrentScene = nullptr;
	}


	if (m_UI)
	{
		m_UI->OnDestroy();
		delete m_UI;
		m_UI = nullptr;
	}

	if (m_Window)
	{
		m_Window->Close();
		delete m_Window;
		m_Window = nullptr;
	}
}


void Game::Input()
{
	bool* keys = EventHandle::GetKeys();
	bool (*mouse_buttons)[3] = EventHandle::GetMouseButton();
	//bool(*key_codes)[3] = EventHandle::GetKeyCodes();



	bool program_should_close = m_Window->WindowShouldClose();


	if ((keys[GLFW_KEY_LEFT_ALT] && keys[GLFW_KEY_F4]) || program_should_close)
		m_Running = false;

	//if (keys[GLFW_KEY_ESCAPE] || program_should_close)
	//{
	//	m_Running = false;
	//}

	//int state = EventHandle::GetKeyState(Graphics::GetWindow(), GLFW_KEY_T);

	if(m_CurrentScene)
	{
		static float cooldown;
		if (keys[GLFW_KEY_T] && cooldown <= 0)
		{
			cooldown = 0.2f;
			m_CurrentScene->GetCamera()->SetPosition(glm::vec3());
		}
		else
			cooldown -= m_Time.DeltaTime();

		static float lock_cooldown;
		if (keys[GLFW_KEY_ESCAPE] && lock_cooldown <= 0)
		{
			lock_cooldown = 0.2f;
			m_Window->ToggleLockCursor();
		}
		else
			lock_cooldown -= m_Time.DeltaTime();



		//if (*m_Window->Ptr_LockCursorFlag())
		//	m_CurrentScene->GetCamera()->Rotate(EventHandle::MousePosition(), (float)m_Window->GetWidth(), (float)m_Window->GetHeight());

		if (*m_Window->Ptr_LockCursorFlag())
			m_CurrentScene->GetCamera()->Rotate(EventHandle::MousePosition(), (float)m_Window->GetWidth(), (float)m_Window->GetHeight());
		//m_CurrentScene->GetCamera()->Rotate(EventHandle::MouseXChange(), EventHandle::MouseYChange());
		else
		{
			if (mouse_buttons[GLFW_MOUSE_BUTTON_LEFT][GLFW_RELEASE] && !*m_UI->ImGuiWantCaptureMouse())
				m_Window->ToggleLockCursor();
		}



		//MOVE CAMERA
		if (keys[GLFW_KEY_W])
		{
			m_CurrentScene->GetCamera()->Translate(m_CurrentScene->GetCamera()->GetFroward(), m_Time.DeltaTime());
		}
		if (keys[GLFW_KEY_S])
		{
			m_CurrentScene->GetCamera()->Translate(m_CurrentScene->GetCamera()->GetFroward() * -1.0f, m_Time.DeltaTime());
		}
		if (keys[GLFW_KEY_A])
		{
			m_CurrentScene->GetCamera()->Translate(m_CurrentScene->GetCamera()->GetRight() * -1.0f, m_Time.DeltaTime());

		}
		if (keys[GLFW_KEY_D])
		{
			m_CurrentScene->GetCamera()->Translate(m_CurrentScene->GetCamera()->GetRight(), m_Time.DeltaTime());
		}
		if (keys[GLFW_KEY_E])
		{
			if (keys[GLFW_KEY_LEFT_SHIFT])
				m_CurrentScene->GetCamera()->Translate(m_CurrentScene->GetCamera()->GetUp(), m_Time.DeltaTime());
			else
				m_CurrentScene->GetCamera()->Translate(glm::vec3(0.0f, 1.0f, 0.0f), m_Time.DeltaTime());
		}
		if (keys[GLFW_KEY_Q])
		{
			if (keys[GLFW_KEY_LEFT_SHIFT])
				m_CurrentScene->GetCamera()->Translate(m_CurrentScene->GetCamera()->GetUp() * -1.0f, m_Time.DeltaTime());
			else
				m_CurrentScene->GetCamera()->Translate(glm::vec3(0.0f, -1.0f, 0.0f), m_Time.DeltaTime());
		}
	}
	
}






