#ifndef __GAME_OBJECT_H
#define __GAME_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Texture2D.h"
#include "SpriteRenderer.h"

class GameObject
{
public:
	glm::vec2 position;
	glm::vec2 size;
	glm::vec2 velocity;
	glm::vec3 color;
	GLfloat rotation;
	Texture2D texture;
	GameObject();
	GameObject(glm::vec2 position, glm::vec2 size, Texture2D texture, glm::vec3 color = glm::vec3(1.0f),
	           glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	virtual void draw(SpriteRenderer & renderer);
};

#endif
