#include "Crypto.h"
#include <fstream>

//Encryptor method defs
Encryptor::Encryptor(): eCode{0, 0, 0}, set(0){}

void Encryptor::Encrypt(int& score, int complexity){
	switch(complexity){
		case 0: void(remove("LocalStorage/Codes.secret")); break;
		case 3: { //Matrix encryption
		} break;
		default: { //Normal encryption
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

void Decryptor::Decrypt(int& score, int dType){
	switch(dType){
		case 0: return;
		case 1: { //Normal decryption
			std::ifstream codes("LocalStorage/Codes.secret");
			std::string line;
			short index = -1;
			while(getline(codes, line)){
				dCode[++index] = stoul(line);
			}
			score = (score + dCode[2]) / dCode[1] - dCode[0];
			codes.close();
		} break;
		case 2: { //Matrix decryption
		}
	}
}