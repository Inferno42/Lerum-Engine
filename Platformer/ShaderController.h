#ifndef SC_H
#define SC_H
#include "Definitions.h"

class CShader
{
public:
	CShader(const char* ss, GLuint mode);

	void Init(const char*, GLuint mode);
	std::string ReadFile(const char* filename);
	void Bind();
	void Unbind();
	void Kill();
	GLuint GetProgram() {if(ShaderProgram) {return ShaderProgram;}}
	void printShaderInfoLog(GLuint obj);
	void printProgramInfoLog(GLuint obj);

	const char* shadfile;
	GLuint ShaderMode;

private:
	GLuint ShaderSource;
	GLuint Shader;
	GLuint ShaderProgram;
	bool Initialized;
};

typedef std::map<const char*, CShader*> tShadeMap;

class CShaderController
{
public:
	CShaderController();

	void RegisterNewShader(const char* signature, const char* file, GLuint type);
	void LinkShader(CShader* shader);
	void KillShader(const char* shnm);
	void BindShader(const char* name);
	void ReloadShader(const char* name);
	void UnbindShader(const char* name);
	void SetUniform(const char* uniform, const char* signature, GLuint var);
	void SetUniform(const char* uniform, const char* signature, GLfloat var);
	void SetUniform(const char* uniform, const char* signature, GLint var);
	void PauseAllShaders();
	void PlayAllShaders();

private:
	tShadeMap ShaderMap;
};

#endif