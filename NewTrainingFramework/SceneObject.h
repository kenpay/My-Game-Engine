#pragma once
#include "ResourceManager.h"
#include <vector>

typedef struct Light
{
	char* type;
	GLfloat specPower;
	Vector3 diffuseColor, specularColor, position;
	Light(char* _type, Vector3 _diffuseColor, Vector3 _specularColor, Vector3 _position, GLfloat _specPower)
		: type(_type), diffuseColor(_diffuseColor), specularColor(_specularColor), position(_position), specPower(_specPower)
	{

	};
	~Light() {};
}Light;

typedef struct Trajectory
{
	char* type, * iteration, * direction;
	Vector3 endPoint, startPoint;
	GLfloat speed;
	Trajectory(char* _type, char* _iteration, char* _direction, Vector3 _endpoint, GLfloat _speed) : type(_type), iteration(_iteration), direction(_direction), endPoint(_endpoint), speed(_speed)
	{
	}
}Trajectory;


class SceneObject
{
protected:
	Model* model;
	Shader* shader;
	vector<Texture*>* textures;
	vector<int>* lights;
	Vector3 position, rotation, scale, color, minC, maxC;
	Trajectory* trajectory;
	char *type, *name;
	bool blend;
	GLuint modelBufferId, **textureBufferId;
	Matrix modelMatrix;
	void Move();
	Matrix getModelMatrix()
	{
		Matrix scaleMatrix, rotationX, rotationY, rotationZ, translationM;
		return scaleMatrix.SetScale(scale)* rotationZ.SetRotationZ(rotation.z)* rotationY.SetRotationY(rotation.y)* rotationX.SetRotationX(rotation.x)* translationM.SetTranslation(position);
	}
public:
	char* getType() { return type; };
	Vector3& getPosition() { return position; };
	bool checkCollision(SceneObject*);
	SceneObject(char* _type, char* _name, bool _blend, Vector3& _color, Vector3& _position, Vector3& _rotation, Vector3& _scale, Trajectory* _trajectory, Model* _model, Shader* _shader, vector<Texture*>* _textures, vector<int>* _lights)
		   : type(_type), name(_name), blend(_blend), color(_color), position(_position), rotation(_rotation), scale(_scale), trajectory(_trajectory), model(_model), shader(_shader), textures(_textures), lights(_lights), textureBufferId(new GLuint*[textures->size() + 1]), modelBufferId(model->generateBuffer())
	{
		minC = model->getMin() + position;
		maxC = model->getMax() + position;
		if (trajectory != NULL)
			trajectory->startPoint = _position;
		GLuint idx;
		for (idx = 0; idx < textures->size(); idx++)
			textureBufferId[idx] = new GLuint(textures->operator[](idx)->generateBuffer());
		textureBufferId[idx] = NULL;
	}
	virtual void Draw();
	virtual void Update();
	~SceneObject();
};

class TerrainObject : public SceneObject
{
	GLuint nrCelule;
	GLfloat offsetY, dimCel;
	Vector3 heights;
public:
	TerrainObject(char* _type, char* _name, bool _blend, Vector3& _color, Vector3& _position, Vector3& _rotation, Vector3& _scale, Trajectory* _trajectory, Model* _model, Shader* _shader, vector<Texture*>* _textures, vector<int>* _lights, GLuint _nrCelule, GLfloat _dimCel, GLfloat offsetY, Vector3& _heights) :
		SceneObject(_type, _name, _blend, _color, _position, _rotation, _scale, _trajectory, _model, _shader, _textures, _lights), nrCelule(_nrCelule), dimCel(_dimCel), offsetY(offsetY), heights(_heights)
	{
	};
	void Draw();
};



class FireObject : public SceneObject
{
	GLfloat u_DispMax, u_Time;
public:
	FireObject(char* _type, char* _name, bool _blend, Vector3 _color, Vector3 _position, Vector3 _rotation, Vector3 _scale, Trajectory* _trajectory, Model* _model, Shader* _shader, vector<Texture*>* _textures, vector<int>* _lights, GLfloat _u_DispMax) :
		SceneObject(_type, _name, _blend, _color, _position, _rotation, _scale, _trajectory, _model, _shader, _textures, _lights), u_DispMax(_u_DispMax)
	{
		u_Time = float(clock());

	}
	void Update();
	void Draw();
	~FireObject()
	{ 

	}
};
