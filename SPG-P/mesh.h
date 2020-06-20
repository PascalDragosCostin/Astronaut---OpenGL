#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "obj_loader.h"
#include "Utils.h"


enum MeshBufferPositions
{
	POSITION_VB = 0,  // sa ma asigur ca e 0, mai incolo accesez array cu enumurile astea
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};

class Mesh
{
public:
	// pentru obiect obj
    Mesh(const std::string& fileName); 
	// pentru verticies declarate in main
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices); 
	~Mesh();

	void Draw();

private:
	// 	POSITION_VB, TEXCOORD_VB, NORMAL_VB, INDEX_VB
	static const unsigned int NUM_BUFFERS = 4;

    void InitMesh(const IndexedModel& model);

	GLuint m_vertexArrayObject;  // VAO
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];  // VBO
	unsigned int m_numIndices;
};
