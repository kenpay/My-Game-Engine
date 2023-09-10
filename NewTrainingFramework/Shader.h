#pragma once
#include "ShaderResource.h"
#include <exception>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
class Shader: ShaderResource
{
	GLint idProgram;
public:
	GLint a_norm, u_dimCel;
	GLint view, perspective, position, scale, rotationX, rotationY, rotationZ, translation, uvAttribute, u_texture_0, u_texture_1, u_texture_2, u_texture_3;
	GLint u_heights, u_Time, u_DispMax, v_coord, u_model, minR, maxR, f_color, u_camPos, u_ambientalCol, u_ratio, u_lightDiffCol, u_lightSpecColor, u_lightPos, u_specPower;
	Shader(char* vertexShaderPath, char* fragmentShaderPath);
	GLint getIdProgram() {
		return idProgram;
	};
	~Shader();
};

