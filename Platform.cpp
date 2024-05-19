#include "Platform.h"

Window::Window(int width, int height, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(1920, 1080, "Sokuban", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(window);
}

void Window::Close()
{
	glfwSetWindowShouldClose(window, true);
}

bool Window::IsKeyPressed(int key)
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Window::IsMouseButtonPressed(int button)
{
	return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

bool Window::IsClosed()
{
	return glfwWindowShouldClose(window);
}
