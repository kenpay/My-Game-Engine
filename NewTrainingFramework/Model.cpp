#include "stdafx.h"
#include "Model.h"
#include <stdio.h>
#include <exception>


Model::Model(char *path) : ModelResource(path), lastPoint(0), iboId(new GLuint[0]), vboId(new GLuint[0]), minX(0), maxX(0), minY(0), maxY(0), minZ(0), maxZ(0)
{
	FILE* file;
	errno_t error = fopen_s(&file, getPath(), "r");
	if (!error && file != NULL)
	{
		int index;
		char buffer[255];
		fgets(buffer, 255, file);
		sscanf_s(buffer, "NrVertices: %d", &this->nrVertices);
		this->vertices = new Vertex[this->nrVertices];
		for (index = 0; index < this->nrVertices; index++)
		{
			fgets(buffer, 255, file);
			GLfloat pos1, pos2, pos3, norm1, norm2, norm3, binorm1, binorm2, binorm3, tgt1, tgt2, tgt3, uv1, uv2;
			sscanf_s(buffer + 6, "pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];", &pos1, &pos2, &pos3, &norm1, &norm2, &norm3, &binorm1, &binorm2, &binorm3, &tgt1, &tgt2, &tgt3, &uv1, &uv2);
			this->vertices[index] = Vertex(Vector3(pos1, pos2, pos3) / 120, Vector3(norm1, norm2, norm3), Vector3(binorm1, binorm2, binorm3), Vector3(tgt1, tgt2, tgt3), Vector2(uv1, uv2));
		}
		fgets(buffer, 255, file);
		sscanf_s(buffer, "NrIndices: %d", &this->nrIndexes);
		this->indexes = new GLushort[this->nrIndexes];
		for (index = 0; index < this->nrIndexes; index += 3)
		{
			GLushort f1, f2, f3;
			fgets(buffer, 255, file);
			sscanf_s(buffer + 5, "%hu, %hu, %hu", &f1, &f2, &f3);
			this->indexes[index] = (GLushort)f1;
			this->indexes[index + 1] = (GLushort)f2;
			this->indexes[index + 2] = (GLushort)f3;
		}
		fclose(file);
	}
	else
		throw(std::exception("couldn't open file"));
};

Model::Model(GLint _nrVertixes, GLint _nrIndexes, Vertex* vertexes, GLushort* _indexes) : ModelResource(NULL), nrVertices(_nrVertixes), nrIndexes(_nrIndexes), vertices(vertexes), indexes(_indexes), lastPoint(0), iboId(new GLuint[0]), vboId(new GLuint[0]), minX(0), maxX(0), minY(0), maxY(0), minZ(0), maxZ(0)
{
}

GLuint Model::generateBuffer()
{
	vboId = arrayCopy(vboId, lastPoint);
	iboId = arrayCopy(iboId, lastPoint);

	//Collision points;
	GLint index;
	for (index = 0; index < nrVertices; index++)
	{
		Vertex& elementV = vertices[index];
		Vector3& elementVPosition = elementV.getPosition();
		if (elementVPosition.x > maxX)
			maxX = elementVPosition.x;
		else if (elementVPosition.x < minX)
			minX = elementVPosition.x;
		if (elementVPosition.y > maxY)
			maxY = elementVPosition.y;
		else if (elementVPosition.y < minY)
			minY = elementVPosition.y;
		if (elementVPosition.z > maxZ)
			maxZ = elementVPosition.z;
		else if (elementVPosition.z < minZ)
			minZ = elementVPosition.z;
	}

	glGenBuffers(1, vboId + lastPoint);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[lastPoint]);
	glBufferData(GL_ARRAY_BUFFER, this->nrVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, iboId + lastPoint);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId[lastPoint]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndexes * sizeof(GLushort), indexes, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return lastPoint++;
}


Model::~Model()
{
	glDeleteBuffers(lastPoint, vboId);
	glDeleteBuffers(lastPoint, iboId);
}
