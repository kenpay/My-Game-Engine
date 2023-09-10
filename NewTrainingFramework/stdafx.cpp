// stdafx.cpp : source file that includes just the standard includes
// NewTrainingFramework.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

char* getValue(char value[])
{
	int length = strlen(value);
	char* returnValue = new char[length+1];
	for (; length >= 0; length--)
		returnValue[length] = value[length];
	return returnValue;
}

//arrayToCopy must be in heap
//Returned value will have capacity = length ( copy is done < length ) -- Maybe raname ? i.e. : expandArray ?
unsigned int* arrayCopy(unsigned int* arrayToCopy, unsigned int length)
{
	unsigned int* returnValue = new unsigned int[length + 1];
	for (unsigned int i = 0; i < length; i++)
		returnValue[i] = arrayToCopy[i];
	delete arrayToCopy;
	return returnValue;

}

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
