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

	/**
	* Get the delta time
	* 
	* @return delta time
	*/
	float GetDeltaTime() const;

	/**
	* Get the time
	* 
	* @return time
	*/
	float GetTime() const;

	/**
	* Get the width
	* 
	* @return width
	*/
	inline int GetWidth() const { return width; }

	/**
	* Get the height
	* 
	* @return height
	*/
	inline int GetHeight() const { return height; }

	/**
	* Get the title
	* 
	* @return title
	*/
	inline const char* GetTitle() const { return title; }

private:
	GLFWwindow* window;
	float deltaTime = 0.0f;
	float thisFrameTime = 0.0f;
	float lastFrameTime = 0.0f;
	float time = 0.0f;
	int width;
	int height;
	const char* title;
};
