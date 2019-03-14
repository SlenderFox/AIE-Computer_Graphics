#pragma once

struct GLFWwindow;

class Application
{
public:
	Application();
	virtual ~Application();

	// Main application loop
	void run(const char* pTitle, int pWidth, int pHeight, bool pFullscreen);

protected:
	bool createWindow(const char* pTitle, int pWidth, int pHeight, bool pFullscreen);
	void destroyWindow();

	GLFWwindow*		m_window;

	bool					m_gameOver;
};