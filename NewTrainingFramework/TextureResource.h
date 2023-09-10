#pragma once
class TextureResource
{
	char *path, *minFilter, *magFilter, *wrapS, *wrapT, *type;
public:
	TextureResource(char* _type, char* _path, char* _minFilter, char* _magFilter, char* _wrapS, char* _wrapT) : type(_type), path(_path), minFilter(_minFilter), magFilter(_magFilter), wrapS(_wrapS), wrapT(_wrapT) {};
	bool isMinFilterLinear() { return strcmp(minFilter, "LINEAR") == 0; };
	bool isMagFilterLinear() { return strcmp(magFilter, "LINEAR") == 0; };
	bool isWrapSClampToEdge() { return strcmp(wrapS, "CLAMP_TO_EDGE") == 0; }
	bool isWrapTClampToEdge() { return strcmp(wrapT, "CLAMP_TO_EDGE") == 0; }
	bool isWrapSRepeat() { return strcmp(wrapS, "REPEAT") == 0; }
	bool isWrapTRepeat() { return strcmp(wrapT, "REPEAT") == 0; }
	bool is2D() { return strcmp(type, "2d") == 0; };
	char* getPath() { return path; }
	~TextureResource()
	{
		delete path;
		delete minFilter;
		delete magFilter;
		delete wrapS;
		delete wrapT;
		delete type;
	};
};

