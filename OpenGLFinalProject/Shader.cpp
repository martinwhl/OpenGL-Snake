#include "Shader.h"
#include <iostream>

Shader & Shader::use()
{
	glUseProgram(this->ID);
	return *this;
}

void Shader::compile(const GLchar * vertexSource, const GLchar * fragmentSource, const GLchar * geometrySource)
{
	GLuint vertexShader, fragmentShader, geometryShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "VERTEX");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, "FRAGMENT");
	if (geometrySource != nullptr)
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometrySource, NULL);
		glCompileShader(geometryShader);
		checkCompileErrors(geometryShader, "GEOMETRY");
	}
	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertexShader);
	glAttachShader(this->ID, fragmentShader);
	if (geometrySource != nullptr)
	{
		glAttachShader(this->ID, geometryShader);
	}
	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, "PROGRAM");
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometrySource != NULL)
	{
		glDeleteShader(geometryShader);
	}
}

void Shader::setInteger(const GLchar * name, GLint value, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::setFloat(const GLchar * name, GLfloat value, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::setVector2f(const GLchar * name, GLfloat x, GLfloat y, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void Shader::setVector2f(const GLchar* name, const glm::vec2 & value, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::setVector3f(const GLchar * name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::setVector3f(const GLchar * name, const glm::vec3 & value, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::setVector4f(const GLchar * name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}

void Shader::setVector4f(const GLchar * name, const glm::vec4 & value, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const GLchar * name, const glm::mat4 & matrix, GLboolean useShader)
{
	if (useShader)
	{
		this->use();
	}
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(GLuint object, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM: Link-time error: Type: " << type << "\n"
				<< infoLog << std::endl;
		}
	}
}

