// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <ctime>

using namespace std;

char* getValue(char value[]);
//arrayToCopy must be in heap
//Returned value will have capacity = length ( copy is done < length ) -- Maybe raname ? i.e. : expandArray ?
unsigned int* arrayCopy(unsigned int* arrayToCopy, unsigned int length);

// TODO: reference additional headers your program requires here
