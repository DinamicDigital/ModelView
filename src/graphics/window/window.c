#include "window.h"
#include "../renderer/renderer.h"
#include <stdio.h>
static GLFWwindow* window;

// CALLBACKS

void mv_framebuffer_resize_callback(GLFWwindow* window, int width, int height)
{
	// TODO: maybe make it update the game while resizing?

	set_viewport(0, 0, width, height);
	render();
}

// FUNCTIONS

// call this once.
void init_window(char* title, unsigned int width, unsigned int height)
{
	// TODO: handle fullscreen/monitors
	window = glfwCreateWindow(width, height, (const char*)title, 0, 0);
	if (window == 0)
	{
		fprintf(stderr, "Window did not create for some reason.\n");
		glfwTerminate();
		return;
	}

	glfwSetFramebufferSizeCallback(window, mv_framebuffer_resize_callback);
	glfwMakeContextCurrent(window);
}



GLFWwindow* window_ptr()
{
	return window;
}