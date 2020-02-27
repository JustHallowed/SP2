#pragma once

class ShaderManager final{ //Singleton
    ShaderManager();
    ShaderManager(const ShaderManager&); //Private copy ctor
    ShaderManager(ShaderManager&&); //Private move ctor
    ShaderManager& operator=(const ShaderManager&){}; //Private copy assignment operator
    ShaderManager& operator=(ShaderManager&&) noexcept{}; //Private move assignment operator
    unsigned int vsID[2], fsID[2];
public:
    ~ShaderManager();
    static ShaderManager& getShaderMan();
    static unsigned int getProgID();
    void LinkProg() const, ParseShader(const char*, unsigned int&) const, UseNewShaders(short, short) const, UseProg() const;
};