#ifndef __SPRITE_RENDERER_H
#define __SPRITE_RENDERER_H

#include "Shader.h"
#include "Texture2D.h"

class SpriteRenderer
{
public:
	SpriteRenderer(Shader & shader);
	~SpriteRenderer();
	void drawSprite(Texture2D & texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotation = 0.0f, 
		glm::vec3 color = glm::vec3(1.0f));
private:
	Shader shader;
	GLuint quadVAO;
	void initRenderData();
};

#endif
