#pragma once
class ShaderResource
{
	char* vertexShader, *fragmentShader;
public:
	char* getVertexShader() { return vertexShader; };
	char* getFragmentShader() { return fragmentShader; }
	ShaderResource(char* _vertexShader, char* _fragmentShader) : vertexShader(_vertexShader), fragmentShader(_fragmentShader) {};
	~ShaderResource()
	{
		delete vertexShader;
		delete fragmentShader;
	}
};

