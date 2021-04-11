#ifndef __SNAKE_FRAGMENT_H
#define __SNAKE_FRAGMENT_H

#include "GameObject.h"

class SnakeFragment : public GameObject
{
public:
	SnakeFragment();
	SnakeFragment(glm::vec2 position, glm::vec2 size, Texture2D texture, glm::vec3 color = glm::vec3(1.0f),
	           glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
};

#endif
