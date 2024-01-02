#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <gl/glew.h>

Shader::Shader(std::string vertexFilepath, std::string fragmentFilepath)
	: m_VertexFilePath(std::move(vertexFilepath)), m_FragmentFilePath(std::move(fragmentFilepath)), m_ProgramId(0)
{
	m_VertexSource = ReadShaderCode(m_VertexFilePath);
	m_FragmentSource = ReadShaderCode(m_FragmentFilePath);
	m_ProgramId = CreateShaders(m_VertexSource, m_FragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(m_ProgramId);
}


std::string Shader::ReadShaderCode(const std::string& fileName)
{
	std::ifstream meInput(fileName);
	if (!meInput.good())
	{
		std::cout << "File failed to load..." << fileName;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>());
}

bool Shader::CheckStatus(
	const GLuint objectId,
	const PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	const PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	const GLenum statusType)
{
	GLint compileStatus;
	objectPropertyGetterFunc(objectId, statusType, &compileStatus);
	if (compileStatus != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* buffer = new GLchar[infoLogLength];
		GLsizei bufferSize;
		getInfoLogFunc(objectId, infoLogLength, &bufferSize, buffer);

		std::cout << buffer << '\n';

		delete[] buffer;
		return false;
	}
	return true;
}


bool Shader::CheckShaderStatus(const GLuint shaderId)
{
	return CheckStatus(
		shaderId,
		glGetShaderiv,
		glGetShaderInfoLog,
		GL_COMPILE_STATUS);
}

bool Shader::CheckProgramStatus(const GLuint programId)
{
	return CheckStatus(
		programId,
		glGetProgramiv,
		glGetProgramInfoLog,
		GL_LINK_STATUS);
}

unsigned int Shader::CreateShaders(const std::string& vertexShader, const std::string& fragmentShader)
{
	const GLuint programId = glCreateProgram();
	const GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	const GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);


	const GLchar* vertexSource = vertexShader.c_str();
	glShaderSource(vertexShaderId, 1, &vertexSource, nullptr);
	const GLchar* fragmentSource = fragmentShader.c_str();
	glShaderSource(fragmentShaderId, 1, &fragmentSource, nullptr);

	glCompileShader(vertexShaderId);
	glCompileShader(fragmentShaderId);

	if (!CheckShaderStatus(vertexShaderId) || !CheckShaderStatus(fragmentShaderId))
		return 0;

	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	if (!CheckProgramStatus(programId))
		return 0;

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return programId;
}

void Shader::Bind() const
{
	glUseProgram(m_ProgramId);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, const int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, const float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, const float v0, const float v1, const float v2, const float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.contains(name))
		return m_UniformLocationCache[name];

	const int location = glGetUniformLocation(m_ProgramId, name.c_str());
	if (location == -1)
	{
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << '\n';
	}


	m_UniformLocationCache[name] = location;
	return location;
}
