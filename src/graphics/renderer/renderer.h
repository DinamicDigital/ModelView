#pragma once


void init_renderer();

void render();

void set_viewport(int x, int y, int width, int height);


typedef struct mv_raw_mesh {
	float* verticies;
	unsigned int vbo;
	unsigned int vao;
	unsigned int shader;
} Raw_Mesh;

void init_raw_mesh(Raw_Mesh* raw_mesh, float* verticies);

void draw_raw_mesh(Raw_Mesh* raw_mesh);

void free_raw_mesh(Raw_Mesh* raw_mesh);