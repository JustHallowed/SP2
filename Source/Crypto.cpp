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
		case 3: { //Matrix encryption (based on Hill Cipher) for name
			if(name.length() > 1){
				reverse(name.begin(), name.end());
				short keyMatrix[4], subjMatrix[2], resultMatrix[2]{0, 0};
				keyMatrix[0] = rand() % 10; //0 - 9
				keyMatrix[3] = rand() % 10; //0 - 9
				do{
					keyMatrix[1] = rand() % 9 + 1; //1 - 9
					keyMatrix[2] = rand() % 9 + 1; //1 - 9
				} while(keyMatrix[0] * keyMatrix[3] - keyMatrix[1] * keyMatrix[2] == 0); //AD - BC = 0
				for(short i = 0; i < 2; ++i){
					subjMatrix[i] = short(name[i]);
				}
				for(short r = 0; r < 2; ++r){
					for(short c = 0; c < 2; ++c){
						resultMatrix[r] += keyMatrix[r * 2 + c] * subjMatrix[c];
					}
				}
				std::string tempStr = "";
				for(short i = 0; i < signed(name.length()); ++i){
					tempStr += (i < 2 ? char(resultMatrix[i]) : name[i]);
				}
				name = tempStr;
				std::ofstream key("LocalStorage/Key.secret");
				for(short i = 0; i < 4; ++i){
					key << (i ? "\n" : "") << keyMatrix[i];
				}
				key.close();
			}
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
		case 2: { //Matrix decryption (based on Hill Cipher) for name
			std::ifstream key("LocalStorage/Key.secret");
			std::string line;
			short keyMatrix[4], subjMatrix[2], resultMatrix[2]{0, 0};
			for(short i = 0; i < 2; ++i){
				subjMatrix[i] = short(name[i]);
			}
			try{
				if(key.is_open()){
					short index = 0;
					while(getline(key, line)){
						keyMatrix[index] = short(stoi(line));
						++index;
					}
					key.close();
				} else{
					throw("Decryption failed.");
				}
			} catch(std::string errorMsg){
				printf(errorMsg.c_str());
			}

			//Get inverse
			keyMatrix[0] += keyMatrix[3];
			keyMatrix[3] = keyMatrix[0] - keyMatrix[3];
			keyMatrix[0] -= keyMatrix[3];
			keyMatrix[1] = -keyMatrix[1];
			keyMatrix[2] = -keyMatrix[2];

			for(short r = 0; r < 2; ++r){
				for(short c = 0; c < 2; ++c){
					resultMatrix[r] += keyMatrix[r * 2 + c] * subjMatrix[c];
				}
			}
			std::string tempStr = "";
			for(short i = 0; i < signed(name.length()); ++i){
				tempStr += (i < 2 ? char(resultMatrix[i]) : name[i]);
			}
			name = tempStr;
			remove("LocalStorage/Key.secret");
			reverse(name.begin(), name.end());
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