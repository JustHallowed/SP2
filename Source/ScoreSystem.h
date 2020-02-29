#pragma once
#include <iostream>
#include "Crypto.h"

class ScoreNode final{
	std::pair<std::string, unsigned short> nameScore;
	ScoreNode *prev, *next;
public:
	ScoreNode();
	std::pair<std::string, unsigned short> getNameScore() const;
	ScoreNode *getPrev() const, *getNext() const;
	void setName(std::string), setScore(unsigned short), setPrev(ScoreNode*), setNext(ScoreNode*);
};

class ScoreManager final{
	int dType; //Decrypt type
	Encryptor* eDevice;
	Decryptor* dDevice;
	ScoreNode *head, *curr;
	std::string text;
public:
	ScoreManager();
	~ScoreManager();
	ScoreNode *Arrange(ScoreNode*, ScoreNode*) const, *DivideList(ScoreNode*) const, *MergeSort(ScoreNode*&) const;
	std::string retrieveNameScoreData(bool);
	void addNameScore(std::pair<std::string, unsigned short>), tapOnBackup(int), putData(int), sortNameScoreData(), createNewBackup(int), storeNewData();
};