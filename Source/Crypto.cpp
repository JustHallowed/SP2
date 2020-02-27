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
		case 3: { //Encryption for name
			if(name.length() > 1){
				char temp = name[0];
				name[0] = name[name.length() - 1];
				name[name.length() - 1] = temp;
				reverse(name.begin(), name.end());
				for(size_t i = 0; i < name.length() - 1; ++i){
					name[i] = char(122 - name[i]);
				}
			}
		}
		default: { //Encryption for score
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
		case 2: { //Decryption for name
			if(name.length() > 1){
				for(size_t i = 0; i < name.length() - 1; ++i){
					name[i] = char(122 - name[i]);
				}
				reverse(name.begin(), name.end());
				char temp = name[0];
				name[0] = name[name.length() - 1];
				name[name.length() - 1] = temp;
			}
		}
		case 1: { //Decryption for score
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