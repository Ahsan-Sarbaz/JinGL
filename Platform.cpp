#include "Platform.h"

Window::Window(int width, int height, const char* title)
	: width(width), height(height), title(title)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, "Sokuban", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::StartFrame()
{
	thisFrameTime = glfwGetTime();
	deltaTime = thisFrameTime - lastFrameTime;
	time += deltaTime;
	glfwPollEvents();
}

void Window::EndFrame()
{
	glfwSwapBuffers(window);
	lastFrameTime = thisFrameTime;
}

void Window::Close()
{
	glfwSetWindowShouldClose(window, true);
}

bool Window::IsClosed()
{
	return glfwWindowShouldClose(window);
}


bool Window::IsKeyPressed(int key)
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Window::IsMouseButtonPressed(int button)
{
	return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

float Window::GetDeltaTime() const
{
	return deltaTime;
}

float Window::GetTime() const
{
	return time;
}
