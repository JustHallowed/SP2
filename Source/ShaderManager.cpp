#include "ShaderManager.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>

ShaderManager::ShaderManager(): progID(glCreateProgram()){
	for(short i = 0; i < 2; ++i){
		vsID[i] = glCreateShader(GL_VERTEX_SHADER);
		fsID[i] = glCreateShader(GL_FRAGMENT_SHADER);
	}
	ParseShader("Resources/Shaders/Regular.vs", vsID[0]);
	ParseShader("Resources/Shaders/Regular.fs", fsID[0]);
	ParseShader("Resources/Shaders/Particle.vs", vsID[1]);
	ParseShader("Resources/Shaders/Particle.fs", fsID[1]);
	glAttachShader(progID, vsID[0]);
	glAttachShader(progID, fsID[0]);
	LinkProg();
	UseProg();
}

ShaderManager::~ShaderManager(){
	for(short i = 0; i < 2; ++i){
		glDetachShader(progID, vsID[i]);
		glDetachShader(progID, fsID[i]);
		glDeleteShader(vsID[i]);
		glDeleteShader(fsID[i]);
	}
	glDeleteProgram(progID);
}

unsigned int ShaderManager::getProgID() const{
	return progID;
}

void ShaderManager::LinkProg() const{
	GLint result, infoLogLength;
	printf("Linking programme...\n\n");
	glLinkProgram(progID); //Vars in diff shaders are linked here too
	glValidateProgram(progID);

	//Check the programme
	glGetProgramiv(progID, GL_LINK_STATUS, &result);
	glGetProgramiv(progID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0){
		std::vector<char> errorMsg(infoLogLength + 1);
		glGetProgramInfoLog(progID, infoLogLength, NULL, &errorMsg[0]);
		printf("%s\n", &errorMsg[0]);
	}
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
		printf("Failed to open and read \"%s\"\n", filePath);
		return;
	}

	printf("Compiling \"%s\"...\n", filePath);
	const char* shaderSrcPtr = shaderSrc.c_str();
	glShaderSource(shaderID, 1, &shaderSrcPtr, NULL);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if(!result){
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* errorMsg = (char*)_malloca(infoLogLength * sizeof(char)); //Allocate memory on the stack dynamically
		glGetShaderInfoLog(shaderID, infoLogLength, &infoLogLength, errorMsg);
		printf("Failed to compile \"%s\"!\n%s\n", filePath, errorMsg);
	}
}

void ShaderManager::UseNewShaders(short currIndex, short newIndex) const{
	glDetachShader(progID, vsID[currIndex]);
	glDetachShader(progID, fsID[currIndex]);
	glAttachShader(progID, vsID[newIndex]);
	glAttachShader(progID, fsID[newIndex]);
	LinkProg();
	UseProg();
}

void ShaderManager::UseProg() const{
	glUseProgram(progID);
}