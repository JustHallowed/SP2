#include "ShaderManager.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>

ShaderManager& ShaderManager::getShaderMan(){
	static ShaderManager shaderMan;
	return shaderMan;
}

unsigned int ShaderManager::getProgID(){
	static unsigned int progID = glCreateProgram();
	return progID;
}

ShaderManager::ShaderManager(){
	for(short i = 0; i < 1; ++i){
		vsID[i] = glCreateShader(GL_VERTEX_SHADER);
		fsID[i] = glCreateShader(GL_FRAGMENT_SHADER);
	}
	ParseShader("Resources/Shaders/Regular.vs", vsID[0]);
	ParseShader("Resources/Shaders/Regular.fs", fsID[0]);
	glAttachShader(getProgID(), vsID[0]);
	glAttachShader(getProgID(), fsID[0]);
	LinkProg();
	UseProg();
}

ShaderManager::~ShaderManager(){
	for(short i = 0; i < 1; ++i){
		glDetachShader(getProgID(), vsID[i]);
		glDetachShader(getProgID(), fsID[i]);
		glDeleteShader(vsID[i]);
		glDeleteShader(fsID[i]);
	}
	glDeleteProgram(getProgID());
}

void ShaderManager::LinkProg() const{
	GLint result, infoLogLength;
	printf("Linking programme...");
	glLinkProgram(getProgID()); //Vars in diff shaders are linked here too
	glValidateProgram(getProgID());

	//Check the programme
	glGetProgramiv(getProgID(), GL_LINK_STATUS, &result);
	glGetProgramiv(getProgID(), GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0){
		std::vector<char> errorMsg(infoLogLength + 1);
		glGetProgramInfoLog(getProgID(), infoLogLength, NULL, &errorMsg[0]);
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
	glDetachShader(getProgID(), vsID[currIndex]);
	glDetachShader(getProgID(), fsID[currIndex]);
	glAttachShader(getProgID(), vsID[newIndex]);
	glAttachShader(getProgID(), fsID[newIndex]);
	LinkProg();
	UseProg();
}

void ShaderManager::UseProg() const{
	glUseProgram(getProgID());
}