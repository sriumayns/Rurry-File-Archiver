#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H
#include <string>
#include <fstream>
#include "byte_pattern_reader.h"
#include "tree_iter.h"
#include <cmath>
#include <ios>

class decompressor {
public:
	//KONSTRUKTOR
	//konstruk decompressor dengan masukan sebuah string nama file
	decompressor(string file_name);

	//start: untuk memulai proses dekompresi
	void start(); 

	//getBit: mengembalikn bit dari current_byte
	char getBit();

	//flush: menuliskan latest_decoded_byte ke dalam file
	void flush(char a);

	//checkTree: mengembalikan id node tree dengan masukan angka (0) atau (1)
	char check_tree_child(char _in);

	//readHeader: membaca header file. Posisi pembacaan dikembalikan ke posisi awal file
	void readHeader();

	//readbody: membaca body. Posisi pembacaan dikembalikan ke posisi awal body
	void readBody();

	//Kembalikan posisi tree_crawler ke root
	void reset_tree_crawler();

	//Parse current byte
	void parse_current_byte(char _mode = 'a');

	//append_byte, untuk "mengambil" bit terdepan byte_2 lalu dijumlahkan 
	void get_bit_stream(int len);

	long long calculate_offset(int _i);

	void readCurrentByte();
	void readBufferByte();
	void refresh_bit();

	/*Operasikan tree berdasarkan input (N, P, L). Jika terjadi pembaruan pohon, maka yang 
	dimasukkan sebagai karakter dalam pohon adalah this->current_byte*/
	void operate_tree(char _tree_id);

	int isBufferEmpty();
	char getBit_Ch(char a);

	//geser buffer ke kiri sebanyak len
	void shift_buffer(int len);
private:
	string in_filename; //nama file yang akan dikompresi

	int header_size;
	int num_of_file; //banyaknya file yang ada di dalam kompresi
	string* compressed_file_name; //nama file-file yang ada di dalam kompresi
	long long* compressed_file_size; //besar file-file yang ada di dalam kompresi
	int dummy_bit; //baanyaknya dummy bit

	int shifter;
	char current_byte; //ini byte yang masih terencode
	char* buffer_byte;
	char buffer_capacity;

	tree_iter* tree_root; //pencatat alamat root tree
	nodetreex* tree_crawler; //crawler tree, gunanya supaya tree dapat ditelusuri

	ifstream infile;
	ofstream outfile; 
};
#endif