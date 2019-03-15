#include "Application.h"
#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Gizmos.h>

using aie::Gizmos;

Application::Application() : m_window(nullptr), m_gameOver(false), m_fps(0)
{
}

Application::~Application()
{
}

bool Application::createWindow(const char* pTitle, const unsigned int pWidth, const unsigned int pHeight, const bool pFullscreen)
{
	if (glfwInit() == GL_FALSE)
		return false;

	m_window = glfwCreateWindow(pWidth, pHeight, pTitle, (pFullscreen ? glfwGetPrimaryMonitor() : nullptr ), nullptr);

	if (m_window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return false;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	glClearColor(0.12f, 0.12f, 0.12f, 1);
	glEnable(GL_DEPTH_TEST);	// Enables the depth buffer

	return true;
}

void Application::destroyWindow()
{
	Gizmos::destroy();

	glfwTerminate();
}

void Application::run(const char* pTitle, const unsigned int pWidth, const unsigned int pHeight, const bool pFullscreen)
{
	// Starts the game loop upon successful initialisation
	if (createWindow(pTitle, pWidth, pHeight, pFullscreen) && startup())
	{
		// Variables for timing
		double prevTime = glfwGetTime();
		double currTime = 0;
		double deltaTime = 0;
		unsigned int frames = 0;
		double fpsInterval = 0;

		while (!m_gameOver)
		{
			// Update deltaTime
			currTime = glfwGetTime();
			deltaTime = currTime - prevTime;
			prevTime = currTime;

			// Update window events such as inputs
			glfwPollEvents();

			// Skip if minimised
			if (glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) != 0)
				continue;

			// Update fps every half second
			frames++;
			fpsInterval += deltaTime;
			if (fpsInterval >= 0.5f)
			{
				m_fps = frames * 2;
				frames = 0;
				fpsInterval -= 0.5f;
			}

			// Call child update function
			update(float(deltaTime));

			// Call child draw function
			draw();

			glfwSwapBuffers(m_window);

			// Has the window been closed?
			m_gameOver = m_gameOver || hasWindowClosed();
		}

		// Cleanup
		shutdown();
		destroyWindow();
	}
}

void Application::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Application::setBackgroundColour(const float pR, const float pG, const float pB, const float pA)
{
	glClearColor(pR, pG, pG, pA);
}

void Application::setShowCursor(const bool pVisible)
{
	ShowCursor(pVisible);
}

bool Application::hasWindowClosed() const
{
	return glfwWindowShouldClose(m_window) == GL_TRUE;
}

unsigned int Application::getWindowWidth() const
{
	int w = 0, h = 0;
	glfwGetWindowSize(m_window, &w, &h);
	return w;
}

unsigned int Application::getWindowHeight() const
{
	int w = 0, h = 0;
	glfwGetWindowSize(m_window, &w, &h);
	return h;
}
