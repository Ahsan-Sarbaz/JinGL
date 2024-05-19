#pragma once

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
	Window(int width, int height, const char* title);
	~Window();

	/**
	* Updates the window i.e poll events and swap buffers
	*/
	void Update();

	/**
	* Closes the window
	*/
	void Close();

	/**
	* Check if the window is closed
	* 
	* @return true if the window is closed
	*/
	bool IsClosed();

	/**
	* Check if the key is pressed
	* 
	* @param key key to check
	* @return true if the key is pressed
	*/
	bool IsKeyPressed(int key);

	/**
	* Check if the mouse button is pressed
	* 
	* @param button button to check
	* @return true if the mouse button is pressed
	*/
	bool IsMouseButtonPressed(int button);

private:
	GLFWwindow* window;
};
