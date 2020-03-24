#include <GLFW/glfw3.h>

// Prototypes

void init_glfw();

void init_external_libraries()
{
	init_glfw();
}

void init_glfw()
{
	if (!glfwInit())
    {
    	fprintf(stderr, "GLFW failed to init\n");
        return;
    }
    glfwSwapInterval(1);
}