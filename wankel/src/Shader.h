#pragma once
#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(std::string vertexFilepath, std::string fragmentFilepath);
	~Shader();

	void Bind() const;
	static void Unbind();

	// Set Uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	static std::string ReadShaderCode(const std::string& fileName);
	static bool CheckStatus(GLuint objectId, PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	                        PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType);
	static bool CheckShaderStatus(GLuint shaderId);
	static bool CheckProgramStatus(GLuint programId);
	static unsigned CreateShaders(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& name);

	std::string m_VertexFilePath;
	std::string m_FragmentFilePath;
	std::string m_VertexSource;
	std::string m_FragmentSource;

	unsigned int m_ProgramId;
	std::unordered_map<std::string, int> m_UniformLocationCache;
};
