#include "ShaderController.h"

CShader::CShader(const char* ss, GLuint mode)
{
	Init(ss,mode);
}

void CShader::Init(const char* ss, GLuint mode)
{
	Shader = glCreateShader(mode);

	std::string _s = ReadFile(ss);

	shadfile = ss;

	const char* shadcon = _s.c_str();

	ShaderMode = mode;

	ShaderProgram = glCreateProgram();

	glShaderSource(Shader, 1, &shadcon, NULL);

	DevDrop("Compiling and loading shader %s",ss);

	glCompileShader(Shader);

	glAttachShader(ShaderProgram, Shader);

	printShaderInfoLog(Shader);
	printProgramInfoLog(ShaderProgram);

	glLinkProgram(ShaderProgram);
}

std::string CShader::ReadFile( const char* filename )
{
	string fileString = string();
	string line = string();

	std::ifstream file(filename);

	if (file.is_open()) 
	{
		while (!file.eof()) 
		{
			getline(file, line);
			fileString.append(line);
			fileString.append("\n");
		}

		file.close();
	}

	return fileString;
}

void CShader::Bind()
{
	glUseProgram(ShaderProgram);
}

void CShader::Unbind()
{
	glUseProgram(NULL);
}

void CShader::printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		if(strlen(infoLog) > 0)
		{
			DevError("%s",infoLog);
		}
		else
		{
			DevDrop("	Shader successfully loaded!");
		}
		free(infoLog);
	}
}

void CShader::printProgramInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		if(strlen(infoLog) > 0)
		{
			DevError("	%s\n",infoLog);
		}
		else
		{
			DevDrop("	Shader Program successfully loaded!");
		}
		free(infoLog);
	}
}

void CShader::Kill()
{
	glUseProgram(0);
	glDeleteProgram(this->ShaderProgram);
	glDeleteShader(this->Shader);
}

CShaderController::CShaderController()
{

}

void CShaderController::RegisterNewShader( const char* signature, const char* file, GLuint type )
{
	CShader* ns = new CShader(file, type);
	ShaderMap[signature] = ns;
}

void CShaderController::KillShader( const char* shnm )
{
	if(ShaderMap.find(shnm) != ShaderMap.end()) //If exists
	{
		ShaderMap[shnm]->Kill();
		ShaderMap.erase(shnm);
	}
}

void CShaderController::BindShader( const char* name )
{
	ShaderMap[name]->Bind();
}

void CShaderController::UnbindShader( const char* name )
{
	ShaderMap[name]->Unbind();
}

void CShaderController::PauseAllShaders()
{

}

void CShaderController::PlayAllShaders()
{

}

void CShaderController::LinkShader( CShader* shader )
{

}

void CShaderController::ReloadShader( const char* name )
{
	GLuint mode;
	const char* sourcefile;
	mode = ShaderMap[name]->ShaderMode;
	sourcefile = ShaderMap[name]->shadfile;
	KillShader(name);
	RegisterNewShader(name, sourcefile, mode);



}

void CShaderController::SetUniform( const char* uniform, const char* signature, GLuint var )
{
	GLint handle = glGetUniformLocation(ShaderMap[signature]->GetProgram(), uniform);
	glProgramUniform1ui(ShaderMap[signature]->GetProgram(), handle, var);
}

void CShaderController::SetUniform( const char* uniform, const char* signature, GLfloat var )
{
	GLint handle = glGetUniformLocation(ShaderMap[signature]->GetProgram(), uniform);
	glProgramUniform1f(ShaderMap[signature]->GetProgram(), handle, var);
}

void CShaderController::SetUniform( const char* uniform, const char* signature, GLint var )
{
	GLint handle = glGetUniformLocation(ShaderMap[signature]->GetProgram(), uniform);
	glProgramUniform1i(ShaderMap[signature]->GetProgram(), handle, var);
}
