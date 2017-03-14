
#include "decompressor.h"

//KONSTRUKTOR
//konstruk decompressor dengan masukan sebuah string nama file
decompressor::decompressor(string file_name) {
	this->in_filename = file_name;
	//Tidak dilakukan inisialisasi ofstream karena nantinya akan berubah-ubah

	//Inisialisasi reader
	this->infile.open(this->in_filename, ios::binary);

	//Inisialisasi pohon
	this->tree_root = new tree_iter();
	this->tree_crawler = this->tree_root->getRoot();

	this->buffer_byte = new char[8];
	for (int i = 0; i < 8; i++) this->buffer_byte[i] = 0;
	this->buffer_capacity = 0;

	//Inisialisasi shifter
	this->shifter = 7;

	this->start();
}

//start: untuk memulai proses dekompresi
void decompressor::start() {
	//Baca header
	this->readHeader();
	this->readBody();
}

//getBit: mengembalikn bit dari current_byte
char decompressor:: getBit() {
	char _temp = this->current_byte;
	_temp = (_temp >> this->shifter) & 1;
	return _temp;
}

char decompressor::getBit_Ch(char a) {
	char _temp = a;
	_temp = (_temp >> this->shifter) & 1;
	return _temp;
}

//flush: menuliskan a ke dalam file
void decompressor::flush(char a) {
	this->outfile << a;
}

//checkTree: mengembalikan id node tree dengan masukan angka (0) atau (1)
//Jika dimasukkan angka 0, maka yang dicek adalah anak sebelah kiri
//Jika yang dimasukkan angka 1, maka yang dicek adalah anak sebelah kanan
//dari tree_crawler. Posisi Tree_crawler dipindahkan ke nodetree yang dicek
char decompressor::check_tree_child(char _in) {
	char _id = '\0';
	if (_in == 0) {
		if (this->tree_crawler->getLeft() != NULL) {
			_id = this->tree_crawler->getLeft()->getId();
			this->tree_crawler = this->tree_crawler->getLeft();
		}
	}
	else if (_in == 1) {
		if (this->tree_crawler->getRight() != NULL) {
			_id = this->tree_crawler->getRight()->getId();
			this->tree_crawler = this->tree_crawler->getRight();
		}
	}
	return _id;
}

//Kembalikan posisi tree_crawler ke root
void decompressor::reset_tree_crawler() {
	this->tree_crawler = this->tree_root->getRoot();
}

//readHeader: membaca header file. Posisi pembacaan dikembalikan ke posisi awal file
//File harus terbuka
void decompressor::readHeader() {
	this->infile.seekg(ios::beg);
	char _dump;
	this->infile >> this->header_size;
	this->infile >> _dump;
	this->infile >> this->num_of_file;
	this->infile >> _dump;

	this->compressed_file_name = new string[this->num_of_file];
	int i = 0;

	//Baca banyaknya string nama file
	while (i < this->num_of_file) {
		this->infile >> _dump;
		if (_dump != '|') { //'|' delimiter
			this->compressed_file_name[i].push_back(_dump);
		}
		else {
			i++;
		}
	}

	this->compressed_file_size = new long long[this->num_of_file];
	//Baca banyaknya size file terkompresi
	for (i = 0; i < this->num_of_file; i++) {
		this->infile >> this->compressed_file_size[i];
		this->infile >> _dump;
	}
	//Baca dummy
	this->infile >> this->dummy_bit;
	this->infile >> _dump;
	this->infile.close();
}

//untuk offset body
long long decompressor::calculate_offset(int _i) {
	long long offset = this->header_size;
	for (int i = _i; i > 0; i--) {
		offset = offset + this->compressed_file_size[i];
	}
	return offset;
}

//Prekondisi: infile harus terbuka
void decompressor::readCurrentByte() {
	this->infile >> noskipws >> this->current_byte;
	if (this->infile.eof()) this->infile.close();
}

//Hmm Read buffer
void decompressor::readBufferByte() {
	char _temp;
	if (!this->infile.eof()) {
		this->infile >> noskipws >> _temp;
		//untuk kali ini, ubah-ubah shifter. Nanti balikin lagi shifternya = 7
		this->shifter = 7;
		for (int i = 0; i < 8; i++) {
			this->buffer_byte[i] = this->getBit_Ch(_temp);
			this->shifter--;
		}
		this->shifter = 7;
		this->buffer_capacity = 8;
		if (this->infile.eof()) this->infile.close();
	}
}

//Hmm buffer empty
int decompressor::isBufferEmpty() {
	return this->buffer_capacity == 0;
}
//readbody: membaca body. Posisi pembacaan dikembalikan ke posisi awal body
void decompressor::readBody() {
	for (int i = 0; i < this->num_of_file; i++) {
		long long offset = calculate_offset(i);
		this->infile.open(this->in_filename, ios::binary);
		this->infile.seekg(offset, ios::beg);

		/*copy file ke sebuah temporary file*/
		ofstream out_temp(this->compressed_file_name[i] + "_temp.txt", ios::binary | ios::app);
		char _temp; int size_counter;
		this->infile >> noskipws >> _temp;
		out_temp << _temp;
		size_counter = 1;
		while (size_counter < this->compressed_file_size[i]) {
			this->infile >> noskipws >> _temp;
			out_temp << _temp;
			size_counter++;
		}
		out_temp.close();
		this->infile.close();
	}
	for (int i = 0; i < this->num_of_file - 1; i++) {
		//baca dari file hasil copy
		this->infile.open(this->compressed_file_name[i] + "_temp.txt", ios::binary);
		this->outfile.open("_bd" + this->compressed_file_name[i], ios::binary);
		this->readCurrentByte();
		if (this->infile.is_open())
			this->readBufferByte();

		//Pembacaan pertama kali
		this->tree_root->spawnChild(this->current_byte);
		this->flush(this->current_byte);
		this->current_byte = this->current_byte << 8;
		this->get_bit_stream(8);
		if (this->infile.is_open() && this->isBufferEmpty()) this->readBufferByte();

		while (this->infile.is_open()) {
			this->parse_current_byte();
		}
		this->infile.close();
		this->outfile.close();
	}

	//untuk terakhir kali:
	//baca dari file hasil copy
	int i = this->num_of_file - 1;
	this->infile.open(this->compressed_file_name[i] + "_temp.txt", ios::binary);
	this->outfile.open("_bd" + this->compressed_file_name[i], ios::binary);
	this->readCurrentByte();
	if (this->infile.is_open())
		this->readBufferByte();

	//Pembacaan pertama kali
	this->tree_root->spawnChild(this->current_byte);
	this->flush(this->current_byte);
	this->current_byte = this->current_byte << 8;
	this->get_bit_stream(8);
	if (this->infile.is_open() && this->isBufferEmpty()) this->readBufferByte();

	while (this->infile.is_open()) {
		this->parse_current_byte();
	}

	//Dicopy paste karena disini ada penanganan dummy
	this->parse_current_byte('b');

	this->infile.close();
	this->outfile.close();

	//Remove semua file temporary
	string filename_destroy;
	for (int i = 0; i < this->num_of_file; i++) {
		filename_destroy = this->compressed_file_name[i] + "_temp.txt";
		remove(filename_destroy.c_str());
	}
}


void decompressor::operate_tree(char _tree_id) {
	char _temp;
	string str_dump; int s_dump;
	if (_tree_id == 'N') {
		//Karena ini adalah NYT node, maka bisa dipastikan bacaan bit berikutnya
		//adalah 1, karena ketika spawn di bawah NYT node, bit, yang dimasukkan
		//selalu ditaruh ke kanan. 
		this->refresh_bit();
		this->tree_root->update(this->current_byte, str_dump, s_dump);
		this->flush(current_byte);
		this->current_byte = 0;
		this->get_bit_stream(8);
		this->reset_tree_crawler();
	}
	else if (_tree_id == 'P') {
		do {
			//terus "parse" untaian bit sampai tree_id bukan P
			_temp = this->getBit();
			_tree_id = this->check_tree_child(_temp); 
			this->refresh_bit();
		} while (_tree_id == 'P');
		//Karena _tree_id sudah tidak mungkin P, mari panggil prosedur ini lagi
		this->operate_tree(_tree_id);
	}
	else if (_tree_id == 'L') {
		this->flush(this->tree_crawler->getByte());
		this->tree_root->update(this->tree_crawler->getByte(), str_dump, s_dump);
		this->reset_tree_crawler();
	}
}

//refresh_bit:: "memajukkan" pita bit menggunakan kondisi current_byte dan buffer_byte
void decompressor::refresh_bit() {
	this->current_byte = this->current_byte << 1;
	this->get_bit_stream(1);
}

void decompressor::parse_current_byte(char _mode) {
	char _bit;
	char _tree_id;
	if (_mode == 'a') {
		_bit = this->getBit();
		this->refresh_bit();
		//cek pohon berdasarkan _bit
		_tree_id = this->check_tree_child(_bit);

		this->operate_tree(_tree_id);
	}
	else { //mode dummy!
		//cari bit yang paling terakhir
		if (this->buffer_capacity > 0) {
			//artinya bit terakhir ada di buffer
			if (this->dummy_bit <= this->buffer_capacity) {
				int _T = this->buffer_capacity - this->dummy_bit;
				for (int i = _T; i < this->buffer_capacity; i++) {
					this->buffer_byte[i] = 0;
				}
				this->buffer_capacity = this->buffer_capacity - this->dummy_bit;
			}
			else {
				for (int i = 0; i < this->buffer_capacity; i++) {
					this->buffer_byte[i] = 0;
				}
				//berarti juga harus membuang dummy bit yang ada di current byte
				char cb_shift = this->dummy_bit - this->buffer_capacity;
				this->buffer_capacity = 0;
				this->current_byte = (this->current_byte >> cb_shift) << cb_shift;
			}
		} //gimana kalo kapasitasnya udah 0?
		while (this->current_byte != 0) {
			this->parse_current_byte('a');
		}
	}
}


//dapetin bit stream untuk current byte dari byte_buffer
void decompressor::get_bit_stream(int len) {
	len = len - 1;
	while (len >= 0) {
		//jika kosong maka isi dulu.
		if (this->isBufferEmpty() && this->infile.is_open())
			this->readBufferByte();

		double t = 2;
		this->current_byte = this->current_byte + (pow(t, len))*this->buffer_byte[0];

		//geser buffer_byte sebanyak 1 ke kiri
		this->shift_buffer(1);

		len--;
	}
}

void decompressor::shift_buffer(int len) {
	for (int i = 0; i < (8 - len); i++)
		this->buffer_byte[i] = this->buffer_byte[i + len];
	for (int i = (8 - len); i < 8; i++)
		this->buffer_byte[i] = 0;
	this->buffer_capacity = this->buffer_capacity - len;
	if(this->isBufferEmpty() && this->infile.is_open()) this->readBufferByte();
}
/*private:
	string in_filename; //nama file yang akan dikompresi

	int header_size;
	int num_of_file; //banyaknya file yang ada di dalam kompresi
	string* compressed_file_name; //nama file-file yang ada di dalam kompresi
	long long* compressed_file_size; //besar file-file yang ada di dalam kompresi
	int dummy_bit; //baanyaknya dummy bit

	int shifter;
	char current_byte; //ini byte yang masih terencode
	char buffer_byte;
	char buffer_capacity;

	tree_iter* tree_root; //pencatat alamat root tree
	tree_iter* tree_crawler; //crawler tree, gunanya supaya tree dapat ditelusuri
	
	ifstream infile;
	ofstream outfile;*/