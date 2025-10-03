#pragma once

#include <stdint.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	/**
	* Creates the window
	* 
	* @param width width of the window
	* @param height height of the window
	* @param title title of the window
	*/
	Window(int32_t width, int32_t height, const char* title, bool full_screen = false);
	~Window();

	/**
	* Starts a new frame
	*/
	void StartFrame();

	/**
	* Ends a frame
	*/
	void EndFrame();

	/**
	* Closes the window
	*/
	void Close();

	/**
	* Check if the window is closed
	* 
	* @return true if the window is closed
	*/
	inline bool IsClosed() const { return glfwWindowShouldClose(window); }

	/**
	* Check if window is open
	* 
	* @return true if the window is open
	*/
	inline bool IsOpen() const { return !glfwWindowShouldClose(window); }

	/**
	* Check if the window is focused
	* 
	* @return true if the window is focused
	*/
	inline bool IsFocused() const { return glfwGetWindowAttrib(window, GLFW_FOCUSED); }

	/**
	* Check if the key is pressed
	* 
	* @param key key to check
	* @return true if the key is pressed
	*/
	inline bool IsKeyPressed(int key) const { return glfwGetKey(window, key) == GLFW_PRESS; }

	/**
	* Check if the mouse button is pressed
	* 
	* @param button button to check
	* @return true if the mouse button is pressed
	*/
	inline bool IsMouseButtonPressed(int button) const { return glfwGetMouseButton(window, button) == GLFW_PRESS; }

	/**
	* Get the delta time
	* 
	* @return delta time
	*/
	inline double GetDeltaTime() const { return deltaTime;}

	/**
	* Get the time
	* 
	* @return time
	*/
	inline double GetTime() const { return time; }

	/**
	* Get the width
	* 
	* @return width
	*/
	inline int32_t GetWidth() const { return width; }

	/**
	* Get the height
	* 
	* @return height
	*/
	inline int32_t GetHeight() const { return height; }

	/**
	* Get the title
	* 
	* @return title
	*/
	inline const char* GetTitle() const { return title; }

private:
	GLFWwindow* window;
	double deltaTime = 0.0f;
	double thisFrameTime = 0.0f;
	double lastFrameTime = 0.0f;
	double time = 0.0f;
	int32_t width;
	int32_t height;
	char* title;
};
