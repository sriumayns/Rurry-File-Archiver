
#include "symbol_list.h"
using namespace std;

/*NOTE TO MYSELF
char* symbol_id;
symbol_list* head;
symbol_list* next;*/

//gatau dah ini objek buat apaan

//KONSTRUKTOR
/*symbol_list::symbol_list(char* _str) {
	/*Deprecated
	if (_str != NULL) {
		//Copy string ke simbol_id
		int i = 0;
		do {
			this->*(symbol_id + i) = new char;
			this->*(symbol_id + i) = *(_str + i);
			i++;
		} while (*(_str + i) != NULL && i < 8);
		//NULL terminating string
		this->*(symbol_id + i) = new char;
		this->*(symbol_id + i) = '\0';
	}
	else this->symbol_id = NULL;
	this->symbol_id = string(_str);
	this->head = this;
	this->next = NULL;
}
symbol_list::symbol_list(string str) {
	this->symbol_id = str;
	this->head = this;
	this->next = NULL;
}

//DEKONSTRUKTOR
symbol_list::~symbol_list() {
	delete[] this->next;
	delete[] this->head;
}

//Operasi dasar

//pushBack: Tambah satu elemen list di paling belakang
void symbol_list::pushBack(char* _str) {
	//alokasi elemen baru
	this->next = new symbol_list(_str);
}
void symbol_list::pushBack(string str) {
	this->next = new symbol_list(str);
}

//Copy Constructor
symbol_list& symbol_list::operator=(const symbol_list& L) {
	this->symbol_id = L.getSymbol;
	symbol_list* P = L.head;
	symbol_list* L_this = this;
	while (P->next != NULL) {
		L_this->pushBack(P->next->getSymbol);
		P = P->next;
		L_this = L_this->next;
	}
}

//prev:: mengembalikan elemen list sebelum _el. Jika tidak ada
//mengembalikan NULL.
symbol_list* symbol_list::prev(symbol_list* _el) {
	symbol_list* P = this->head;
	unsigned short found = 0;
	while ((P->next != NULL) && (!found)) {
		if (P->next == _el) {
			found = 1;
		}
		else P = P->next;
	}
	//antara P->next = null atau found
	if (found) return P;
	else return NULL;
}

//delete1: delete sebuah elemen list yang ditentukan
//Prekond: el pasti ada di list
void symbol_list::delete1(symbol_list* el) {
	//dapetin elemen list sebelum el
	symbol_list* P = this->prev(el);
	//pointer diubah-ubah
	if (P != NULL) {
		P->next = el->next;
	}
	else {
		//bisa jadi dia elemen pertama
		if (el == this->head) {
			//majuin head
			this->head = this->next;
		}
		//else, dia jadi elemen paling belakang
		//ga usah ngapa-ngapain?
	}	
	//delete el
	delete[] el;
}

//operator overload +, konkat list ini dengan list L
//List L jadi masih bisa dibedain?
symbol_list symbol_list:: operator+ (symbol_list L) {
	//copy dulu si L
	symbol_list list_copy = L;
	//cari elemen terakhir this
	symbol_list *P = this->head;
	while (P != NULL) {
		P = P->next;
	}
	P->next = list_copy.head;
}

//update: update semua elemen list yang mempunyai symbol id
//_X dengan simbol id _Y
void symbol_list::update(char* _X, char* _Y) {
	symbol_list* L = this->head;
	while (L != NULL) {
		if (L->symbol_id.compare( _X)) {
			L->symbol_id = _Y;
		}
		L = L->next;
	}
	//udah
}

//writedown: tulis semua elemen list ini ke dalam sebuah file
//bernama _filename dengan mode: b untuk binary, t untuk txt.
void symbol_list::writedown(char* _filename, char _mode) {
	//TODO, harus ngerjain ini.
}

//fwritedown: sama seperti writedown namun list ini didelete.
void symbol_list::fwritedown(char* _filename, char _mode) {
	this->writedown(_filename, _mode);
	delete[] this;
}*/

/*Kembalikan interpretasi "pseudo-bit" yang masih dalam bentuk string ke tipe
car yang mengembalikan interpretasi bit sebenarnya*/
_BYTE bitStrToCharch(const char* _str) {
	int iter = 0;
	bool found = false;
	while (iter < 255 && !found) {
		if (!strcmp(_str, bit_table_str[iter])) found = true;
		else iter++;
	}
	if (found) {
		iter++;
		return static_cast<char>(iter);
	}
	else {
		iter = 0;
		return static_cast<char>(iter);
	}
}

_BYTE bitStrToChar(string _str) {
	_BYTE apagitu = bitStrToCharch(_str.c_str());
	return apagitu;
}

/*Kembalikan interpretasi string "pseudo-bit dari char ch*/
string bitCharToStr(const _BYTE &ch) {
	string str_rtn;
	unsigned char uch = (unsigned char)ch;
	if (uch != 0) {
		str_rtn = bit_table_str[uch - 1];
	}
	else str_rtn = "00000000";
	return str_rtn;
}