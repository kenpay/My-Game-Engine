#pragma once
#include "Globals.h"
#include "SceneObject.h"
#define _USE_MATH_DEFINES
#include <math.h>
class Camera {
	SceneObject* object;
	Vector3 position, target, up;// , xAxis, yAxis, zAxis;
	GLfloat moveSpeed, rotationSpeed, nearFl, farFl, fov, deltaTime;
	Matrix viewMatrix, worldMatrix, perspective;
public:
	Matrix getView() { return viewMatrix; };
	Matrix getPerspective() { return perspective; };
	Camera(Vector3, Vector3, Vector3, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	//Vector4 position, target, up;// xAxis, yAxis, zAxis;
	/*Camera(GLfloat _moveSpeed, GLfloat _rotateSpeed, GLfloat _near, GLfloat _far) : moveSpeed(_moveSpeed), rotationSpeed(_rotateSpeed), nearFl(_near), farFl(_far)	{
		target = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		position = Vector4(0.0f, 0.0f, -1.0f, 1.0f);
		up = Vector4(0.0, 1.0, 0.0, 0.0f);
		viewMatrix.SetIdentity();
		worldMatrix.SetIdentity();
		perspective.SetPerspective((GLfloat)M_PI / 4, ((GLfloat) Globals::screenWidth)/Globals::screenHeight, nearFl, farFl);
		updateWorldView();
	};*/
	void setDeltaTime(GLfloat dt) {
		this->deltaTime = dt * 10;
	};
	GLfloat getDeltaTime()
	{
		return deltaTime;
	}
	void setObject(SceneObject* _object) { object = _object; }
	void moveOx(GLfloat);
	void moveOy(GLfloat);
	void moveOz(GLfloat);
	void rotateOx(GLfloat);
	void rotateOy(GLfloat);
	void rotateOz(GLfloat);
	void updateWorldView();
	Vector3& getPosition()
	{
		return position;
	}
};
