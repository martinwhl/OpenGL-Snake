#ifndef __RESOURCE_MANAGER_H
#define __RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <glad/glad.h>
#include "Texture2D.h"
#include "Shader.h"

class ResourceManager
{
public:
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture2D> textures;
	static Shader loadShader(const GLchar* vertexShaderFilePath, const GLchar* fragmentShaderFilePath,
	                         const GLchar* geometryShaderFilePath, std::string name);
	static Shader getShader(std::string name);
	static Texture2D loadTexture(const GLchar * textureFilePath, GLboolean alpha, std::string name);
	static Texture2D getTexture(std::string name);
	static void clear();
private:
	ResourceManager();
	static Shader loadShaderFromFile(const GLchar * vertexShaderFilePath, const GLchar * fragmentShaderFilePath, 
		const GLchar * geometryShaderFilePath = nullptr);
	static Texture2D loadTextureFromFile(const GLchar * textureFilePath, GLboolean alpha);
};

#endif
