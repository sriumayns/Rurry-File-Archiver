#ifndef TREE_ITERATIF_H
#define TREE_ITERATIF_H

#include <list>
#include <string>
#include "byte_pattern_reader.h"

class nodetreex{
public:
	//SPECIAL ID
	//NYT_node = N
	//Daun = L
	//Bukan Daun dan Bukan Root = P
	//Root awal = R	
	
	//Konstruktor-Destruktor untuk kelas nodetree
	nodetreex();
	nodetreex(char c);
	nodetreex(const nodetreex& T);
	~nodetreex();
	nodetreex& operator= (const nodetreex& T);

	//OPERASI DASAR
	
	//Getter
	_BYTE getByte();
	nodetreex* getLeft();
	nodetreex* getRight();
	long getWeight();
	char getId();
	nodetreex* getParent();
	
	//Getter Spesial. Untuk mengetahui kedalaman simpul
	short getlevel(nodetreex& T);
	
	//Increment weight
	void incrementWeight();
	
	//Setter
	void setByte(_BYTE bc);
	void setid(char c);
	void setRight(nodetreex* ptr);
	void setLeft(nodetreex* ptr);
	void setweight(long i);
	void setParent(nodetreex* ptr);
	
	//Informasi
	int hasOnlyLeftChild();
	int hasOnlyRightChild();
	int hasNoChild();
	int hasThisByte(_BYTE& bc);
	
	//Searching
	nodetreex* searchTree(_BYTE bc);
	nodetreex* searchid(char idx);

	//Tetangga
	nodetreex* getLeftestNeighbour();
	nodetreex* getRightestNeighbour();

	//Node paling kanan/kiri di suatu kedalaman
	nodetreex* getLeftestLevel(short lvl);
	nodetreex* getRightestLevel(short lvl);

	//Mendapatkan string
	string getString(char C);
	
	//I.S. berada di node NYT_node
	/*
		Spawn_child: menghasilkan dua buah anak, anak kanan
		dan anak kiri. Anak kanan adalah node yang berisi byte 
		yang menjadi parameter dan NYT_node dipindahkan menjadi
		anak kiri.
	*/
	virtual void spawnChild(_BYTE b);
	
	//Harus dipanggil oleh root.
	void PlusParent();

	//Hanya rencana.
	void PrintTree();
	
protected:
	
	//Atribut Pohon
	_BYTE b;
	unsigned char id;
	nodetreex* left;
	nodetreex* right;
	long weight;
	nodetreex* parent;
};

class tree_iter : public nodetreex{
public:
	
	//KONSTRUKTOR-DESTRUKTOR
	tree_iter();

	//UPDATING TREE
	tree_iter& update(char C, string& hasil, int& sinyal);

	//GETTER
	nodetreex* getNYTnode();
	nodetreex* getRoot();

	//Menghapus Node NYT
	//HANYA DILAKUKAN DI AKHIR
	void deleteNYT();

	//Modifiers

	//Menukar Node
	void swapNodeTree(nodetreex& srcNode, nodetreex& destNode);
	//Menambah weight node
	void incrementWeightNode(nodetreex& T);
	//Spawn pertama yang harus dipanggil root untuk karakter pertama
	void spawnChild(_BYTE b);
	
protected:
	
	//Metode untuk set NYT node.
	void setNYTnode();
	
	//Atribut Manipulator
	nodetreex* root;
};
#endif
