#pragma once
#include <string>

class Encryptor final{
	bool set;
	unsigned int eCode[3];
public:
	Encryptor();
    void Encrypt(std::string&, int&, int);
};

class Decryptor final{
	unsigned int dCode[3];
public:
	Decryptor();
	void Decrypt(std::string&, int&, int);
};