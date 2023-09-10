#pragma once

#include "stdafx.h"
#include "Texture.h"

GLuint Texture::generateBuffer()
{
	GLint width, height, bpp;
	GLuint type = GL_TEXTURE_2D, bppType = GL_RGB;
	idBuffer = arrayCopy(idBuffer, lastPoint);
	glGenTextures(1, idBuffer+lastPoint);
	if (!is2D())
		type = GL_TEXTURE_CUBE_MAP;

	glBindTexture(type, idBuffer[lastPoint]);
	if (isMinFilterLinear())
		if (is2D())
			glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		else
		{
			glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}

	if (isMagFilterLinear())
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (isWrapSClampToEdge())
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	else if (isWrapSRepeat())
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);

	if (isWrapTClampToEdge())
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	else if (isWrapTRepeat())
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	unsigned char* array_pixeli = (unsigned char *) LoadTGA(getPath(), &width, &height, &bpp);

	if (bpp == 32)
		bppType = GL_RGBA;

	if (is2D())
		glTexImage2D(type, 0, bppType, width, height, 0, bppType, GL_UNSIGNED_BYTE, array_pixeli);
	else
	{
		GLint imageWidth = width / 4, imageHeigth = height/3, i, j, k, bytesPerSample = bpp/8;
		char* buffer = new char[bytesPerSample * imageHeigth * imageHeigth];
		//0
		for (i = 0; i < imageWidth; i++)
			for (j = 0; j < imageHeigth; j++)
				for (k=0; k< bytesPerSample; k++)
				buffer[bytesPerSample * (i * imageWidth + j) + k] = array_pixeli[bytesPerSample * (width * imageHeigth + i * width + 2 * imageWidth + j) + k];
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, bppType, imageWidth, imageHeigth, 0, bppType, GL_UNSIGNED_BYTE, buffer);		
		//1
		for (i = 0; i < imageWidth; i++)
			for (j = 0; j < imageHeigth; j++)
				for (k = 0; k < bytesPerSample; k++)
					buffer[bytesPerSample * (i * imageWidth + j) + k] = array_pixeli[bytesPerSample * (width * imageHeigth + i * width + j) + k];
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, bppType, imageWidth, imageHeigth, 0, bppType, GL_UNSIGNED_BYTE, buffer);
		//2
		for (i = 0; i < imageWidth; i++)
			for (j = 0; j < imageHeigth; j++)
				for (k = 0; k < bytesPerSample; k++)
					buffer[bytesPerSample * (i * imageWidth + j) + k] = array_pixeli[bytesPerSample * (i * width + imageWidth + j) + k];
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, bppType, imageWidth, imageHeigth, 0, bppType, GL_UNSIGNED_BYTE, buffer);
		//3
		for (i = 0; i < imageWidth; i++)
			for (j = 0; j < imageHeigth; j++)
				for (k = 0; k < bytesPerSample; k++)
					buffer[bytesPerSample * (i * imageWidth + j) + k] = array_pixeli[bytesPerSample * (2 * width * imageHeigth + i * width + imageWidth + j) + k];
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, bppType, imageWidth, imageHeigth, 0, bppType, GL_UNSIGNED_BYTE, buffer);
		//4
		for (i = 0; i < imageWidth; i++)
			for (j = 0; j < imageHeigth; j++)
				for (k = 0; k < bytesPerSample; k++)
					buffer[bytesPerSample * (i * imageWidth + j) + k] = array_pixeli[bytesPerSample * (width * imageHeigth + i * width + imageWidth + j) + k];
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, bppType, imageWidth, imageHeigth, 0, bppType, GL_UNSIGNED_BYTE, buffer);
		//5
		for (i = 0; i < imageWidth; i++)
			for (j = 0; j < imageHeigth; j++)
				for (k = 0; k < bytesPerSample; k++)
					buffer[bytesPerSample * (i * imageWidth + j) + k] = array_pixeli[bytesPerSample * (width * imageHeigth + i * width + 3 * imageWidth + j) + k];
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, bppType, imageWidth, imageHeigth, 0, bppType, GL_UNSIGNED_BYTE, buffer);
		delete[] buffer;
		glGenerateMipmap(type);
	}

	glBindTexture(type, 0);

	return lastPoint++;
}
