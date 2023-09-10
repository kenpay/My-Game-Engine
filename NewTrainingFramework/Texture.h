#pragma once
#include "TextureResource.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
class Texture : public TextureResource
{
	GLuint *idBuffer, lastPoint;
public:
	GLuint generateBuffer();
	GLuint getId(int i) { return idBuffer[i]; };
	Texture(char* _type, char* _path, char* _minFilter, char* _magFilter, char* _wrapS, char* _wrapT) : TextureResource(_type, _path, _minFilter, _magFilter, _wrapS, _wrapT), idBuffer(new GLuint[0]), lastPoint(0) { };
	~Texture() {};
};

