#ifndef __FOOD_GENERATOR_H
#define __FOOD_GENERATOR_H

#include "Food.h"
#include "SnakeFragment.h"
#include <vector>

class FoodGenerator
{
public:
	static Food generate(GLuint width, GLuint height, glm::vec2 unitSize, const std::vector<SnakeFragment>& fragments);
private:
	FoodGenerator();
};

#endif
