#pragma once

class ShaderManager final{
    unsigned int progID, vsID[2], fsID[2];
public:
    ShaderManager();
    ~ShaderManager();
    unsigned int getProgID() const;
    void LinkProg() const, ParseShader(const char*, unsigned int&) const, UseNewShaders(short, short) const, UseProg() const;
};