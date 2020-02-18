#pragma once

class ShaderManager final{
    unsigned int progID, vsID, fsID;
public:
    ShaderManager(const char*, const char*);
    ~ShaderManager();
    unsigned int getProgID() const;
    void LinkProg() const, ParseShader(const char*, unsigned int&) const, UseProg() const;
};