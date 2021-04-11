#ifndef __TEXT_RENDERER_H
#define __TEXT_RENDERER_H

#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Texture2D.h"
#include "Shader.h"

class Character
{
public:
	GLuint textureID;
	glm::ivec2 size;
	glm::ivec2 bearing;
	GLuint advance;
};

class TextRenderer
{
public:
	std::map<GLchar, Character> characters;
	Shader textShader;
	TextRenderer(GLuint width, GLuint height);
	void load(std::string font, GLuint fontSize);
	void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));
private:
	GLuint VAO;
	GLuint VBO;
};

#endif