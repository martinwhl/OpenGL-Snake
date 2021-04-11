#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Snake.h"
#include "FoodGenerator.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <ctime>
#include <irrKlang/irrKlang.h>

Game::Game(GLuint width, GLuint height) : state(GAME_ACTIVE), keys(), width(width), height(height)
{
}

Game::~Game()
{
	delete spriteRenderer;
	delete textRenderer;
	delete snake;
	delete food;
	delete soundEngine;
}

void Game::init()
{
	srand(time(NULL));
	ResourceManager::loadShader("shaders/sprite.vs", "shaders/sprite.fs", nullptr, "sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height),
	                                  0.0f, -1.0f, 1.0f);
	ResourceManager::getShader("sprite").use().setInteger("image", 0);
	ResourceManager::getShader("sprite").setMatrix4("projection", projection);
	spriteRenderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
	ResourceManager::loadTexture("res/8-bit/apple-1.png", GL_TRUE, "apple-1");
	ResourceManager::loadTexture("res/8-bit/apple-2.png", GL_TRUE, "apple-2");
	ResourceManager::loadTexture("res/8-bit/apple-3.png", GL_TRUE, "apple-3");
	ResourceManager::loadTexture("res/8-bit/apple-4.png", GL_TRUE, "apple-4");
	ResourceManager::loadTexture("res/8-bit/apple-5.png", GL_TRUE, "apple-5");
	ResourceManager::loadTexture("res/8-bit/meadow.png", GL_TRUE, "meadow");
	ResourceManager::loadTexture("res/8-bit/snake-body-left.png", GL_TRUE, "snake-body-left");
	ResourceManager::loadTexture("res/8-bit/snake-body-right.png", GL_TRUE, "snake-body-right");
	ResourceManager::loadTexture("res/8-bit/snake-body-up.png", GL_TRUE, "snake-body-up");
	ResourceManager::loadTexture("res/8-bit/snake-body-down.png", GL_TRUE, "snake-body-down");
	ResourceManager::loadTexture("res/8-bit/snake-head-left.png", GL_TRUE, "snake-head-left");
	ResourceManager::loadTexture("res/8-bit/snake-head-right.png", GL_TRUE, "snake-head-right");
	ResourceManager::loadTexture("res/8-bit/snake-head-up.png", GL_TRUE, "snake-head-up");
	ResourceManager::loadTexture("res/8-bit/snake-head-down.png", GL_TRUE, "snake-head-down");
	ResourceManager::loadTexture("res/8-bit/snake-tail-left.png", GL_TRUE, "snake-tail-left");
	ResourceManager::loadTexture("res/8-bit/snake-tail-right.png", GL_TRUE, "snake-tail-right");
	ResourceManager::loadTexture("res/8-bit/snake-tail-up.png", GL_TRUE, "snake-tail-up");
	ResourceManager::loadTexture("res/8-bit/snake-tail-down.png", GL_TRUE, "snake-tail-down");
	ResourceManager::loadTexture("res/8-bit/snake-turn-left-up.png", GL_TRUE, "snake-turn-left-up");
	ResourceManager::loadTexture("res/8-bit/snake-turn-left-down.png", GL_TRUE, "snake-turn-left-down");
	ResourceManager::loadTexture("res/8-bit/snake-turn-right-up.png", GL_TRUE, "snake-turn-right-up");
	ResourceManager::loadTexture("res/8-bit/snake-turn-right-down.png", GL_TRUE, "snake-turn-right-down");
	textRenderer = new TextRenderer(this->width, this->height);
	textRenderer->load("res/PressStart2P.ttf", 16);
	soundEngine = irrklang::createIrrKlangDevice();
	soundEngine->play2D("res/music/Rolemusic_-_Shaanti.mp3", GL_TRUE);

	runningTime = 0.0f;
	lastFrame = 0.0f;
	score = 0;
	snake = new Snake();
	snake->setActivityRange(0, 0, this->width, this->height);
	Food f = FoodGenerator::generate(this->width, this->height, glm::vec2(32, 32), snake->fragments);
	food = new Food(f);
}

void Game::update(GLfloat dt)
{
	runningTime += dt;
	if (state == GAME_ACTIVE)
	{
		if (runningTime - lastFrame >= frameTime())
		{
			snake->move();
			if (snake->isDead)
			{
				state = GAME_OVER;
			}
			lastFrame = runningTime;
		}
	}
}

GLfloat Game::frameTime()
{
	if (score < 50)
	{
		return (0.2000f - score * 0.0015f);
	}
	if (score < 150)
	{
		return (0.1250f - (score - 50) * 0.0005f);
	}
	return 0.0750f;
}

void Game::processInput(GLfloat dt)
{
	if (this->state == GAME_ACTIVE)
	{
		if (this->keys[GLFW_KEY_A] || this->keys[GLFW_KEY_LEFT])
		{
			if (snake->direction == DIRECTION_RIGHT)
			{
				return;
			}
			snake->direction = DIRECTION_LEFT;
			soundEngine->play2D("res/sounds/sfx_movement_footsteps1a.wav", GL_FALSE);
		}
		if (this->keys[GLFW_KEY_D] || this->keys[GLFW_KEY_RIGHT])
		{
			if (snake->direction == DIRECTION_LEFT)
			{
				return;
			}
			snake->direction = DIRECTION_RIGHT;
			soundEngine->play2D("res/sounds/sfx_movement_footsteps1a.wav", GL_FALSE);
		}
		if (this->keys[GLFW_KEY_W] || this->keys[GLFW_KEY_UP])
		{
			if (snake->direction == DIRECTION_DOWN)
			{
				return;
			}
			snake->direction = DIRECTION_UP;
			soundEngine->play2D("res/sounds/sfx_movement_footsteps1a.wav", GL_FALSE);
		}
		if (this->keys[GLFW_KEY_S] || this->keys[GLFW_KEY_DOWN])
		{
			if (snake->direction == DIRECTION_UP)
			{
				return;
			}
			snake->direction = DIRECTION_DOWN;
			soundEngine->play2D("res/sounds/sfx_movement_footsteps1a.wav", GL_FALSE);
		}
	}
	else if (this->state == GAME_OVER)
	{
		if (this->keys[GLFW_KEY_R])
		{
			delete snake;
			snake = new Snake();
			snake->setActivityRange(0, 0, this->width, this->height);
			delete food;
			Food f = FoodGenerator::generate(this->width, this->height, glm::vec2(32, 32), snake->fragments);
			food = new Food(f);
			runningTime = lastFrame = 0.0f;
			score = 0;
			this->state = GAME_ACTIVE;
		}
	}
}

void Game::render()
{
	if (this->state == GAME_ACTIVE)
	{
		// meadow
		for (GLuint i = 0; i < height / 32; i++)
		{
			for (GLuint j = 0; j < width / 32; j++)
			{
				spriteRenderer->drawSprite(ResourceManager::getTexture("meadow"), glm::vec2(i * 32, j * 32),
				                           glm::vec2(32, 32), 0.0f,
				                           glm::vec3(1.0f, 1.0f, 1.0f));
			}
		}

		GLchar timeChars[64];
		sprintf(timeChars, "%.2f", runningTime);
		GLchar scoreChars[64];
		sprintf(scoreChars, "%d", score);
		// text
		textRenderer->renderText("TIME: " + std::string(timeChars), this->width - 160.0f, 25.0f, 0.8f,
		                         glm::vec3(1.0f, 1.0f, 1.0f));
		textRenderer->renderText("SCORE: " + std::string(scoreChars), this->width - 160.0f, 50.0f, 0.8f,
		                         glm::vec3(1.0f, 1.0f, 1.0f));

		// temp snake with Snake class
		snake->draw(*spriteRenderer);
		snake->eatFood(*food);
		if (food->isEaten)
		{
			soundEngine->play2D("res/sounds/sfx_sounds_powerup8.wav", GL_FALSE);
			score += food->score;
			Food f = FoodGenerator::generate(this->width, this->height, glm::vec2(32, 32), snake->fragments);
			delete food;
			food = new Food(f);
		}
		food->draw(*spriteRenderer);
	}
	else if (this->state == GAME_OVER)
	{
		soundEngine->play2D("res/sounds/sfx_deathscream_alien2.wav", GL_FALSE);
		char lastFrameChars[64];
		sprintf(lastFrameChars, "%.2f", lastFrame);
		char scoreChars[64];
		sprintf(scoreChars, "%d", score);
		textRenderer->renderText("GAME OVER", 180.0f, 200.0f, 2.0f);
		textRenderer->renderText("TIME: " + std::string(lastFrameChars), 240.0f, 300.0f, 1.0f);
		textRenderer->renderText("SCORE: " + std::string(scoreChars), 240.0f, 350.0f, 1.0f);
		textRenderer->renderText("PRESS R TO RESTART", 180.0f, 450.0f, 1.0f);
	}
}


// sample snake to test the texture
// spriteRenderer->drawSprite(ResourceManager::getTexture("apple-5"), glm::vec2(0, 0), glm::vec2(32, 32), 0.0f,
//                            glm::vec3(1.0f, 1.0f, 1.0f));
// spriteRenderer->drawSprite(ResourceManager::getTexture("snake-head-up"), glm::vec2(64, 64), glm::vec2(32, 32), 0,
//                            glm::vec3(1.0f, 1.0f, 1.0f));
// spriteRenderer->drawSprite(ResourceManager::getTexture("snake-turn-right-up"), glm::vec2(64, 96), glm::vec2(32, 32),
//                            0,
//                            glm::vec3(1.0f, 1.0f, 1.0f));
// spriteRenderer->drawSprite(ResourceManager::getTexture("snake-body-right"), glm::vec2(96, 96), glm::vec2(32, 32), 0,
//                            glm::vec3(1.0f, 1.0f, 1.0f));
// spriteRenderer->drawSprite(ResourceManager::getTexture("snake-turn-left-down"), glm::vec2(128, 96),
//                            glm::vec2(32, 32), 0,
//                            glm::vec3(1.0f, 1.0f, 1.0f));
// spriteRenderer->drawSprite(ResourceManager::getTexture("snake-body-up"), glm::vec2(128, 128), glm::vec2(32, 32), 0,
//                            glm::vec3(1.0f, 1.0f, 1.0f));
// spriteRenderer->drawSprite(ResourceManager::getTexture("snake-tail-up"), glm::vec2(128, 160), glm::vec2(32, 32), 0,
//                            glm::vec3(1.0f, 1.0f, 1.0f));
