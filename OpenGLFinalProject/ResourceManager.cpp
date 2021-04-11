#include "ResourceManager.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stb_image.h>

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture2D> ResourceManager::textures;

Shader ResourceManager::loadShader(const GLchar* vertexShaderFilePath, const GLchar* fragmentShaderFilePath,
                                   const GLchar* geometryShaderFilePath, std::string name)
{
	shaders[name] = loadShaderFromFile(vertexShaderFilePath, fragmentShaderFilePath, geometryShaderFilePath);
	return shaders[name];
}

Shader ResourceManager::getShader(std::string name)
{
	return shaders[name];
}

Texture2D ResourceManager::loadTexture(const GLchar* textureFilePath, GLboolean alpha, std::string name)
{
	textures[name] = loadTextureFromFile(textureFilePath, alpha);
	return textures[name];
}

Texture2D ResourceManager::getTexture(std::string name)
{
	return textures[name];
}

void ResourceManager::clear()
{
	for (std::map<std::string, Shader>::iterator iter = shaders.begin(); iter != shaders.end(); ++iter)
	{
		glDeleteProgram(iter->second.ID);
	}
	for (std::map<std::string, Texture2D>::iterator iter = textures.begin(); iter != textures.end(); ++iter)
	{
		glDeleteTextures(1, &iter->second.ID);
	}
}

Shader ResourceManager::loadShaderFromFile(const GLchar* vertexShaderFilePath, const GLchar* fragmentShaderFilePath,
                                           const GLchar* geometryShaderFilePath)
{
	std::string vertexShaderCode, fragmentShaderCode, geometryShaderCode;
	try
	{
		std::ifstream vertexShaderFile(vertexShaderFilePath);
		std::ifstream fragmentShaderFile(fragmentShaderFilePath);
		std::stringstream vertexShaderStream;
		std::stringstream fragmentShaderStream;
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();
		vertexShaderFile.close();
		fragmentShaderFile.close();
		vertexShaderCode = vertexShaderStream.str();
		fragmentShaderCode = fragmentShaderStream.str();
		if (geometryShaderFilePath != nullptr)
		{
			std::ifstream geometryShaderFile(geometryShaderFilePath);
			std::stringstream geometryShaderStream;
			geometryShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryShaderCode = geometryShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files." << std::endl;
	}
	const GLchar * vertexShaderCodeChars = vertexShaderCode.c_str();
	const GLchar * fragmentShaderCodeChars = fragmentShaderCode.c_str();
	const GLchar * geometryShaderCodeChars = geometryShaderCode.c_str();
	Shader shader;
	shader.compile(vertexShaderCodeChars, fragmentShaderCodeChars, geometryShaderFilePath != nullptr ? geometryShaderCodeChars :	nullptr);
	return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar* textureFilePath, GLboolean alpha)
{
	Texture2D texture;
	if (alpha)
	{
		texture.internalFormat = GL_RGBA;
		texture.imageFormat = GL_RGBA;
	}
	GLint width, height, channels;
	// stbi_set_flip_vertically_on_load(true);
	GLubyte * image = stbi_load(textureFilePath, &width, &height, &channels, STBI_rgb_alpha);
	if (!image)
	{
		std::cout << "ERROR::TEXTURE: Cannot load texture image." << std::endl;
		std::cout << stbi_failure_reason() << std::endl;
		return texture;
	}
	texture.generate(width, height, image);
	stbi_image_free(image);
	return texture;
}

