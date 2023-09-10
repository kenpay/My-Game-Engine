#pragma once
#include <string>
#include "Camera.h"
#include "SceneObject.h"

using namespace rapidxml;
using namespace std;

class SceneManager
{
	static SceneManager* sceneManager;
	Vector3 backgroundColor;
	unordered_map<int, Camera*> cameras;
	unordered_map<int, SceneObject*> objects;
	GLint activeCamera;
	SceneManager();
	void getCamera(xml_node<char>*);
	void getObject(xml_node<char>*);
	void parseAmbietalLight(xml_node<char>*);
	void getLight(xml_node<char>*);
	Trajectory getTrajectory(xml_node<char>* node);
	Vector3 getVector3(xml_node<char>*);
public:
	unordered_map<int, Light*> lights;
	GLfloat razaMica, razaMare;
	Vector3 fogColor;
	GLfloat ratio;
	Vector3 ambietalLight;
	static SceneManager* getInstance();
	void Draw(ESContext* esContext);
	void Update(ESContext*, float);
	bool checkCollision(SceneObject*);
	Camera& getActiveCamera() { return *cameras[activeCamera]; }
	~SceneManager();
};
