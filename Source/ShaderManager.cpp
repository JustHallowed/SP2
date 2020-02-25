#include "ShaderManager.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>

ShaderManager::ShaderManager(const char* vsPath, const char* fsPath): progID(glCreateProgram()), vsID(glCreateShader(GL_VERTEX_SHADER)), fsID(glCreateShader(GL_FRAGMENT_SHADER)){
	ParseShader(vsPath, vsID);
	ParseShader(fsPath, fsID);
	LinkProg();
	UseProg();
}

ShaderManager::~ShaderManager(){
	glDeleteProgram(progID);
}

unsigned int ShaderManager::getProgID() const{
	return progID;
}

void ShaderManager::LinkProg() const{
	GLint result, infoLogLength;
//	printf("Linking programme...\n\n");
	glLinkProgram(progID); //Vars in diff shaders are linked here too
	glValidateProgram(progID);

	//Check the programme
	glGetProgramiv(progID, GL_LINK_STATUS, &result);
	glGetProgramiv(progID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0){
		std::vector<char> errorMsg(infoLogLength + 1);
		glGetProgramInfoLog(progID, infoLogLength, NULL, &errorMsg[0]);
		//printf("%s\n", &errorMsg[0]);
	}

	glDeleteShader(vsID);
	glDeleteShader(fsID);
}

void ShaderManager::ParseShader(const char* filePath, unsigned int& shaderID) const{
	GLint result, infoLogLength;
	std::ifstream stream(filePath, std::ios::in);
	std::string shaderSrc, line;

	if(stream.is_open()){
		while(getline(stream, line)){
			shaderSrc += "\n" + line;
		}
		stream.close();
	} else{
		//printf("Failed to open and read \"%s\"\n", filePath);
		return;
	}

	//printf("Compiling \"%s\"...\n", filePath);
	const char* shaderSrcPtr = shaderSrc.c_str();
	glShaderSource(shaderID, 1, &shaderSrcPtr, NULL);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if(!result){
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* errorMsg = (char*)_malloca(infoLogLength * sizeof(char)); //Allocate memory on the stack dynamically
		glGetShaderInfoLog(shaderID, infoLogLength, &infoLogLength, errorMsg);
		//printf("Failed to compile \"%s\"!\n%s\n", filePath, errorMsg);
	}

	glAttachShader(progID, shaderID);
}

void ShaderManager::UseProg() const{
	glUseProgram(progID);
}