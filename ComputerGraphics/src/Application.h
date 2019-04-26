#pragma once

struct GLFWwindow;

class Application
{
public:
	/*
	@brief Default constructor
	*/
	Application();

	/*
	@brief Virtual deconstructer to be overridden by derived class
	*/
	virtual ~Application();

	/*
		@brief Main application loop
		@param The title of the game window
		@param The width of the game window
		@param The height of the game window
		@param Whether or not the window is fullscreen
	*/
	void run(const char* pTitle, const unsigned int pWidth, const unsigned int pHeight, const bool pFullscreen);

	/*
		@brief Virtual function to be overridden by derived class, called when the application starts
		@return True if successful and false if fails
	*/
	virtual bool startup() = 0;

	/*
		@brief Virtual function to be overridden by derived class, called when the application ends
	*/
	virtual void shutdown() = 0;

	/*
		@brief Virtual function to be overridden by derived class, called once per frame
		@param Deltatime, the time in between frames
	*/
	virtual void update(const float pDeltaTime) = 0;

	/*
		@brief Virtual function to be overridden by derived class, called once per frame
	*/
	virtual void draw() = 0;

	/*
		@brief Wipes the screen to the background colour
	*/
	void clearScreen();

	/*
		@brief Changes the colour of the background
	*/
	void setBackgroundColour(const float pR, const float pG, const float pB, const float pA = 1.0f);

	/*
		@brief Toggle the visiblity of the default cursor
	*/
	void setShowCursor(const bool pVisible);

	/*
		@brief Sets m_gameOver to true, ending the app
	*/
	void quit() { m_gameOver = true; }

	/*
		@brief Returns a pointer to the game window
		@return A pointer to the game window
	*/
	GLFWwindow* getWindowPtr() const { return m_window; }

	/*
		@brief Returns whether or not the window is closed
		@return Whether or not the window is currently closed
	*/
	bool hasWindowClosed() const;

	/*
		@brief Returns the width of the window
		@return The width of the window
	*/
	unsigned int getWindowWidth() const;

	/*
		@brief Returns the height of the window
		@return The height of the window
	*/
	unsigned int getWindowHeight() const;

protected:

	/*
		@brief Creates a new game window using the parameters
		@param The title of the game window
		@param The width of the game window
		@param The height of the game window
		@param Whether or not the window is fullscreen
		@return Whether the window creation failed or succeded
	*/
	bool createWindow(const char* pTitle, const unsigned int pWidth, const unsigned int pHeight, const bool pFullscreen);

	/*
		@brief Destroys the window
	*/
	void destroyWindow();

	// A pointer to the window
	GLFWwindow*		m_window;

	// A bool that determines whether the game is over or not
	bool					m_gameOver;

	// The fps of the game
	unsigned int		m_fps;
};