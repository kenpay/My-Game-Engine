#include "stdafx.h"
#include "SceneObject.h"
#include "SceneManager.h"

void SceneObject::Draw()
{
	glUseProgram(shader->getIdProgram());
	glEnable(GL_DEPTH_TEST);
	glBindBuffer(GL_ARRAY_BUFFER, model->getVBOId(modelBufferId));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getIBOId(modelBufferId));
	for (GLuint index = 0; textureBufferId[index] != NULL; index++)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		GLuint type = GL_TEXTURE_2D;
		Texture * texture = textures->operator[](index);
		if (!texture->is2D())
			type = GL_TEXTURE_CUBE_MAP;
		glBindTexture(type, texture->getId(*textureBufferId[index]));
		if (blend)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		switch (index)
		{
		case 0:
			if (shader->u_texture_0 != -1)
			{
				//glActiveTexture(GL_TEXTURE0);
				glUniform1i(shader->u_texture_0, index);
			}
			break;
		case 1:
			if (shader->u_texture_1 != -1)
			{
				//glActiveTexture(GL_TEXTURE1);
				glUniform1i(shader->u_texture_1, index);
			}
			break;
		case 2:
			if (shader->u_texture_2 != -1)
			{
				//glActiveTexture(GL_TEXTURE2);
				glUniform1i(shader->u_texture_2, index);
			}
			break;
		case 3:
			if (shader->u_texture_3 != -1)
			{
				//glActiveTexture(GL_TEXTURE3);
				glUniform1i(shader->u_texture_3, index);
			}
			break;
		default:
			break;
		}
	}
	SceneManager* sceneManager = SceneManager::getInstance();
	Camera& activeCamera = sceneManager->getActiveCamera();
	Matrix mvp;
	if (shader->uvAttribute != -1)
	{
		glEnableVertexAttribArray(shader->uvAttribute);
		glVertexAttribPointer(shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(Vector3)));
	}
	if (shader->position != -1)
	{
		glEnableVertexAttribArray(shader->position);
		glVertexAttribPointer(shader->position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (shader->view != -1)
	{
		glUniformMatrix4fv(shader->view, 1, GL_FALSE, &(mvp = activeCamera.getView()).m[0][0]);
	}
	if (shader->perspective != -1)
	{
		glUniformMatrix4fv(shader->perspective, 1, GL_FALSE, &(mvp = activeCamera.getPerspective()).m[0][0]);
	}
	if (shader->scale != -1)
	{
		glUniformMatrix4fv(shader->scale, 1, GL_FALSE, &((mvp.SetScale(scale)).m[0][0]));
	}
	if (shader->rotationX != -1)
	{
		glUniformMatrix4fv(shader->rotationX, 1, GL_FALSE, &((mvp.SetRotationX(rotation.x)).m[0][0]));
	}
	if (shader->rotationY != -1)
	{
		glUniformMatrix4fv(shader->rotationY, 1, GL_FALSE, &((mvp.SetRotationY(rotation.y)).m[0][0]));
	}
	if (shader->rotationZ != -1)
	{
		glUniformMatrix4fv(shader->rotationZ, 1, GL_FALSE, &((mvp.SetRotationZ(rotation.z)).m[0][0]));
	}
	if (shader->translation != -1)
	{
		glUniformMatrix4fv(shader->translation, 1, GL_FALSE, &((mvp.SetTranslation(position)).m[0][0]));
	}
	if (shader->a_norm != -1)
	{
		glEnableVertexAttribArray(shader->a_norm);
		glVertexAttribPointer(shader->a_norm, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(2 * sizeof(Vector3)));
	}
	if (shader->u_model != -1)
	{
		glUniformMatrix4fv(shader->u_model, 1, GL_FALSE, &modelMatrix.m[0][0]);
	}
	if (shader->minR != -1)
	{
		glUniform1f(shader->minR, sceneManager->razaMica);
	}
	if (shader->maxR != -1)
	{
		glUniform1f(shader->maxR, sceneManager->razaMare);
	}
	if (shader->f_color != -1)
	{
		glUniform3fv(shader->f_color, 1, (GLfloat*)& sceneManager->fogColor);
	}
	if (shader->u_camPos != -1)
	{
		glUniform3fv(shader->u_camPos, 1, (GLfloat*)& activeCamera.getPosition());
	}
	if (shader->u_ambientalCol != -1)
	{
		glUniform3fv(shader->u_ambientalCol, 1, (GLfloat*)& sceneManager->ambietalLight);
	}
	if (shader->u_ratio != -1)
	{
		glUniform1f(shader->u_ratio, sceneManager->ratio);
	}
	Light light = *sceneManager->lights.at(1);
	if (shader->u_lightDiffCol != -1)
	{
		glUniform3fv(shader->u_lightDiffCol, 1, (GLfloat*)& light.diffuseColor);
	}
	if (shader->u_lightSpecColor != -1)
	{
		glUniform3fv(shader->u_lightSpecColor, 1, (GLfloat*)& light.specularColor);
	}
	if (shader->u_lightPos != -1)
	{
		glUniform3fv(shader->u_lightPos, 1, (GLfloat*)& light.position);
	}
	if (shader->u_specPower != -1)
	{
		glUniform1f(shader->u_specPower, light.specPower);
	}
	glDrawElements(GL_TRIANGLES, model->getNrIndexes(), GL_UNSIGNED_SHORT, 0);
}

void SceneObject::Update()
{
	if (trajectory != NULL)
		Move();
}

SceneObject::~SceneObject()
{
}

void TerrainObject::Draw()
{
	SceneObject::Draw();
		if (shader->u_heights != -1)
		{
			glUniform3fv(shader->u_heights, 1,(GLfloat*) &heights);
		}
		if (shader->u_dimCel != -1)
		{
			glUniform1f(shader->u_dimCel, dimCel);
		}
}

void FireObject::Update()
{
	u_Time += SceneManager::getInstance()->getActiveCamera().getDeltaTime();
	if (u_Time > 0.1)
	{
		double d;
		u_Time = float(modf(double(u_Time), &d));
	}
}

void FireObject::Draw()
{
	SceneObject::Draw();
		if (shader->u_Time != -1)
		{
			glUniform1f(shader->u_Time, u_Time);
		}
		if (shader->u_DispMax != -1)
		{
			glUniform1f(shader->u_DispMax, u_DispMax);
		}
}


void SceneObject::Move()
{
	bool shouldExecute = true;
	static int iterationsDone = 0;
	if (strcmp(trajectory->iteration, "infinite") != 0)
		if (iterationsDone++ > stof(trajectory->iteration))
			shouldExecute = false;
	if (shouldExecute)
	{
		SceneManager* sceneManager = SceneManager::getInstance();
		GLfloat deltaTime = sceneManager->getActiveCamera().getDeltaTime();
		Vector3 forword = (trajectory->endPoint - position).Normalize();
		if ((trajectory->endPoint - position).Length() < 0.01f)
			if (strcmp(trajectory->direction, "alternate") == 0)
			{
				Vector3 aux = trajectory->startPoint;
				trajectory->startPoint = trajectory->endPoint;
				trajectory->endPoint = aux;
				forword = -forword;
			}
			else
				position = trajectory->startPoint;
		Vector3 deplasare = forword * trajectory->speed * deltaTime;
		if (!sceneManager->checkCollision(this))
		{
			position += deplasare;
			minC += deplasare;
			maxC += deplasare;
		}
	}

}

bool SceneObject::checkCollision(SceneObject* object)
{
	if ((minC.x >= object->minC.x && minC.x <= object->maxC.x) || (maxC.x >= object->minC.x && maxC.x <= object->maxC.x))
		if ((minC.y >= object->minC.y && minC.y <= object->maxC.y) || (maxC.y >= object->minC.y && maxC.y <= object->maxC.y))
			if ((minC.z >= object->minC.z && minC.z <= object->maxC.z) || (maxC.z >= object->minC.z && maxC.z <= object->maxC.z))
			{
				object->position += (object->position - position);
				object->minC += (object->position - position);
				object->maxC += (object->position - position);
				return true;
			}
	return false;
}