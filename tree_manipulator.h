#ifndef TREE_MANIPULATOR_H
#define TREE_MANIPULATOR_H

#include <list>
#include <string>
#include "byte_pattern_reader.h"

using namespace std;

class nodetree{
public:
	//SPECIAL ID
	//NYT_node = N
	//Daun = L
	//Bukan Daun dan Bukan Root = P
	//Root awal = R	
	
	//Konstruktor-Destruktor untuk kelas nodetree
	nodetree();
	nodetree(char c);
	nodetree(const nodetree& T);
	~nodetree();
	nodetree& operator= (const nodetree& T);

	//OPERASI DASAR
	
	//Getter
	_BYTE getByte();
	nodetree* getLeft();
	nodetree* getRight();
	long getWeight();
	char getId();
	
	//Getter Spesial. Untuk mengetahui kedalaman simpul
	short getlevel(nodetree& T);
	
	//Increment weight
	void incrementWeight();
	
	//Setter
	void setByte(_BYTE bc);
	void setid(char c);
	void setRight(nodetree* ptr);
	void setLeft(nodetree* ptr);
	void setweight(long i);
	
	
	//Informasi
	int hasOnlyLeftChild();
	int hasOnlyRightChild();
	int hasNoChild();
	int hasThisByte(_BYTE& bc);
	
	//Searching
	nodetree* searchTree(_BYTE bc);
	nodetree* searchid(char idx);
	nodetree* searchParent(nodetree* P);

	//Tetangga
	nodetree* getLeftestNeighbour(nodetree* root);
	nodetree* getRightestNeighbour(nodetree* root);

	//Node paling kanan/kiri di suatu kedalaman
	nodetree* getLeftestLevel(short lvl);
	nodetree* getRightestLevel(short lvl);

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
	void PlusParent(nodetree& T);

	//Hanya rencana.
	void PrintTree();
	
protected:
	
	//Atribut Pohon
	_BYTE b;
	unsigned char id;
	nodetree* left;
	nodetree* right;
	long weight;
};

class tree_manipulator : public nodetree{
public:
	
	//KONSTRUKTOR
	tree_manipulator();

	//UPDATING TREE
	tree_manipulator& update(char C, string& hasil, int& sinyal);

	//GETTER
	nodetree* getNYTnode();
	nodetree* getRoot();

	//Menghapus Node NYT
	//HANYA DILAKUKAN DI AKHIR
	void deleteNYT();

	//Modifiers

	//Menukar Node
	void swapNodeTree(nodetree& srcNode, nodetree& destNode);
	//Menambah weight node
	void incrementWeightNode(nodetree& T);
	//Spawn pertama yang harus dipanggil root untuk karakter pertama
	void spawnChild(_BYTE b);
	
protected:
	
	//Metode untuk set NYT node.
	void setNYTnode();
	
	//Atribut Manipulator
	nodetree* root;
};
#endif
