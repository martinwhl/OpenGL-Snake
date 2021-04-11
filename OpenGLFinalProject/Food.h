#ifndef __FOOD_H
#define __FOOD_H

#include "GameObject.h"

class Food : public GameObject
{
public:
	Food();
	Food(glm::vec2 position, glm::vec2 size, Texture2D texture, GLuint score, glm::vec3 color = glm::vec3(1.0f),
	           glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	void draw(SpriteRenderer & renderer);
	GLuint score;
	GLboolean isEaten;
};

#endif
