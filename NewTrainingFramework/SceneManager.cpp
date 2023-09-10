#include "stdafx.h"
#include "rapidXML/rapidxml.hpp"
#include "SceneManager.h"
#include "ResourceManager.h"
#include <string>
#include <vector>
#include <fstream>

using namespace rapidxml;

SceneManager* SceneManager::sceneManager = NULL;

Vector3 SceneManager::getVector3(xml_node<char>* node)
{
	GLfloat x = stof(node->value()), y = stof((node = node->next_sibling())->value()), z = stof((node = node->next_sibling())->value());
	Vector3 aux(x, y, z);
	return aux;
}

/* Deprecated 
void getVector3(Vector3& vector3, xml_node<char> *node)
{
	while (node != 0x00)
	{
		if (strcmp(node->name(), "x") == 0)
			vector3.x = std::stof(node->value());
		else if (strcmp(node->name(), "y") == 0)
			vector3.y = std::stof(node->value());
		else if (strcmp(node->name(), "z") == 0)
			vector3.z = std::stof(node->value());
		node = node->next_sibling();
	}
}
*/

SceneManager::SceneManager()
{
	ifstream myfile("sceneManager.xml");
	vector<char> *buffer = new vector<char>((istreambuf_iterator<char>(myfile)), std::istreambuf_iterator<char>());
	buffer->push_back('\0');
	xml_document<> *doc = new xml_document<>();
	doc->parse<0>(&(*buffer)[0]);
	xml_node<char> *node2;
	for (xml_node<char>* node = doc->first_node()->first_node(); node != 0x00; node = node->next_sibling())
		if (strcmp(node->name(), "backgroundColor") == 0)
			backgroundColor = getVector3(node->first_node());
		else if (strcmp(node->name(), "ambientalLight") == 0)
			parseAmbietalLight(node->first_node());
		else if (strcmp(node->name(), "activeCamera") == 0)
			activeCamera = atoi(node->value());//?
		else if (strcmp(node->name(), "razaMica") == 0)
			razaMica = stof(node->value());
		else if (strcmp(node->name(), "razaMare") == 0)
			razaMare = stof(node->value());
		else if (strcmp(node->name(), "fogColor") == 0)
			fogColor = getVector3(node->first_node());
		else
			for (node2 = node->first_node(); node2 != 0x00; node2 = node2->next_sibling())
				if (strcmp(node->name(), "cameras") == 0)
				getCamera(node2);
			else if (strcmp(node->name(), "objects") == 0)
				getObject(node2);
			else if (strcmp(node->name(), "lights") == 0)
				getLight(node2);
	if (activeCamera != -1)
	{
		/*Camera& activeCamera = getActiveCamera();
		for (unordered_map<int, SceneObject*>::iterator it = objects.begin(); it != objects.end(); it++)
			if (strcmp(it->second->getType(), "character") == 0)
				activeCamera.setObject(it->second);*/
	}
	delete buffer;
	delete doc;
}


SceneManager::~SceneManager()
{
}

Trajectory SceneManager::getTrajectory(xml_node<char>* node)
{
	char* type, * iteration, * direction;
	Vector3 endPoint;
	GLfloat speed;

	xml_attribute<char>* firstAttribute = node->first_attribute();
	while (firstAttribute != 0x00)
	{
		if (strcmp(firstAttribute->name(), "type") == 0)
			type = getValue(firstAttribute->value());
		if (strcmp(firstAttribute->name(), "iteration") == 0)
			iteration = getValue(firstAttribute->value());
		if (strcmp(firstAttribute->name(), "direction") == 0)
			direction = getValue(firstAttribute->value());
		firstAttribute = firstAttribute->next_attribute();
	}
	node = node->first_node();
	while (node != 0x00)
	{
		if (strcmp(node->name(), "endPoint") == 0)
			endPoint = getVector3(node->first_node());
		else if (strcmp(node->name(), "speed") == 0)
			speed = stof(node->value());

		node = node->next_sibling();
	}
	return Trajectory(type, iteration, direction, endPoint, speed);

}

void SceneManager::parseAmbietalLight(xml_node<char>* node)
{
	ambietalLight = getVector3(node->first_node());
	ratio = stof(node->next_sibling()->value());
}

void SceneManager::getLight(xml_node<char> *node)
{
	xml_attribute<char> *firstAttribute = node->first_attribute();
	int id;
	while (firstAttribute != 0x00)
	{
		if (strcmp(firstAttribute->name(), "id") == 0)
			id = atoi(firstAttribute->value());
		firstAttribute = firstAttribute->next_attribute();
	}
	node = node->first_node();
	Vector3 diffuseColor, specularColor, position;
	char* type;
	float specPower;
	while (node != 0x00)
	{
		if (strcmp(node->name(), "position") == 0)
			position = getVector3(node->first_node());
		else if (strcmp(node->name(), "diffuseColor") == 0)
			diffuseColor = getVector3(node->first_node());
		else if (strcmp(node->name(), "specularColor") == 0)
			specularColor = getVector3(node->first_node());
		else if (strcmp(node->name(), "type") == 0)
			type = getValue(node->value());
		else if (strcmp(node->name(), "specPower") == 0)
			specPower = stof(node->value());

		node = node->next_sibling();
	}
	lights[id] = new Light(type, diffuseColor, specularColor, position, specPower);
}

void SceneManager::getObject(xml_node<char> *node)
{
	xml_attribute<char> *firstAttribute = node->first_attribute();
	int id, tempId;
	while (firstAttribute != 0x00)
	{
		if (strcmp(firstAttribute->name(), "id") == 0)
			id = atoi(firstAttribute->value());
		firstAttribute = firstAttribute->next_attribute();
	}
	GLuint nrCelule= 4;
	GLfloat offsetY=-1.0f, dimCel = 1.0f, dispMax = 0.7f;
	char *type = NULL, *name = NULL;
	bool blend = false;
	Model* model = NULL;
	Shader* shader = NULL;
	vector<Texture*> *textures = new vector<Texture*>();
	vector<int>* lights = new vector<int>();
	Vector3 position, rotation, scale, inaltimi, color;
	Trajectory *trajectory = NULL;
	node = node->first_node();
	while (node != 0x00)
	{
		if (strcmp(node->name(), "position") == 0)
			position = getVector3(node->first_node());
		else if (strcmp(node->name(), "rotation") == 0)
			rotation = getVector3(node->first_node());
		else if (strcmp(node->name(), "scale") == 0)
			scale = getVector3(node->first_node());
		else if (strcmp(node->name(), "color") == 0)
			color = getVector3(node->first_node());
		else if (strcmp(node->name(), "model") == 0)
		{
			if ((tempId = atoi(node->value())) != 0)
				model = ResourceManager::getInstance()->getModel(tempId);
		}
		else if (strcmp(node->name(), "textures") == 0)
			for (xml_node<char>* node2 = node->first_node(); node2 != 0x00; node2 = node2->next_sibling())
				textures->push_back(ResourceManager::getInstance()->getTexture(atoi(node2->first_attribute()->value())));
		else if (strcmp(node->name(), "shader") == 0)
			shader = ResourceManager::getInstance()->getShader(atoi(node->value()));
		else if (strcmp(node->name(), "type") == 0)
			type = getValue(node->value());
		else if (strcmp(node->name(), "blend") == 0)
			blend = strcmp(node->value(), "true") == 0;
		else if (strcmp(node->name(), "name") == 0)
			name = getValue(node->value());
		else if (strcmp(node->name(), "lights") == 0)
			for (xml_node<char>* node2 = node->first_node(); node2 != 0x00; node2 = node2->next_sibling())
				lights->push_back(atoi(node2->value()));
		else if (strcmp(node->name(), "dimCel") == 0)
			dimCel = stof(node->value());
		else if (strcmp(node->name(), "nrCelule") == 0)
			nrCelule = atoi(node->value());
		else if (strcmp(node->name(), "offsetY") == 0)
			offsetY = stof(node->value());
		else if (strcmp(node->name(), "inaltimi") == 0)
			inaltimi = getVector3(node->first_node());
		else if (strcmp(node->name(), "dispMax") == 0)
			dispMax = stof(node->value());
		else if (strcmp(node->name(), "trajectory") == 0)
			trajectory = new Trajectory(getTrajectory(node));

		node = node->next_sibling();
	}
	if (strcmp("terrain", type) == 0)
	{
		GLint width, height, bpp;
		unsigned char* pixels = (unsigned char*) LoadTGA(textures->operator[](3)->getPath(), &width, &height, &bpp);
		GLfloat* offsetYMap = new GLfloat[width * height];
		for (int i = 0, j; i < width * height; i++)
		{
			offsetYMap[i] = 0.0f;
			offsetYMap[i] = GLfloat(pixels[0]) / 100.0f * 10.0f / 3.0f + GLfloat(pixels[1])/ 100.0f * 50.0f / 3.0f  + GLfloat(pixels[2]) /100.0f * (- 20.0f) / 3.0f;
			pixels += 3;
		}

		GLuint nrVertices = (width+1) * (height+1), nrIndexes = 6 * width * height;
		Vertex* vertices = new Vertex[nrVertices];
		Vector2 * uv = new Vector2[nrVertices];
		GLushort *indices = new GLushort[nrIndexes];
		GLuint i, j;
		for (i = 0; i < width; i++)
			for (j = 0; j < height; j++)
			{
				indices[6 * (i * width + j)] = i * (width + 1) + j;
				indices[6 * (i * width + j) + 1] = (i + 1) * (width + 1) + j;
				indices[6 * (i * width + j) + 2] = i * (width + 1) + j + 1;


				indices[6 * (i * width + j) + 3] = (i + 1) * (width + 1) + j;
				indices[6 * (i * width + j) + 4] = i * (width + 1) + j + 1;
				indices[6 * (i * width + j) + 5] = (i + 1) * (width + 1) + j + 1;
			}
		for (i = 0; i <= width; i++)
			for (j = 0; j <= height; j++)
				vertices[i * (width + 1) + j] = Vertex(Vector3(float(dimCel) * (-int(width) / 2 + int(i)), offsetYMap[int(float(i)-0.5f)*width+int((float(j)-0.5f))], float(dimCel) * (-int(height) / 2 + int(j))), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(GLfloat(i) / width, GLfloat(j) / height));
		objects[id] = new TerrainObject(type, name, blend, color, position, rotation, scale, trajectory, new Model(nrVertices, nrIndexes, vertices, indices), shader, textures, lights, nrCelule, dimCel, offsetY, inaltimi);
	}
		
	else if (strcmp("fire", type) == 0)
		objects[id] = new FireObject(type, name, blend, color, position, rotation, scale, trajectory, model, shader, textures, lights, dispMax);
	else
		objects[id] = new SceneObject(type, name, blend, color, position, rotation, scale, trajectory, model, shader, textures, lights);
}

void SceneManager::getCamera(xml_node<char> *node)
{
	xml_attribute<char> *firstAttribute = node->first_attribute();
	int id;
	while (firstAttribute != 0x00)
	{
		if (strcmp(firstAttribute->name(), "id") == 0)
			id = atoi(firstAttribute->value());
		firstAttribute = firstAttribute->next_attribute();
	}
	node = node->first_node();
	Vector3 position, target, up; 
	GLfloat translationSpeed = 0.0f, rotation = 0.0f, fov = 0.0f, nearFl = 0.0f, farFl = 0.0f;
	while (node != 0x00)
	{
		if (strcmp(node->name(), "position") == 0)
			position = getVector3(node->first_node());
		else if (strcmp(node->name(), "target") == 0)
			target = getVector3(node->first_node());
		else if (strcmp(node->name(), "up") == 0)
			up = getVector3(node->first_node());
		else if (strcmp(node->name(), "translationSpeed") == 0)
			translationSpeed = stof(node->value());
		else if (strcmp(node->name(), "rotationSpeed") == 0)
			rotation = stof(node->value());
		else if (strcmp(node->name(), "fov") == 0)
			fov = stof(node->value());
		else if (strcmp(node->name(), "near") == 0)
			nearFl = stof(node->value());
		else if (strcmp(node->name(), "far") == 0)
			farFl = stof(node->value());
		node = node->next_sibling();
	}
	cameras[id] = new Camera(position, target, up, translationSpeed, rotation, nearFl, farFl, fov);
}

/*
void SceneManager::getBackgroundColor(xml_node<char> *&node)
{
	backgroundColor = getVector3(node);
}
*/

SceneManager* SceneManager::getInstance()
{
	if (sceneManager == NULL)
		sceneManager = new SceneManager();
	return sceneManager;
};


void SceneManager::Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (unordered_map<int, SceneObject*>::iterator it = objects.begin(); it != objects.end(); it++)
		it->second->Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SceneManager::Update(ESContext* esContext, float deltaTime)
{
	static float staticDeltaTime = 0.0f;
	staticDeltaTime += deltaTime;
	if (staticDeltaTime > 0.001)
	{
		SceneManager::getInstance()->getActiveCamera().setDeltaTime(0.001);
		staticDeltaTime = 0.0f;
	}

	for (unordered_map<int, SceneObject*>::iterator it = objects.begin(); it != objects.end(); it++)
		it->second->Update();
}

bool SceneManager::checkCollision(SceneObject* object)
{
	for (unordered_map<int, SceneObject*>::iterator it = objects.begin(); it != objects.end(); it++)
		if (object != it->second)
			if (object->checkCollision(it->second))
				return true;
	return false;
}
