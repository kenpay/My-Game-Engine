	// NewTrainingFramework.cpp : Defines the entry point for the console application.
	//

#include "stdafx.h"

#include "rapidXML/rapidxml.hpp"
#include <fstream>
#include <vector>

#include "Vertex.h"
#include "Shaders.h"

#include "Globals.h"
#include "Camera.h"
#include <iostream>
#include "Model.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "../Utilities/utilities.h"

using namespace rapidxml;

	void Draw(ESContext *esContext)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glEnable(GL_DEPTH_TEST);
		SceneManager::getInstance()->Draw(esContext);
		eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
		SceneManager::getInstance()->getActiveCamera().updateWorldView();
	}

	void Update(ESContext *esContext, float deltaTime)
	{
		SceneManager::getInstance()->Update(esContext, deltaTime);
	}

	void Key(ESContext *esContext, unsigned char key, bool bIsPressed)
	{
		Camera& myCamera = SceneManager::getInstance()->getActiveCamera();
		switch (key)
		{
			case 'W':
			{
				myCamera.moveOz(-25);
				break;
			}
			case 'S':
			{
				myCamera.moveOz(25);
				break;
			}
			case 'A':
			{
				myCamera.moveOx(-25);
				break;
			}
			case 'D':
			{
				myCamera.moveOx(25);
				break;
			}
			case 'Z':
			{
				myCamera.moveOy(25);
				break;
			}
			case 'X':
			{
				myCamera.moveOy(-25);
				break;
			}
			case 'U':
			{
				myCamera.rotateOz(5);
				break;
			}
			case 'J':
			{
				myCamera.rotateOz(-5);
				break;
			}
			case 'H':
			{
				myCamera.rotateOx(-5);
				break;
			}
			case 'L':
			{
				myCamera.rotateOx(5);
				break;
			}
			case 'N':
			{
				myCamera.rotateOy(5);
				break;
			}
			case 'M':
			{
				myCamera.rotateOy(-5);
				break;
			}
		}
	}


	//TODO: Cleanup
	void CleanUp()
	{
		//glDeleteBuffers(2, buffers);
		//glDeleteTextures(1, &textures);
	}


	int _tmain(int argc, _TCHAR* argv[])
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		ESContext esContext;

		esInitContext(&esContext);
		esCreateWindow(&esContext, "My Game Engine", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);
		ShowCursor(FALSE);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		SceneManager::getInstance()->getActiveCamera().setDeltaTime(0.0);
		int err = glGetError();
		if (err != 0)
			return 0;

		esRegisterDrawFunc(&esContext, Draw);
		esRegisterUpdateFunc(&esContext, Update);
		esRegisterKeyFunc(&esContext, Key);
		
		esMainLoop(&esContext);
		CleanUp();

		return 0;
	}

