#ifndef __SNAKE_H
#define __SNAKE_H

#include "GameObject.h"
#include "SnakeFragment.h"
#include <vector>

class Food;

enum MovingDirection
{
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN
};

class Snake
{
public:
	glm::vec2 initLocation;
	glm::vec2 fragmentSize;
	MovingDirection direction;
	GLboolean isDead;
	Snake();
	Snake(glm::vec2 initLocation, glm::vec2 fragmentSize);
	std::vector<SnakeFragment> fragments;
	void setActivityRange(GLuint minX, GLuint minY, GLuint maxX, GLuint maxY);
	void move();
	void draw(SpriteRenderer & renderer);
	GLboolean eatFood(Food & food);
	GLuint minX;
	GLuint minY;
	GLuint maxX;
	GLuint maxY;
};

#endif
