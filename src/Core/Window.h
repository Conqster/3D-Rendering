#pragma once
#include "glm/glm.hpp"

struct GLFWwindow;

class Window
{
public:
	Window();
	Window(unsigned int width, unsigned int height);
	Window(unsigned int width, unsigned int height, const char* program_name);

	bool Init();

	void SwapBuffers() const;
	void ToggleLockCursor();
	bool WindowShouldClose() const;

	void Close() const;

	inline bool const Initilised() { return m_Initilised; }
	inline unsigned int const GetWidth() { return m_Width; }
	inline unsigned int const GetHeight() { return m_Height; }
	inline float const GetAspectRatio() { return (float)m_Width / (float)m_Height; }
	glm::vec2 GetMouseScreenPosition();

	inline bool* const Ptr_LockCursorFlag() { return &m_LockCursor; }

	GLFWwindow* GetNativeWindow() const { return m_Window; }

	~Window();
private:
	unsigned int m_Width;
	unsigned int m_Height;

	GLFWwindow* m_Window = nullptr;
	const char* m_ProgramName = "default";

	bool m_LockCursor = false;
	bool m_Initilised = false;
};
