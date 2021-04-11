#include "Food.h"

Food::Food() : GameObject(), score(0), isEaten(GL_FALSE)
{
}

Food::Food(glm::vec2 position, glm::vec2 size, Texture2D texture, GLuint score, glm::vec3 color, glm::vec2 velocity) : GameObject(
	position, size, texture, color, velocity), score(score), isEaten(GL_FALSE)
{
}

void Food::draw(SpriteRenderer& renderer)
{
	renderer.drawSprite(texture, position, size);
}
