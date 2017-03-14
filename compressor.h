#ifndef COMPRESOR_H
#define COMPRESOR_H

#include "byte_pattern_reader.h"
#include "tree_iter.h" //tunggu jadi dulu
#include "symbol_list.h"
#include <ctime>

using namespace std;

class compressor{
public:
	//Konstruktor
	//Harus menyebutkan nama file yang akan dibuka
	compressor();
	compressor(char* _filename);
	compressor(string &_filename);
	compressor(int filecount, string* filename_array);

	//Dekonstruktor
	~compressor();

	//Mulai kompresi
	//_fcount: banyaknya file yang akan dikompresi, 
	//arr_file_name: array string nama file yang dikompresi
	void start(const int _fcount, string* arr_file_name);

	time_t get_elapsed_time();
	
	//Buat string yang isinya pas 8 karakter untuk di"flush" ke file
	//Kembalikan string sisanya jika ada
	void buildStrToWrite(string& _str_from_tree);

	//Getter
	string getFileName() {
		return this->_filename;
	}
	string getCompressedFileName() {
		return this->cmpressd_filename;
	}
	tree_iter* getTreeRoot() {
		return this->tree_root;
	}
	byte_pattern_reader* getReader() {
		return this->reader;
	}
	string getStringToWrite() {
		return this->str_to_write;
	}
	int getStrToWrtLen();

	void build_header(const int _file_count, string* file_name, long long* file_size, const int& dummy_count);

	string file_append(const int _file_count, string* file_name);
	
	string getFileCompressedName() { return this->cmpressd_filename; }
private:
	//Kembalikan size file output
	long long start();

	//Masukkan untaian bit ke file
	void flush();

	string _filename;
	string cmpressd_filename;
	ofstream _cmpressd_out;
	string _header_name;

	tree_iter* tree_root;
	byte_pattern_reader* reader;

	string str_to_write;
	time_t time_begin;
	time_t time_finished;
};

#endif
