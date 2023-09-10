#pragma once
class ModelResource
{
	char* path;
public:
	ModelResource(char _path[]) : path(_path) {};
	char* getPath() { return path; };
	~ModelResource() { delete path; };
};

