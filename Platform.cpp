#include "Platform.h"
#include <string.h>

Window::Window(int32_t width, int32_t height, const char* title)
	: width(width), height(height)
{
	auto title_len = strlen(title);
	this->title = new char[title_len + 1];
#if defined(_MSC_VER) && (_MSC_VER >= 1400) && !defined(__clang__)
	strcpy_s(this->title, title_len + 1, title);
#else
	strcpy(this->title, title);
#endif
	this->title[title_len] = '\0';

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, this->title, nullptr, nullptr);
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
