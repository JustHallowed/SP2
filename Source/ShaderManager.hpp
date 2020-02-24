#pragma once

class ShaderManager final{
    unsigned int vsID[2], fsID[2];
public:
    ShaderManager();
    ~ShaderManager();
    static unsigned int getProgID();
    void LinkProg() const, ParseShader(const char*, unsigned int&) const, UseNewShaders(short, short) const, UseProg() const;
};