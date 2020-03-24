#include "renderer.h"
#include "../GLAD/glad.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

void init_renderer()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fprintf(stderr, "glad failed to init\n"); // fallback when something goes wrong later maybe
	}
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);


}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	// call this at the end of frame.
	glfwSwapBuffers(window);
}

void set_viewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}

void init_raw_mesh(Raw_Mesh* raw_mesh, float* verticies)
{
	int vert_size = sizeof(verticies) / sizeof(verticies[0]);
	
	raw_mesh->verticies = (float*) malloc(vert_size);
	raw_mesh->verticies = verticies;

	glGenVertexArrays(1, &(raw_mesh->vao));
	glBindVertexArray(raw_mesh->vao);


	glGenBuffers(1, &(raw_mesh->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, raw_mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(raw_mesh->verticies), raw_mesh->verticies, GL_STATIC_DRAW);

	const char* vss = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

   	unsigned int vs;
   	vs = glCreateShader(GL_VERTEX_SHADER);
   	glShaderSource(vs, 1, &vss, 0);
   	glCompileShader(vs);

   	int success;
   	char log[512];
   	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
   	if (!success)
   	{
   		glGetShaderInfoLog(vs, 512, NULL, log);
   		fprintf(stderr, "Vertex Shader Error:\n%s\n", log);
   	}

   	const char* fss = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 3.0f, 1.0f);\n"
    "}\0";

    unsigned int fs;
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fss, 0);
    glCompileShader(fs);

    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success)
    {
    	glGetShaderInfoLog(fs, 512, NULL, log);
    	fprintf(stderr, "Fragment Shader Error:\n%s\n", log);
    }

    raw_mesh->shader = glCreateProgram();
    glAttachShader(raw_mesh->shader, vs);
    glAttachShader(raw_mesh->shader, fs);

    glLinkProgram(raw_mesh->shader);

    glGetProgramiv(raw_mesh->shader, GL_LINK_STATUS, &success);
    if (!success)
    {
    	glGetProgramInfoLog(raw_mesh->shader, 512, NULL, log);
    	fprintf(stderr, "Shader Link Error:\n%s\n", log);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}


void draw_raw_mesh(Raw_Mesh* raw_mesh)
{
	glUseProgram(raw_mesh->shader);
	glBindVertexArray(raw_mesh->vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void free_raw_mesh(Raw_Mesh* raw_mesh) 
{
	free(raw_mesh->verticies);
}