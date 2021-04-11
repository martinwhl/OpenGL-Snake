#include "Snake.h"
#include "ResourceManager.h"
#include "Food.h"

Snake::Snake()
{
	direction = DIRECTION_RIGHT;
	isDead = GL_FALSE;
	initLocation = glm::vec2(160, 160);
	fragmentSize = glm::vec2(32, 32);
	fragments.push_back(SnakeFragment(initLocation, fragmentSize, ResourceManager::getTexture("snake-head-right")));
	fragments.push_back(SnakeFragment(initLocation - glm::vec2(2 * fragmentSize.x, 0), fragmentSize,
	                                  ResourceManager::getTexture("snake-tail-right")));
	std::vector<SnakeFragment>::const_iterator iter = fragments.end() - 1;
	fragments.insert(iter, SnakeFragment(initLocation - glm::vec2(fragmentSize.x, 0), fragmentSize,
	                                     ResourceManager::getTexture("snake-body-right")));
	// To change the texture of a fragment
	// fragments[1].texture = ResourceManager::getTexture("apple-5");
}

Snake::Snake(glm::vec2 initLocation, glm::vec2 fragmentSize)
{
	direction = DIRECTION_RIGHT;
	isDead = GL_FALSE;
	this->initLocation = initLocation;
	this->fragmentSize = fragmentSize;
}

void Snake::move()
{
	// new position after moving
	GLuint i = fragments.size() - 1;
	if (fragments[fragments.size() - 1].position.x == fragments[fragments.size() - 2].position.x && 
		fragments[fragments.size() - 1].position.y == fragments[fragments.size() - 2].position.y)
	{
		i--;
	}
	while (i > 0)
	{
		fragments[i].position = fragments[i - 1].position;
		i--;
	}
	// change the direction and the texture of snake head
	switch (direction)
	{
	case DIRECTION_LEFT:
		fragments[0].position -= glm::vec2(fragmentSize.x, 0);
		fragments[0].texture = ResourceManager::getTexture("snake-head-left");
		break;
	case DIRECTION_RIGHT:
		fragments[0].position += glm::vec2(fragmentSize.x, 0);
		fragments[0].texture = ResourceManager::getTexture("snake-head-right");
		break;
	case DIRECTION_UP:
		fragments[0].position -= glm::vec2(0, fragmentSize.y);
		fragments[0].texture = ResourceManager::getTexture("snake-head-up");
		break;
	case DIRECTION_DOWN:
		fragments[0].position += glm::vec2(0, fragmentSize.y);
		fragments[0].texture = ResourceManager::getTexture("snake-head-down");
		break;
	}
	// determines the texture of the snake using for-loop
	for (GLuint i = 1; i < fragments.size() - 1; i++)
	{
		if (fragments[i].position.x == fragments[i - 1].position.x)
		{
			if (fragments[i].position.x == fragments[i + 1].position.x)
			{
				if (fragments[i].position.y > fragments[i - 1].position.y)
				{
					fragments[i].texture = ResourceManager::getTexture("snake-body-up");
				}
				else if (fragments[i].position.y < fragments[i - 1].position.y)
				{
					fragments[i].texture = ResourceManager::getTexture("snake-body-down");
				}
			}
			else if (fragments[i].position.x < fragments[i + 1].position.x)
			{
				if (fragments[i].position.y > fragments[i - 1].position.y)
				{
					fragments[i].texture = ResourceManager::getTexture("snake-turn-right-up");
				}
				else if (fragments[i].position.y < fragments[i - 1].position.y)
				{
					fragments[i].texture = ResourceManager::getTexture("snake-turn-right-down");
				}
			}
			else if (fragments[i].position.x > fragments[i + 1].position.x)
			{
				if (fragments[i].position.y > fragments[i - 1].position.y)
				{
					fragments[i].texture = ResourceManager::getTexture("snake-turn-left-up");
				}
				else if (fragments[i].position.y < fragments[i - 1].position.y)
				{
					fragments[i].texture = ResourceManager::getTexture("snake-turn-left-down");
				}
			}
		}
		else if (fragments[i].position.x < fragments[i - 1].position.x)
		{
			if (fragments[i].position.x == fragments[i + 1].position.x)
			{
				if (fragments[i].position.y > fragments[i + 1].position.y)
				{
					fragments[i].texture = ResourceManager::getTexture("snake-turn-right-up");
				}
				else if (fragments[i].position.y < fragments[i + 1].position.y)
				{
					fragments[i].texture = ResourceManager::getTexture("snake-turn-right-down");
				}
			}
			else if (fragments[i].position.x > fragments[i + 1].position.x)
			{
				fragments[i].texture = ResourceManager::getTexture("snake-body-right");
			}
		}
		else if (fragments[i].position.x > fragments[i - 1].position.x)
		{
			if (fragments[i].position.x == fragments[i + 1].position.x)
			{
				if (fragments[i].position.y > fragments[i + 1].position.y)
				{
					fragments[i].texture = ResourceManager::getTexture("snake-turn-left-up");
				}
				else if (fragments[i].position.y < fragments[i + 1].position.y)
				{
					fragments[i].texture = ResourceManager::getTexture("snake-turn-left-down");
				}
			}
			else if (fragments[i].position.x < fragments[i + 1].position.x)
			{
				fragments[i].texture = ResourceManager::getTexture("snake-body-left");
			}
		}
	}
	// tail
	if (fragments[fragments.size() - 1].position.x > fragments[fragments.size() - 2].position.x)
	{
		fragments[fragments.size() - 1].texture = ResourceManager::getTexture("snake-tail-left");
	}
	else if (fragments[fragments.size() - 1].position.x < fragments[fragments.size() - 2].position.x)
	{
		fragments[fragments.size() - 1].texture = ResourceManager::getTexture("snake-tail-right");
	}
	else if (fragments[fragments.size() - 1].position.y > fragments[fragments.size() - 2].position.y)
	{
		fragments[fragments.size() - 1].texture = ResourceManager::getTexture("snake-tail-up");
	}
	else if (fragments[fragments.size() - 1].position.y < fragments[fragments.size() - 2].position.y)
	{
		fragments[fragments.size() - 1].texture = ResourceManager::getTexture("snake-tail-down");
	}
	// self-intersection
	for (GLuint i = 0; i < fragments.size(); i++)
	{
		for (GLuint j = i + 1; j < fragments.size(); j++)
		{
			if (fragments[i].position.x == fragments[j].position.x && fragments[i].position.y == fragments[j].position.y)
			{
				isDead = GL_TRUE;
			}
		}
	}
	// hit the window frame
	if (fragments[0].position.x < minX || fragments[0].position.x > maxX ||
		fragments[0].position.y < minY || fragments[0].position.y > maxY)
	{
		isDead = GL_TRUE;
	}
}

void Snake::setActivityRange(GLuint minX, GLuint minY, GLuint maxX, GLuint maxY)
{
	this->minX = minX;
	this->minY = minY;
	this->maxX = maxX;
	this->maxY = maxY;
}


GLboolean Snake::eatFood(Food& food)
{
	if (food.position.x == fragments[0].position.x && food.position.y == fragments[0].position.y)
	{
		food.isEaten = GL_TRUE;
		fragments.push_back(SnakeFragment(fragments[fragments.size() - 1].position, fragmentSize, fragments[fragments.size() - 1].texture));
		return GL_TRUE;
	}
	return GL_FALSE;
}

void Snake::draw(SpriteRenderer& renderer)
{
	for (GLuint i = 0; i < fragments.size(); i++)
	{
		fragments[i].draw(renderer);
	}
}
