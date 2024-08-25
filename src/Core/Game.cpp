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


void Game::OnStart()
{
	TimeTaken InitGame("Init Game");

	m_Time.Init(100);


	m_WindowProp.width = 1000;
	m_WindowProp.height = 700;

	if (m_UseFullScreen)
		m_WindowProp.width = GetSystemMetrics(SM_CXSCREEN), m_WindowProp.height = GetSystemMetrics(SM_CYSCREEN);



	m_Window = new Window(m_WindowProp);

	//m_CurrentScene = new MainScene();
	//m_CurrentScene = new Light_ModelScene();
	//m_CurrentScene = new AdvanceOpenGLScene();
	m_CurrentScene = new FaceCullingScene();
	//m_CurrentScene = new Texture_FrameBufferScene();

	if (m_Window && m_CurrentScene)
	{
		m_CurrentScene->OnInit(m_Window);

		//UIManager
		m_UI = new UIManager(*m_Window);
		//m_UI->OnInit(*m_Window);

		m_Running = true;
		return;
	}
	std::cout << "Failed to init window &/ Scene!!!!!\n";
}


void Game::Run()
{
	while (m_Running)
	{
		m_Time.Update();

		Input();

		m_CurrentScene->OnUpdate(m_Time.DeltaTime());

		m_UI->OnStartFrame();
		m_CurrentScene->OnRenderUI();
		m_UI->OnEndFrame();

		m_Window->OnUpdate();
	}

	OnEnd();
}

void Game::OnEnd()
{
	TimeTaken ShuttingDown("Shutting down program");

	m_CurrentScene->OnDestroy();
	delete m_CurrentScene;
	m_CurrentScene = nullptr;

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






