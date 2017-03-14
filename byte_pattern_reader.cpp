#include "byte_pattern_reader.h"
#include "symbol_list.h"
#include <ios>

using namespace std;

byte_pattern_reader::byte_pattern_reader(const char* str) {
	if (str != NULL) {
		//buka file, baca dalam mode binary
		if (this->openFile(str)) {
			//file terbuka, dapatkan size dulu
			this->fin.seekg(0, ios::end);
			file_size = this->fin.tellg();
			//baca pola bit pertama
			this->fin.seekg(0, ios::beg);
			this->fin.get(this->byteptrn);
		}
		else cout << "Unable to open file " << str << endl;
	}
}

int byte_pattern_reader::openFile(const char* filename) {
		if (filename != NULL) {
			this->fin.open(filename, ios::in | ios::binary);
			if (this->fin.bad()) return 0;
			else return 1;
		}
		else return 0;
}

void byte_pattern_reader::openFileAndRead(const char* filename) {
	int valid = this->openFile(filename);
	if (valid) {
		this->fin.seekg(0, ios::end);
		this->file_size = this->fin.tellg();
		//baca pola bit pertama
		this->fin.seekg(0, ios::beg);
		this->fin.get(this->byteptrn);
	}
}

_BYTE byte_pattern_reader::getCurrentByte() {
	return this->byteptrn;
}

//PREKONDISI harus sudah dicek EOF-nya
_BYTE byte_pattern_reader::getNextByte() {
	this->fin >> std::noskipws >> (this->byteptrn);
	this->bytecounter++;
	return this->byteptrn;
}

bool byte_pattern_reader::isEOF() {
	return this->fin.eof();
}

int byte_pattern_reader::getByteCount() {
	return this->bytecounter;
}

long long byte_pattern_reader::getFileSize() {
	return static_cast<long long>(this->file_size);
}

void byte_pattern_reader::closeFile() {
	this->fin.close();
}
string byte_pattern_reader::getBinaryString() {
	//Ubah CURRENT BYTE menjadi sebuah string
	/*Deprecated
	char* binarystr = new char[9];
	for (int i = 0; i < 9; i++) {
		binarystr[i] = '\0';
	}
	if (iterator > 256) {
		for (int i = iterator; i >= 0; i--) {
			int npot = pow(2, i); //npot:nearest power of two
			if (byte_int - npot >= 0) {
				binarystr = strcat(binarystr, "1");
			}
			else {
				binarystr = strcat(binarystr, "0");
			}
		}
	}
	*/
	return bitCharToStr(this->byteptrn);
}

/*TODO testing.
_BYTE byteptrn;
long bytecounter;
streampos file_size;
INFILE fin;*/