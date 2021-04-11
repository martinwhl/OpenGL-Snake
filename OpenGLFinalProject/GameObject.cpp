#include "GameObject.h"

GameObject::GameObject() : position(0, 0), size(1, 1), velocity(0.0f), color(1.0f), rotation(0.0f), texture()
{
}

GameObject::GameObject(glm::vec2 position, glm::vec2 size, Texture2D texture, glm::vec3 color, glm::vec2 velocity) :
	position(position), size(size), velocity(velocity), color(color), rotation(0.0f), texture(texture)
{
}

void GameObject::draw(SpriteRenderer & renderer)
{
	renderer.drawSprite(this->texture, this->position, this->size, this->rotation, this->color);
}
