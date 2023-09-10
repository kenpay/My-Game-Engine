#pragma once

#include"../Utilities/utilities.h"

class Vertex 
{
public:
	Vector3 pos, col, norm, binorm, tgt;
	Vector2 uv;
	Vertex(Vector3 position, Vector3 color) : pos(position), col(color) {};
	Vertex(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _r, GLfloat _g, GLfloat _b) : pos(Vector3(_x, _y, _z)), col(Vector3(_r, _g, _b)) {};
	Vertex(Vector3 _pos, Vector3 _norm, Vector3 _binorm, Vector3 _tgt, Vector2 _uv) : pos(_pos), norm(_norm), binorm(_binorm), tgt(_tgt), uv(_uv) {
		this->col = Vector3(1.0f, 1.0f, 1.0f);
	};
	Vertex() {};
	Vertex(Vertex& vertex) : pos(vertex.pos), col(vertex.col), norm(vertex.norm), binorm(vertex.binorm), tgt(vertex.tgt), uv(vertex.uv) {}
	Vector3& getPosition() { return this->pos; }
	Vector3& getNorm() { return this->norm; }
	Vector3& getBinorm() { return this->binorm; }
	Vector3& getTangent() { return this->tgt; }
	Vector3& getColor() { return this->col; }
	Vector2& getUv() { return this->uv; }

	void setTranslation(Vector3 translation)
	{
		Matrix translationMatrix;
		translationMatrix.SetTranslation(translation);
		pos = ((Vector4)pos) * translationMatrix;
	}

	void setRotation(Vector3 rotation)
	{
		Matrix rotationMatrix, rotationMatrixX, rotationMatrixY, rotationMatrixZ;
		rotationMatrix = rotationMatrixZ.SetRotationZ(rotation.z) * rotationMatrixY.SetRotationY(rotation.y) * rotationMatrixX.SetRotationX(rotation.x);
		pos = ((Vector4)pos) * rotationMatrix;
	}

	void setScale(Vector3 scale)
	{
		Matrix scaleMatrix;
		scaleMatrix.SetScale(scale);
		pos = ((Vector4)pos) * scaleMatrix;
	}
};