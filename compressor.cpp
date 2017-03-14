
#include "compressor.h"
#include <iostream>
#include <cmath>

//Konstruktor
//Harus menyebutkan nama file yang akan dibuka
compressor::compressor() {
}
compressor::compressor(char* _filenameIn) {
	reader = new byte_pattern_reader(_filenameIn);
	tree_root = new tree_iter; //disini harus ditinjau ulang
									  //ketika tree_iter udah jadi
}

compressor::compressor(string &_filenameIn) {
	this->reader = new byte_pattern_reader(_filenameIn.c_str());
	this->tree_root = new tree_iter; 

	this->tree_root->spawnChild(this->reader->getCurrentByte()); 
	//harus dicatat.
	this->_cmpressd_out.open(_filenameIn + "_bd" + ".rur", ios::binary | ios::app);
	string _str = bitCharToStr(this->reader->getCurrentByte());
	while(!_str.empty()) this->buildStrToWrite(_str);
	this->_cmpressd_out.close();

	this->reader->getNextByte();

	string* filename_array = new string[1];
	filename_array[0] = _filenameIn;

	this->start(1, filename_array);
	delete[] filename_array;
}

compressor::compressor(int filecount, string* filename_array) {
	
	this->reader = new byte_pattern_reader(filename_array[0].c_str());
	this->tree_root = new tree_iter;
	this->tree_root->spawnChild(this->reader->getCurrentByte());

	this->str_to_write = "0";
	this->_cmpressd_out.open(filename_array[0] + "_bd" + ".rur", ios::binary | ios::app);
	string _str = bitCharToStr(this->reader->getCurrentByte());
	while(!_str.empty()) this->buildStrToWrite(_str);
	this->_cmpressd_out.close();

	this->reader->getNextByte();
	this->start(filecount, filename_array);
}

//Dekonstruktor. Akibat dari perbuatan ini string nama file juga ikut terhapus
compressor::~compressor() {
	delete reader;
	delete tree_root;
}

//Mulai kompresi
void compressor::start(const int _fcount, string* arr_file_name) {
	string* outfile_array = new string[_fcount];
	long long* filesize_array = new long long[_fcount];

	this->_filename = arr_file_name[0];
	outfile_array[0] = this->_filename + "_bd" + ".rur";
	filesize_array[0] = this->start();

	//lakukan kompresi file satu persatu
	//lalu update reader
	for (int i = 1; i < _fcount; i++) {
		this->_filename = arr_file_name[i];
		//update reader.
		this->reader->openFileAndRead(this->_filename.c_str());
		outfile_array[i] = this->_filename + "_bd" + ".rur";
		filesize_array[i] = this->start();
	}

	//selesai, cek str_to_write masih sisa atau gak. Jika masih sisa, bikin bit dummy
	int dummy_bit_count = 8 - this->getStrToWrtLen();
	if (dummy_bit_count > 0 && dummy_bit_count < 8) {
		for (int i = dummy_bit_count; i > 0; i--) {
			this->str_to_write.push_back('0');
		}
		//buka lagi file yang terakhir dibuka
		this->_cmpressd_out.open(outfile_array[_fcount - 1], ios::binary | ios::app);
		this->flush();
		//tutup lagi
		this->_cmpressd_out.close();
		byte_pattern_reader last(outfile_array[_fcount - 1].c_str());
		last.closeFile();
		filesize_array[_fcount - 1] = last.getFileSize();
	}
	//buat headernya
	if (dummy_bit_count == 8) dummy_bit_count = 0;
	this->build_header(_fcount, arr_file_name, filesize_array, dummy_bit_count);
	//append semua file yag dikompresi
	this->cmpressd_filename = this->file_append(_fcount, outfile_array);
	//lalu append dengan header
	string* final_name = new string[2];
	final_name[0] = this->_header_name;
	final_name[1] = this->cmpressd_filename;
	this->cmpressd_filename = this->file_append(2, final_name);
	//selesai?
}


long long compressor:: start() {
	this->cmpressd_filename = this->_filename + "_bd" + ".rur";
	this->_cmpressd_out.open(this->cmpressd_filename, ios::binary | ios::app);
	_BYTE curr_byte = this->reader->getCurrentByte(); 
	string str_from_tr;
	int signal;

	do {
		this->tree_root->update(curr_byte, str_from_tr, signal); //update tree lagi dibuat
		//ada dua kemungkinan:
		//Pertama, kalo str_from_tr masih ada, build str_to_write lagi sampai habis.
		//Kedua, kalo str_from_tr abis, mestinya langsung append curr_byte seandainya dapet sinyal
		//ada kejadian spawn_child.
		while (!str_from_tr.empty()) this->buildStrToWrite(str_from_tr);
		if (signal == 0) {
			//cari representasi string yang pas
			string str_char = bitCharToStr(curr_byte);
			while (!str_char.empty()) this->buildStrToWrite(str_char);
		}
		curr_byte = this->reader->getNextByte();
		//cout << curr_byte << " ";
	} while (!this->reader->isEOF());

	this->_cmpressd_out.close();

	//kalkulasi besar file keluaran
	byte_pattern_reader out_size(this->cmpressd_filename.c_str());
	out_size.closeFile();
	long long sizes = out_size.getFileSize();
	
	this->reader->closeFile();
	return sizes;
}

//File append: gabungkan semua file yang disebutkan dalam array file_name
//ke dalam sebuah file master dengan memerhatikan keterurutan file. 
//File yang diappend dihapus dari komputer
//I.S. semua file dalam keadaan tertutup
string compressor::file_append(const int _file_count, string* file_name) {
	ofstream fappend(file_name[0], ios::binary | ios::app);
	ifstream fread;
	char temp;

	for (int i = 1; i < _file_count; i++) {
		fread.open(file_name[i], ios::binary | ios::beg);
		//baca karakter dari fread, tulis ke fappend

		fread >> std::noskipws >> temp;
		bool aadc = fread.eof();
		while (!aadc) {
			fappend << temp;
			fread >> std::noskipws >> temp;
			aadc = fread.eof();
		}
		fread.close();
	}

	//delete file dari file_name[1] sampai habis
	for (int i = 1; i < _file_count; i++) {
		remove(file_name[i].c_str());
	}

	//tutup file append
	fappend.close();
	return file_name[0];
}


void compressor::build_header(const int _file_count, string* file_name, long long* file_size, const int& dummy_count) {
	string header_temp; //header sementara untuk menyimpan data-data input
						//nantinya akan digabung dengan file yang isinya size dari header ini
	header_temp =  "header_temp.headtmp";
	ofstream fheaderout;
	fheaderout.open(header_temp, ios::binary | ios::beg);
	
	fheaderout << '|';

	//tulis banyaknya file yang ada di body
	fheaderout << _file_count;
	fheaderout << '|';

	//tulis nama-nama file yang disebutkan
	for (int i = 0; i < _file_count; i++) {
		fheaderout << file_name[i];
		fheaderout << '|';
	}
	

	//tulis besar fil masing-masing secara berurutan
	for (int i = 0; i < _file_count; i++) {
		fheaderout << file_size[i];
		fheaderout << '|';
	}

	//tulis banyaknya dummy bit yang digunakan
	fheaderout << dummy_count;
	fheaderout << '|';

	//hitung besar file header temp ini
	fheaderout.close();
	byte_pattern_reader fheaderchecksize(header_temp.c_str());
	long double size = fheaderchecksize.getFileSize();
	fheaderchecksize.closeFile();
	//diasumsikan panjang header ga banyak banyak amat
	long double b = 10;
	int size_length = ceil(log(size + 1) / log(b));

	//tulis besar file size header_temp ini ke file header sesungguhnya + 4
	//karena tipe data integer
	this->_header_name = file_name[0] + "_head_final.rur";
	fheaderout.open(this->_header_name, ios::binary | ios::beg);
	fheaderout << size + size_length;
	fheaderout.close();

	//bentuk sebuah string yang isinya nama header temp dan nama sesungguhnya
	string* header_arr = new string[2];
	header_arr[0] = this->_header_name;
	header_arr[1] = header_temp;

	//append semua file
	this->_header_name = file_append(2, header_arr);
	delete[] header_arr;
}

//Dapetin waktu yang dibutuhkan untuk kompres seluruh file
time_t compressor::get_elapsed_time() {
	return static_cast<time_t>(difftime(time_begin, time_finished));
}

//Masukkan untaian bit str_to_write ke file. 
//I.S. panjang harus pas 8 karakter
//F.S. file diappend dengan representasi char yang tepat dari str_to_write
void compressor::flush() {
	//cout << this->str_to_write << " ";
	_BYTE toWrite = bitStrToChar(this->str_to_write);
	this->_cmpressd_out << toWrite;
	this->str_to_write.erase(this->str_to_write.begin(), this->str_to_write.end());
}

//Buat string yang isinya pas 8 karakter untuk di"flush" ke file kalo bisa
//Kembalikan string sisanya jika ada. String didapat dari hasil 
//interpretasi pohon huffman 'tree_root'. F.S. jika panjang str_to_write masih kurang
//, kembalikan empty string, string belum di flush ke file
//jika panjang sudah cukup, kembalikan sisa string dari huffman dan flush str_to_write
//file
void compressor::buildStrToWrite(string& _str) {

	if (this->getStrToWrtLen() >= 8) {
		//hapus string, ready to be rewritten
		this->str_to_write.erase(this->str_to_write.begin(), this->str_to_write.end());
		//cek string dari huffman
		if (_str.length() > 8) {
			while (this->getStrToWrtLen() < 8) {
				this->str_to_write.push_back(_str.front());
				_str.erase(_str.begin(), _str.begin()+1);
			}
			this->flush();
		}
		else if (_str.length() <= 8) {
			this->str_to_write = _str;
			if(_str.length() == 8){
				this->flush();
			}
			_str.erase(_str.begin(), _str.end());
		}
	}
	else {
		//berarti append karakter satu-satu ke str_to_write sampai lengthnya = 8 
		//jika memungkinkan
		while (this->getStrToWrtLen() < 8 && !_str.empty()) {
			this->str_to_write.push_back(_str.front());
			_str.erase(_str.begin(), _str.begin() + 1);
		}//keluar loop, str_to_write length = 8 atau str_from_tree kosong
		if (this->getStrToWrtLen() == 8) {
			this->flush();
		}
	}
}

int compressor::getStrToWrtLen() {
	return this->str_to_write.size();
}

//GETTER. Udah didefinisikan

/*
string _filename;
string cmpressd_filename;
ofstream _cmpressd_out;
string _header_name;
tree_iter* tree_root;
byte_pattern_reader* reader;
string str_to_write;
time_t time_begin;
time_t time_finished;*/