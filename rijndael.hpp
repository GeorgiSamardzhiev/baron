#ifndef RIJNDAEL_HPP
#define RIJNDAEL_HPP

#include <fstream>
#include <iostream>

namespace baron {

	//Nb -> number of columns of the state
	//Nk -> number of columns of the cipher key

	void keyExpansionCore(unsigned char* in, unsigned int i);
	void keyExpansion(unsigned char* inputKey, unsigned char* expandedKeys, short Nk = 4, short Nb = 4);
	void addRoundKey(unsigned char* state, unsigned char* roundKey, short Nb = 4);

	void subBytes(unsigned char* state, short Nb = 4);
	void shiftRows(unsigned char* state, short Nb = 4);
	void mixColumns(unsigned char* state, short Nb = 4);
	void encryptionRound(unsigned char* state, unsigned char* roundKey, short Nb = 4);
	void lastEncryptionRound(unsigned char* state, unsigned char* roundKey, short Nb = 4);
	void encryptBlock(unsigned char* message, unsigned char* expandedKey, short Nb = 4, short Nk = 4);
	void encrypt(unsigned char* message, size_t size, unsigned char* key, short Nb = 4, short Nk = 4);
	void encryptStream(std::istream& is, std::ostream& os, unsigned char* key, short Nb = 4, short Nk = 4);
	void encryptFile(const char* input, const char* output, unsigned char* key, short Nb = 4, short Nk = 4);

	void invShiftRows(unsigned char* state, short Nb = 4);
	void invSubBytes(unsigned char* state, short Nb = 4);
	void invMixColumns(unsigned char* state, short Nb = 4);
	void decryptRound(unsigned char* state, unsigned char* roundKey, short Nb = 4);
	void firstDecryptionRound(unsigned char* state, unsigned char* roundKey, short Nb = 4);
	void decryptBlock(unsigned char* message, unsigned char* expandedKey, short Nb = 4, short Nk = 4);
	void decrypt(unsigned char* message, size_t size, unsigned char* key, short Nb = 4, short Nk = 4);
	void decryptStream(std::istream & is, std::ostream & os, unsigned char* key, short Nb = 4, short Nk = 4);
	void decryptFile(const char* input, const char* output, unsigned char* key, short Nb = 4, short Nk = 4);

	unsigned char* padMessage(unsigned char* msg, size_t size, short bLen = 16);

}

#endif // !RIJNDAEL_HPP
