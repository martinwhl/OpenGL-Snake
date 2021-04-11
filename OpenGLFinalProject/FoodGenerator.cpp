#include "FoodGenerator.h"
#include <cstdlib>
#include "ResourceManager.h"

Food FoodGenerator::generate(GLuint width, GLuint height, glm::vec2 unitSize, const std::vector<SnakeFragment>& fragments)
{
	GLuint rows = width / unitSize.x;
	GLuint columns = height / unitSize.y;
	GLuint randomRow;
	GLuint randomColumn;
	GLboolean conflict = GL_TRUE;
	while (conflict)
	{
		randomRow = rand() % rows;
		randomColumn = rand() % columns;
		GLuint randomX = randomRow * unitSize.x;
		GLuint randomY = randomColumn * unitSize.y;
		GLuint i = 0;
		while (i < fragments.size())
		{
			if (fragments[i].position.x == randomX && fragments[i].position.y == randomY)
			{
				break;
			}
			i++;
		}
		if (i == fragments.size())
		{
			conflict = GL_FALSE;
		}
	}
	// GLuint randomAppleNumber = rand() % 5 + 1;
	GLuint randomAppleNumber = rand() % 5 + 1;
	GLchar randomAppleNumChars[64];
	sprintf(randomAppleNumChars, "%d", randomAppleNumber);
	return Food(glm::vec2(randomRow * unitSize.x, randomColumn * unitSize.y), unitSize, 
		ResourceManager::getTexture("apple-" + std::string(randomAppleNumChars)), randomAppleNumber);
}
