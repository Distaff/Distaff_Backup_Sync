#pragma once
#include <string>
#include <openssl/md5.h>

const char HEX_LOOKUP[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

class md5_t {
	uint8_t data[MD5_DIGEST_LENGTH];
public:
	std::string to_string() {
		std::string res = "";
		for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
			res += HEX_LOOKUP[0b00001111 & this->data[i]];
			res += HEX_LOOKUP[(0b11110000 & this->data[i]) >> 4];
		}
	}
	//md5_t operator=(md5_t& rhs) {
	//	this->data[0]
	//}
};