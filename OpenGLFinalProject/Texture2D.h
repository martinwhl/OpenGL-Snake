#ifndef __TEXTURE2D_H
#define __TEXTURE2D_H

#include <glad/glad.h>

class Texture2D
{
public:
	GLuint ID;
	GLuint width;
	GLuint height;
	GLuint internalFormat;
	GLuint imageFormat;
	GLuint wrapS;
	GLuint wrapT;
	GLuint filterMin;
	GLuint filterMag;
	Texture2D();
	void generate(GLuint width, GLuint height, GLubyte * data);
	void bind() const;
};

#endif
