#include "SnakeFragment.h"

SnakeFragment::SnakeFragment() : GameObject()
{
}

SnakeFragment::SnakeFragment(glm::vec2 position, glm::vec2 size, Texture2D texture, glm::vec3 color, glm::vec2 velocity) : GameObject(
	position, size, texture, color, velocity)
{
}
