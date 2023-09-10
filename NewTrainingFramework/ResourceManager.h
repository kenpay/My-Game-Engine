#pragma once
#include <unordered_map>
#include "Texture.h"
#include "rapidXML/rapidxml.hpp"
#include "Model.h"
#include "Shader.h"
using namespace rapidxml;
class ResourceManager
{
	static ResourceManager* resourceManager;
	unordered_map<int, Texture*> textures;
	unordered_map<int, Shader*> shaders;
	unordered_map<int, Model*> models;
	ResourceManager();
public:
	void parseTexture(xml_node<char> *);
	void parseShader(xml_node<char> *);
	void parseModel(xml_node<char> *);
	void xmlParse(xml_node<char> *);
	Model* getModel(int i)
	{
		return models[i];
	}
	Texture* getTexture(int i)
	{
		return textures[i];
	}
	Shader* getShader(int i)
	{
		return shaders[i];
	}
	static ResourceManager* getInstance()
	{
		if (resourceManager == 0x00)
			resourceManager = new ResourceManager();
		return resourceManager;
	}
	~ResourceManager() {};
};

