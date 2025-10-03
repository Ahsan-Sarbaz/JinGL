#include "Platform.h"
#include <string.h>

Window::Window(int32_t width, int32_t height, const char* title, bool full_screen)
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

	int32_t final_width = width;
	int32_t final_height = height;
	int32_t window_pos_x = 0;
	int32_t window_pos_y = 0;
	auto monitor = glfwGetPrimaryMonitor();
	auto mode = glfwGetVideoMode(monitor);

	if (full_screen) {
		final_width = mode->width;
		final_height = mode->height;
	} else {
		// If width or height is 0, set it to 75% of the screen size
		if (final_width == 0 || final_height == 0) {
			final_width = int32_t(float(mode->width) * 0.75);
			final_height = int32_t(float(mode->height) * 0.75);
		}

		// If the window size is smaller than the screen size, window is centered
		if (final_width != mode->width || final_height != mode->height) {
			window_pos_x = (mode->width - final_width) / 2;
			window_pos_y = (mode->height - final_height) / 2;
		}
	}


	this->width = final_width;
	this->height = final_height;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_POSITION_X, window_pos_x);
	glfwWindowHint(GLFW_POSITION_Y, window_pos_y);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(final_width, final_height, this->title, full_screen ? monitor : nullptr, nullptr);
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
