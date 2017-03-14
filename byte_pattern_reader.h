#ifndef BYTE_PATTERN_READER_H
#define BYTE_PATTERN_READER_H

#include <cstdio>
#include <fstream>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

typedef char _BYTE;
typedef ifstream INFILE;

class byte_pattern_reader {
public:
	//Konstruktor
	byte_pattern_reader(const char* str = NULL);

	//Baca dari file yang ditentukan
	//Mengembalikan 0 jika gagal dibuka
	int openFile(const char* filename);

	void openFileAndRead(const char* filename);

	//Mengembalikan pola bit saat ini
	_BYTE getCurrentByte();

	//Membaca pola bit berikutnya
	//PREKONDISI harus sudah dicek EOF-nya
	_BYTE getNextByte();

	//Mengembalikan byte count
	int getByteCount();

	//Mengembalikan besar file
	long long  getFileSize();

	//Menutup file yang dibuka
	void closeFile();

	//Mengembalikan hasil interpretasi byte sebagai biner dalam bentuk string
	string getBinaryString();

	//Cek eof
	bool isEOF();

private:
	_BYTE byteptrn;
	long bytecounter;
	streampos file_size;
	INFILE fin;
};
#endif