#include "stdafx.h"
#include "Camera.h"

Camera::Camera(Vector3 _position, Vector3 _target, Vector3 _up, GLfloat _moveSpeed, GLfloat _rotateSpeed, GLfloat _near, GLfloat _far, GLfloat _fov) :
	target(_target), position(_position), up(_up), moveSpeed(_moveSpeed), rotationSpeed(_rotateSpeed), nearFl(_near), farFl(_far), fov(_fov), object(NULL)
{

	updateWorldView();
	perspective.SetPerspective((GLfloat)M_PI / 4, ((GLfloat)Globals::screenWidth) / Globals::screenHeight, nearFl, farFl);
}

void Camera::moveOx(GLfloat directie)
{
	Vector3 forward = Vector3(up.x, up.y, up.z).Cross(-(Vector3(target.x, target.y, target.z)-Vector3(position.x, position.y, position.z))).Normalize() * directie;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
}

void Camera::moveOy(GLfloat directie) 
{
	Vector3 forward = Vector3(up.x, up.y, up.z).Normalize() * directie;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
}

void Camera::moveOz(GLfloat directie)
{
	if (object == NULL) {
		Vector3 forward = -(Vector3(target.x, target.y, target.z) - Vector3(position.x, position.y, position.z)).Normalize() * directie;
		Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
		position += vectorDeplasare;
		target += vectorDeplasare;
	}
	else
	{
		
	}
}

void Camera::rotateOx(GLfloat direction)
{
	Matrix mRotateOX;
	mRotateOX.SetRotationX(deltaTime * rotationSpeed * direction);
	Vector4 rotatedLocalUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f) * mRotateOX;
	up = rotatedLocalUp * worldMatrix;
	up = up.Normalize();
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f), rotatedTarget = localTarget * mRotateOX; 
	target = rotatedTarget * worldMatrix;
}

void Camera::rotateOy(GLfloat direction)
{
	Matrix mRotateOY;
	mRotateOY.SetRotationY(deltaTime * rotationSpeed * direction);
	Vector4 localTarget(0.0f, 0.0f, -(target - position).Length(), 1.0f); 
	Vector4 rotatedTarget = localTarget * mRotateOY; 
	target = rotatedTarget * worldMatrix;
}
void Camera::rotateOz(GLfloat direction)
{
	Matrix mRotateOZ;
	mRotateOZ.SetRotationZ(deltaTime* rotationSpeed * direction);
	Vector4 rotatedLocalUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f) * mRotateOZ;
	up = rotatedLocalUp * worldMatrix;
	up = up.Normalize();
}



void Camera::updateWorldView()
{
	if (object != NULL)
	{
		position = object->getPosition() - Vector3(2, 2, -2);
		target = object->getPosition();
		up = (target - position).Cross(position);
	}
	Matrix R, T;
	Vector3 zAxis = (-(Vector3(target.x, target.y, target.z) - Vector3(position.x, position.y, position.z))).Normalize(), yAxis = Vector3(up.x, up.y, up.z).Normalize(), xAxis = yAxis.Cross(zAxis).Normalize();
	R.m[0][0] = xAxis.x;
	R.m[0][1] = xAxis.y;
	R.m[0][2] = xAxis.z;
	R.m[0][3] = 0;
	R.m[1][0] = yAxis.x;
	R.m[1][1] = yAxis.y;
	R.m[1][2] = yAxis.z;
	R.m[1][3] = 0;
	R.m[2][0] = zAxis.x;
	R.m[2][1] = zAxis.y;
	R.m[2][2] = zAxis.z;
	R.m[2][3] = 0;
	R.m[3][0] = 0;
	R.m[3][1] = 0;
	R.m[3][2] = 0;
	R.m[3][3] = 1;
	
	worldMatrix = R * T.SetTranslation(Vector3(position.x, position.y, position.z));

	viewMatrix = T.SetTranslation(Vector3(-position.x, -position.y, -position.z)) * R.Transpose();
}