#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "ResourceManager.h"
#include <iostream>

void key_callback(GLFWwindow * window, GLint key, GLint scanCode, GLint action, GLint mode);

const GLuint WINDOW_WIDTH = 640;
const GLuint WINDOW_HEIGHT = 640;

Game game(WINDOW_WIDTH, WINDOW_HEIGHT);

int main(int argc, char * argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Snake", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD." << std::endl;
	}

	glfwSetKeyCallback(window, key_callback);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	game.init();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;
	game.state = GAME_ACTIVE;

	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();
		game.processInput(deltaTime);
		game.update(deltaTime);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		game.render();
		glfwSwapBuffers(window);
	}

	ResourceManager::clear();
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow * window, GLint key, GLint scanCode, GLint action, GLint mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			game.keys[key] = GL_TRUE;
		}
		else if (action == GLFW_RELEASE)
		{
			game.keys[key] = GL_FALSE;
		}
	}
}
