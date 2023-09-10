#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "ModelResource.h"
class Model : ModelResource
{
	GLint nrVertices, nrIndexes;
	GLuint* iboId, * vboId, lastPoint;
	GLfloat minX, maxX, minY, maxY, minZ, maxZ;
	Vertex* vertices;
	GLushort* indexes;
public:
	Model(char* path);
	Model(GLint, GLint, Vertex*, GLushort*);
	GLint getNrVertices() { return this->nrVertices; }
	Vertex* getVerticesData() { return this->vertices; }
	GLint getNrIndexes() { return this->nrIndexes; }
	GLushort* getIndexesData() { return this->indexes; }
	GLint getIBOId(int i) { return iboId[i]; }
	GLint getVBOId(int i) { return vboId[i]; }
	Vector3 getMin() { return Vector3(minX, minY, minZ); }
	Vector3 getMax() { return Vector3(maxX, maxY, maxZ); }
	GLuint generateBuffer();
	~Model();
};

