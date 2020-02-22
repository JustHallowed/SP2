#include "ScoreSystem.h"
#include <fstream>

//ScoreNode member function defs
ScoreNode::ScoreNode(): nameScore("", 0), prev(0), next(0){}

std::pair<std::string, unsigned short> ScoreNode::getNameScore() const{
	return nameScore;
}

ScoreNode* ScoreNode::getPrev() const{
	return prev;
}

ScoreNode* ScoreNode::getNext() const{
	return next;
}

void ScoreNode::setName(std::string newName){
	nameScore.first = newName;
}

void ScoreNode::setScore(unsigned short newScore){
	nameScore.second = newScore;
}

void ScoreNode::setPrev(ScoreNode* newPrev){
	prev = newPrev;
}

void ScoreNode::setNext(ScoreNode* newNext){
	next = newNext;
}

//ScoreManager member function defs
ScoreManager::ScoreManager(): head(0), curr(0){
	eDevice = new Encryptor;
	dDevice = new Decryptor;
	std::ifstream codes("LocalStorage/Codes.secret"), key("LocalStorage/Key.secret");
	dType = (key.peek() != std::ifstream::traits_type::eof() ? 2 : (codes.peek() != std::ifstream::traits_type::eof() ? 1 : 0));
	tapOnBackup(dType);
	putData(dType);
	codes.close();
}

ScoreManager::~ScoreManager(){
	createNewBackup(dType);
	storeNewData();
	if(head != 0){
		while(head->getNext() != 0){
			head = head->getNext();
			delete head->getPrev();
		}
		delete head;
	}
	delete eDevice;
	delete dDevice;
}

ScoreNode* ScoreManager::Arrange(ScoreNode* head, ScoreNode* subHead) const{ //Merge 2 sub-LLs
	if(!head){
		return subHead;
	} else if(!subHead){
		return head;
	}
	if(head->getNameScore().second < subHead->getNameScore().second){
		head->setNext(Arrange(head->getNext(), subHead));
		head->getNext()->setPrev(head);
		return head;
	} else{
		subHead->setNext(Arrange(head, subHead->getNext()));
		subHead->getNext()->setPrev(subHead);
		return subHead;
	}
}

ScoreNode* ScoreManager::DivideList(ScoreNode* head) const{
	ScoreNode *fast = head, *slow = head;
	while(fast->getNext() && fast->getNext()->getNext()){
		fast = fast->getNext()->getNext();
		slow = slow->getNext();
	}
	return slow->getNext();
}

ScoreNode* ScoreManager::MergeSort(ScoreNode*& head) const{
	if(head && head->getNext()){ //If length of LL != 0/1...
		ScoreNode* subHead = DivideList(head);
		subHead->getPrev()->setNext(0); //Disconnects 1 list from another
		head = Arrange(MergeSort(head), MergeSort(subHead));
	}
	return head;
}

void ScoreManager::addNameScore(std::pair<std::string, unsigned short> newNameScore){
	ScoreNode* newNode = new ScoreNode;
	if(head == 0){
		head = curr = newNode;
	} else{
		newNode->setNext(head);
		head->setPrev(newNode);
		head = newNode;
	}
	(*newNode).setName(newNameScore.first);
	(*newNode).setScore(newNameScore.second);
}

void ScoreManager::sortNameScoreData(){
	if(head != 0){
		MergeSort(head)->setPrev(0);
	}
}

void ScoreManager::showNameScoreData(bool showType){
	if(!head){
		printf("No names and scores to show.\n");
		return;
	}
	curr = head;
	if(showType){ //Print nameScore data from lowest to highest
		while(curr != 0){
			std::cout << curr->getNameScore().first << ": " << curr->getNameScore().second << std::endl;
			curr = curr->getNext();
		}
	} else{ //Print nameScore data from highest to lowest
		while(curr->getNext() != 0){
			curr = curr->getNext();
		}
		while(curr != 0){
			std::cout << curr->getNameScore().first << ": " << curr->getNameScore().second << std::endl;
			curr = curr->getPrev();
		}
	}
}

void ScoreManager::tapOnBackup(int dType){
	std::ifstream data("LocalStorage/NamesAndScores.data"), backup("LocalStorage/NamesAndScores.backup");
	std::string line;
	if(data.peek() == std::ifstream::traits_type::eof() && backup.peek() != std::ifstream::traits_type::eof()){
		std::ofstream newData("LocalStorage/NamesAndScores.data"); //Create blank data file
		while(getline(backup, line)){
			size_t commaPos = line.find(',');
			std::string name = line.substr(0, commaPos);
			int score = stoi(line.substr(commaPos + 2));
			dDevice->Decrypt(name, score, dType);
			text += name + ", " + std::to_string(score) + '\n';
		}
		text.erase(text.begin() + text.length() - 1); //Remove extra '\n'
		newData << text;
		newData.close();
	}
	data.close();
	backup.close();
}

void ScoreManager::putData(int dType){
	std::ifstream data("LocalStorage/NamesAndScores.data");
	std::string line;
	if(data.peek() != std::ifstream::traits_type::eof()){
		while(getline(data, line)){
			ScoreNode* newNode = new ScoreNode;
			if(!head){
				head = curr = newNode;
			} else{
				newNode->setPrev(curr);
				curr->setNext(newNode);
				curr = newNode;
			}
			size_t commaPos = line.find(',');
			std::string name = line.substr(0, commaPos);
			int score = stoi(line.substr(commaPos + 2));
			dDevice->Decrypt(name, score, dType);
			newNode->setName(name);
			newNode->setScore(unsigned short(score));
		}
	}
	data.close();
}

void ScoreManager::createNewBackup(int dType){
	std::ifstream data("LocalStorage/NamesAndScores.data");
	std::string line;
	text = "";
	if(data.peek() != std::ifstream::traits_type::eof()){
		while(getline(data, line)){
			size_t commaPos = line.find(',');
			std::string name = line.substr(0, commaPos);
			int score = stoi(line.substr(commaPos + 2));
			dDevice->Decrypt(name, score, dType); //Decrypt currently encrypted data
			eDevice->Encrypt(name, score, 3);
			text += name + ", " + std::to_string(score) + '\n';
		}
		std::ofstream newBackup("LocalStorage/NamesAndScores.backup");
		text.erase(text.begin() + text.length() - 1); //Remove extra '\n'
		newBackup << text;
		newBackup.close();
	}
	data.close();
}

void ScoreManager::storeNewData(){ //Store new data encrypted
	std::string line;
	text = "";
	try{
		std::fstream newData("LocalStorage/NamesAndScores.data", std::ios::out);
		if(newData.is_open()){
			curr = head;
			while(curr != 0){
				std::string name = curr->getNameScore().first;
				int score = curr->getNameScore().second;
				eDevice->Encrypt(name, score, 3);
				text += (text.empty() ? "" : "\n") + name + ", " + std::to_string(score);
				curr = curr->getNext();
			}
			newData << text;
			newData.close();
		} else{
			throw("Unable to store names and scores locally.\n");
		}
	} catch(const char* errorMsg){
		printf(errorMsg);
	}
}