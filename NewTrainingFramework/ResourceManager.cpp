#include "stdafx.h"
#include "rapidXML/rapidxml.hpp"
#include "ResourceManager.h"
#include <fstream>
#include <cstring>
#include <vector>

ResourceManager* ResourceManager::resourceManager = 0x00;

ResourceManager::ResourceManager()
{
	ifstream myfile("resourceManager.xml");
	vector<char> *buffer = new std::vector<char>((std::istreambuf_iterator<char>(myfile)), std::istreambuf_iterator<char>());
	buffer->push_back('\0');
	xml_document<> *doc = new xml_document<>;
	doc->parse<0>(&(*buffer)[0]);
	xml_node<char> *firstNode = doc->first_node();
	xmlParse(firstNode->first_node());
	delete buffer;
	delete doc;
}

void ResourceManager::parseTexture(xml_node<char> *node)
{
	xml_attribute<char> *firstAttribute = node->first_attribute();
	int id=  0;
	char *type = NULL, *path = NULL, *minFilter = NULL, *magFilter = NULL, *wrapS = NULL, *wrapT = NULL;
	while (firstAttribute != 0x00)
	{
		if (strcmp(firstAttribute->name(), "id") == 0)
			id = atoi(firstAttribute->value());
		else if (strcmp(firstAttribute->name(), "type") == 0)
			type = getValue(firstAttribute->value());
		firstAttribute = firstAttribute->next_attribute();
	}
	node = node->first_node();
	while (node != 0x00)
	{
		if (strcmp(node->name(), "path") == 0)
			path = getValue(node->value());
		else if (strcmp(node->name(), "min_filter") == 0)
			minFilter = getValue(node->value());
		else if (strcmp(node->name(), "mag_filter") == 0)
			magFilter = getValue(node->value());
		else if (strcmp(node->name(), "wrap_s") == 0)
			wrapS = getValue(node->value());
		else if (strcmp(node->name(), "wrap_t") == 0)
			wrapT = getValue(node->value());
		node = node->next_sibling();
	}
	textures[id] = new Texture(type, path, minFilter, magFilter, wrapS, wrapT);
}


void ResourceManager::parseModel(xml_node<char> *node)
{
	xml_attribute<char> *firstAttribute = node->first_attribute();
	int id = 0;
	char* path = NULL;
	while (firstAttribute != 0x0)
	{
		if (strcmp(firstAttribute->name(), "id") == 0)
			id = atoi(firstAttribute->value());
		firstAttribute = firstAttribute->next_attribute();
	}
	node = node->first_node();
	while (node != 0x00)
	{
		if (strcmp(node->name(), "path") == 0)
			path = getValue(node->value());
		node = node->next_sibling();
	}
	models[id] = new Model(path);
}

void ResourceManager::parseShader(xml_node<char> *node)
{
	xml_attribute<char> *firstAttribute = node->first_attribute();
	int id = 0;
	char *vertexShader = NULL, *fragmentShader = NULL;
	while (firstAttribute != 0x0)
	{
		if (strcmp(firstAttribute->name(), "id") == 0)
			id = atoi(firstAttribute->value());
		firstAttribute = firstAttribute->next_attribute();
	}
	node = node->first_node();
	while (node != 0x00)
	{
		if (strcmp(node->name(), "vs") == 0)
			vertexShader = getValue(node->value());
		else if (strcmp(node->name(), "fs") == 0)
			fragmentShader = getValue(node->value());
		node = node->next_sibling();
	}
	try {
		shaders[id] = new Shader(vertexShader, fragmentShader);
	}
	catch (exception loadingError)
	{
		printf_s("%s, id:%d", loadingError.what(), id);
	}
}

void ResourceManager::xmlParse(xml_node<char> *node)
{
	xml_node<char> *node2;
	while (node != 0x00)
	{
		node2 = node->first_node();
		while (node2 != NULL)
		{
			if (strcmp(node->name(), "textures") == 0)
				parseTexture(node2);
			else if (strcmp(node->name(), "models") == 0)
				parseModel(node2);
			else if (strcmp(node->name(), "shaders") == 0)
				parseShader(node2);
			node2 = node2->next_sibling();
		}
		node = node->next_sibling();
	}
}

