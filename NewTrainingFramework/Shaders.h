#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	GLint matrixUniform;
	GLint mvpMatrix;
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute, uvAttribute, sampler2DUnif;
	GLint colorsAttribute;
	virtual int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};

class LineShader: public Shaders
{
public:
	int Init(char * fileVertexShader, char * fileFragmentShader);
};