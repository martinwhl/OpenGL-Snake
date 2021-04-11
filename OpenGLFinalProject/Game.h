#ifndef __GAME_H
#define __GAME_H

#include <glad/glad.h>
#include <irrKlang/irrKlang.h>
#include "Food.h"
#include "Snake.h"
#include "TextRenderer.h"

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_OVER
};

class Game
{
public:
	GameState state;
	GLboolean keys[1024];
	GLuint width;
	GLuint height;
	Game(GLuint width, GLuint height);
	~Game();
	void init();
	void processInput(GLfloat dt);
	void update(GLfloat dt);
	void render();
private:
	GLfloat frameTime();
	SpriteRenderer* spriteRenderer;
	TextRenderer* textRenderer;
	Snake * snake;
	Food * food;
	GLfloat runningTime;
	GLfloat lastFrame;
	GLuint score;
	irrklang::ISoundEngine * soundEngine;
};

#endif
