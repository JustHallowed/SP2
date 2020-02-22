#include "Crypto.h"
#include <fstream>

//Encryptor method defs
Encryptor::Encryptor(): eCode{0, 0, 0}, set(0){}

void Encryptor::Encrypt(std::string& name, int& score, int complexity){
	switch(complexity){
		case 0: { //Remove files to prevent decryption
			void(remove("LocalStorage/Codes.secret"));
			void(remove("LocalStorage/Key.secret"));
			break;
		}
		case 3: { //Matrix encryption for name
			//size_t strLen = name.length();
			//short *keyMatrix = new short[strLen * strLen], *subjMatrix = new short[strLen], *resultMatrix = new short[strLen];
			//std::string keyStr = "GYBNQKURPHJLAMCTGYBNQKURPHJLAMCTGYBNQKURPHJLAMCT";
			//int k = 0;
			//for(size_t i = 0; i < strLen * strLen; ++i){
			//	keyMatrix[i] = rand() % 3;
			//	//keyMatrix[i] = (keyStr[k]) % 65;
			//	//++k;
			//}
			//for(size_t i = 0; i < strLen; ++i){
			//	subjMatrix[i] = short(name[i]);
			//	resultMatrix[i] = 0;
			//}
			//std::string tempStr = "";
			//for(size_t r = 0; r < strLen; ++r){
			//	for(size_t c = 0; c < strLen; ++c){
			//		resultMatrix[r] += keyMatrix[r * strLen + c] * subjMatrix[r];
			//		tempStr += char(resultMatrix[r]);
			//	}
			//}
			//name = tempStr;
			//std::ofstream key("LocalStorage/Key.secret");
			//for(size_t i = 0; i < strLen; ++i){
			//	key << (i ? "\n" : "") << resultMatrix[i];
			//}
			//key.close();
			//delete[] keyMatrix;
			//delete[] subjMatrix;
			//delete[] resultMatrix;
		}
		default: { //Normal encryption for score
			if(!set){
				if(complexity & 1){
					eCode[0] = (rand() % 10) + 1; //1 - 10
					eCode[1] = eCode[2] = 2;
				} else{
					eCode[0] = ((rand() % 10) + 1) * 2; //2 - 20
					eCode[1] = rand() % 5 + 2; //2 - 6
					eCode[2] = unsigned int(abs(int(eCode[0]) - int(eCode[1])));
				}
				set = 1;
			}
			score = (score + eCode[0]) * eCode[1] - eCode[2];
			std::ofstream codes("LocalStorage/Codes.secret");
			codes << eCode[0] << std::endl << eCode[1] << std::endl << eCode[2];
			codes.close();
		}
	}
}

//Decryptor method defs
Decryptor::Decryptor(): dCode{0, 0, 0}{}

void Decryptor::Decrypt(std::string& name, int& score, int dType){
	switch(dType){
		case 0: return;
		case 2: { //Matrix decryption for name
		}
		case 1: { //Normal decryption for score
			std::ifstream codes("LocalStorage/Codes.secret");
			std::string line;
			short index = -1;
			while(getline(codes, line)){
				dCode[++index] = stoul(line);
			}
			score = (score + dCode[2]) / dCode[1] - dCode[0];
			codes.close();
		}
	}
}