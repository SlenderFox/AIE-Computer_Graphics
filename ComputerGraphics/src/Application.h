#pragma once

struct GLFWwindow;

class Application
{
public:
	Application();
	virtual ~Application();

	// Main application loop
	void run(const char* pTitle, unsigned int pWidth, unsigned int pHeight, bool pFullscreen);

	// Functions to be implemented by the derived class
	virtual bool startup() = 0;
	virtual void shutdown() = 0;
	virtual void update(float pDeltaTime) = 0;
	virtual void draw() = 0;

	// Wipes the screen to the background colour
	void clearScreen();

	// Changes the colour of the background
	void setBackgroundColour(float pR, float pG, float pB, float pA = 1.0f);

	// Toggle the visiblity of the default cursor
	void setShowCursor(bool pVisible);

	// Sets m_gameOver to true, ending the app
	void quit() { m_gameOver = true; }

	// Returns a pointer to the game window
	GLFWwindow* getWindowPtr() const { return m_window; }

	// Returns whether or not the window is closed
	bool hasWindowClosed();

	// Returns the width and height of the window
	unsigned int getWindowWidth() const;
	unsigned int getWindowHeight() const;

protected:
	bool createWindow(const char* pTitle, unsigned int pWidth, unsigned int pHeight, bool pFullscreen);
	void destroyWindow();

	GLFWwindow*		m_window;

	bool					m_gameOver;

	unsigned int		m_fps;
};