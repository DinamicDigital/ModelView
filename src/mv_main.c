#include <stdio.h>
#include "graphics/GLAD/glad.h"
#include "graphics/window/window.h" // includes GLFW
#include "graphics/renderer/renderer.h"

#include "util/external_lib.h"


int main(int argc, char* argv[])
{

	init_external_libraries();
	
	init_window("ModelView", 800, 600);
 
	init_renderer();

	float tri_verts[] = {
    	-0.5f, -0.5f, 0.0f,
    	 0.5f, -0.5f, 0.0f,
    	 0.0f,  0.5f, 0.0f
	};


	Raw_Mesh* tri;
	init_raw_mesh(tri, tri_verts);



    /* TODO: Make messaging system for application lifetime */
    while (!glfwWindowShouldClose(window_ptr()))
    {
    	render();
    	draw_raw_mesh(tri);

        /* Poll for and process events */
        glfwPollEvents();
    }
    free_raw_mesh(tri);
    glfwTerminate();
    return 0;

}
