#pragma once
#include <string>
#include <unordered_map>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{

private:

	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int > m_UniformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();


	void Bind() const;
	void UnBind() const;

	//Set Uniforms:
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform1f(const std::string& name, float v0);

private:
	int GetUniformLocation(const std::string& name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexshader, const std::string& fragmentshader);
	ShaderProgramSource ParseShader(const std::string& filepath);
};