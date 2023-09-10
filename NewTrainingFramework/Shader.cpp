#include "stdafx.h"
#include "Shader.h"

Shader::Shader(char* vertexShaderPath, char* fragmentShaderPath) : ShaderResource(vertexShaderPath, fragmentShaderPath)
{
	int vertexShader = esLoadShader(GL_VERTEX_SHADER, getVertexShader());
	if (vertexShader == 0)
		throw(exception("No vertex shader"));
	int fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, getFragmentShader());

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		throw(exception("No fragment shader"));
	}

	idProgram = esLoadProgram(vertexShader, fragmentShader);

	position = glGetAttribLocation(idProgram, "position");
	view = glGetUniformLocation(idProgram, "view");
	perspective = glGetUniformLocation(idProgram, "perspective");
	scale = glGetUniformLocation(idProgram, "scale");
	rotationX = glGetUniformLocation(idProgram, "rotationX");
	rotationY = glGetUniformLocation(idProgram, "rotationY");
	rotationZ = glGetUniformLocation(idProgram, "rotationZ");
	translation = glGetUniformLocation(idProgram, "translation");
	a_norm = glGetAttribLocation(idProgram, "a_norm");
	uvAttribute = glGetAttribLocation(idProgram, "a_uv");
	u_heights = glGetUniformLocation(idProgram, "u_height");
	u_dimCel = glGetUniformLocation(idProgram, "u_dimCel");
	u_Time = glGetUniformLocation(idProgram, "u_Time");
	u_DispMax = glGetUniformLocation(idProgram, "u_DispMax");
	v_coord = glGetUniformLocation(idProgram, "v_coord");
	u_model = glGetUniformLocation(idProgram, "u_model");
	minR = glGetUniformLocation(idProgram, "minR");
	maxR = glGetUniformLocation(idProgram, "maxR");
	f_color = glGetUniformLocation(idProgram, "f_color");
	u_camPos = glGetUniformLocation(idProgram, "u_camPos");
	u_ambientalCol = glGetUniformLocation(idProgram, "u_ambientalCol");
	u_ratio = glGetUniformLocation(idProgram, "u_ratio");
	u_lightDiffCol = glGetUniformLocation(idProgram, "u_lightDiffCol");
	u_lightSpecColor = glGetUniformLocation(idProgram, "u_lightSpecColor");
	u_lightPos = glGetUniformLocation(idProgram, "u_lightPos");
	u_specPower = glGetUniformLocation(idProgram, "u_specPower");
	u_texture_0 = glGetUniformLocation(idProgram, "u_texture_0");
	u_texture_1 = glGetUniformLocation(idProgram, "u_texture_1");
	u_texture_2 = glGetUniformLocation(idProgram, "u_texture_2");
	u_texture_3 = glGetUniformLocation(idProgram, "u_texture_3");
};

Shader::~Shader()
{
}