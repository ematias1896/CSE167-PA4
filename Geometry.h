#ifndef GEOMETRY_H
#define GEOMETRY_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h> // Remove this line in future projects
#else
#include <GL/glew.h>
#endif

#include<GLFW/glfw3.h>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<iostream>
#include<stdio.h>
#include<vector>
#include<string>
#include<algorithm>
#include"Node.h"
#include"shader_m.h"
#include"camera.h"

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

class Geometry : public Node
{
public:
	Geometry();
	~Geometry();
	void init(std::string filepath);
	void update();
	void draw(glm::mat4 C, Shader* shaderProgram, Camera camera, glm::mat4 projection, bool phong);

private:
	bool initialized;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> nindices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4 toWorld;
	glm::mat4 totalRot;
	glm::mat4 rotOffset;
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	GLuint NBO;
	int direction;
	float angle;
	float scalePointAmount;
	float scaleAmount;
	float baseX;
	float baseY;
	float baseZ;
	float x;
	float y;
	float z;
	bool transFirst = false;

	void parse(const char* filepath);
	void centerAndResize();
};

#endif
