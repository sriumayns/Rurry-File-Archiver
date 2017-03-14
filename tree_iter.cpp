
#include "tree_iter.h"
#include <iostream>

using namespace std;

//-----------------------------------------------------------------------------------------------//
//                                           NODETREEX                                           //
//-----------------------------------------------------------------------------------------------//

// Konstruktor-Destruktor kelas nodetreex
nodetreex :: nodetreex(){
	b = 0;
	weight = 0;
	left = NULL;
	right = NULL;
	id = 'L';
	parent = NULL;
}

nodetreex :: nodetreex(char c){
	b = 0;
	weight = 0;
	left = NULL;
	right = NULL;
	id = c;
	parent = NULL;
}

nodetreex :: nodetreex(const nodetreex& T){
	left = T.left;
	right = T.right;
	id = T.id;
	b = T.b;
	weight = T.weight;
	parent = T.parent;
}

nodetreex :: ~nodetreex(){
	if(this->left != NULL){
		this->left->setParent(NULL);
	}
	if(this->right != NULL){
		this->right->setParent(NULL);
	}
	delete left;
	delete right;
}
	
nodetreex& nodetreex :: operator= (const nodetreex& T){
	left = T.left;
	right = T.right;
	id = T.id;
	b = T.b;
	weight = T.weight;
	parent = T.parent;
	return *this;
}

// Operasi Dasar Kelas Tree

// Getter

_BYTE nodetreex :: getByte(){
	return b;
}

nodetreex*  nodetreex :: getLeft(){
	return left;
}

nodetreex*  nodetreex :: getRight(){
	return right;
}

long nodetreex :: getWeight(){
	return weight;
}

char nodetreex :: getId(){
	return id;
}

nodetreex* nodetreex :: getParent(){
	return parent;
}

// Getter Spesial. Untuk mengetahui kedalaman simpul
short nodetreex :: getlevel(nodetreex& T){
	if(this == &T){
		return 0;
	} else {
		if(this->left->searchTree(T.b) != NULL){
			return 1 + this->left->getlevel(T);
		} else if(this->right->searchTree(T.b) != NULL){
			return 1 + this->right->getlevel(T);
		}
	}
}

// Increment weight	
void nodetreex :: incrementWeight(){
	weight++;
}

// Setter
	
void nodetreex :: setByte(_BYTE bc){
	b = bc;
}

void nodetreex :: setid(char c){
	id = c;
}

void nodetreex :: setLeft(nodetreex* ptr){
	left = ptr;
}

void nodetreex :: setRight(nodetreex* ptr){
	right = ptr;
}

void nodetreex :: setweight(long i){
	weight = i;
}

void nodetreex :: setParent(nodetreex* ptr){
	parent = ptr;
}
	
// Informasi anak dan isi node

int nodetreex :: hasOnlyLeftChild(){
	return this->right == NULL && this->left != NULL;
}

int nodetreex :: hasOnlyRightChild(){
	return this->left == NULL && this->right != NULL;
}

int nodetreex :: hasNoChild(){
	return this->left == NULL && this->right == NULL;
}
	
int nodetreex :: hasThisByte(_BYTE& bc){
	return this->b == bc;
}

// Searching
	
nodetreex* nodetreex :: searchTree(_BYTE bc){
	nodetreex* x;
	if(this->getId() == 'N'){
		return NULL;
	} else if(this->hasThisByte(bc) && this->getId() == 'L'){
		return this;
	} else {
		if(this->right != NULL){
			if(this->left != NULL){
				x = this->left->searchTree(bc);
				if(x!= NULL){
					return x;
				} else {
					x = this->right->searchTree(bc);
					if(x != NULL){
						return x;
					} else {
						return NULL;
					}
				}
			} else {
				return this->right->searchTree(bc);
			}
		} else {
			if (this->left != NULL){
				return this->left->searchTree(bc);
			} else {
				return NULL;
			}
		}
	}
}
	
nodetreex* nodetreex :: searchid(char idx){
	nodetreex* x;
	if(this->id == idx){
		return this;
	} else {
		if(this->right != NULL){
			if(this->left != NULL){
				x = this->left->searchid(idx);
				if(x!= NULL){
					return x;
				} else {
					x = this->right->searchid(idx);
					if(x != NULL){
						return x;
					} else {
						return NULL;
					}
				}
			} else {
				return this->right->searchid(idx);
			}
		} else {
			if (this->left != NULL){
				return this->left->searchid(idx);
			} else {
				return NULL;
			}
		}
	}
}	

// Tetangga
// I.S: Bukan yang paling kanan di levelnya.
// Mengembalikan node selevel yang paling kiri yang berada di kanan node ini.
nodetreex* nodetreex :: getLeftestNeighbour(){
	nodetreex* x = this->parent;
	if(this == x->getLeft()){
		return x->getRight();
	} else {
		nodetreex* y = x->getLeftestNeighbour();
		int i = y->hasNoChild();
		while(i){
			x = y;
			y = x->getLeftestNeighbour();
			i = y->hasNoChild();
		}
		return y->getLeft();
	}
}

// I.S: Bukan yang paling kiri di levelnya.
// Mengembalikan node selevel yang paling kanan yang berada di kiri node ini.
nodetreex* nodetreex :: getRightestNeighbour(){
	nodetreex* x = this->parent;
	if(this == x->getRight()){
		return x->getLeft();
	} else {
		nodetreex* y = x->getRightestNeighbour();
		int i = y->hasNoChild();
		while(i){
			x = y;
			y = x->getRightestNeighbour();
			i = y->hasNoChild();
		}
		return y->getRight();
	}
}

// Node paling kanan/kiri di suatu kedalaman
// Harus dipanggil di root. lvl >= 0. Ada kedalaman sedalam minimal level.
// Mengembalikan node paling kiri di level tersebut.
nodetreex* nodetreex :: getLeftestLevel(short lvl){
	if(lvl == 0){
		return this;
	} else {
		if(this->hasNoChild()){
			return NULL;
		} else {
			nodetreex* x = this->left->getLeftestLevel(lvl - 1);
			if(x == NULL){
				return this->right->getLeftestLevel(lvl - 1);
			} else {
				return x;
			}
		}
	}
}

// Harus dipanggil di root. lvl >= 0. Ada kedalaman sedalam minimal level.
// Mengembalikan node paling kanan di level tersebut.
nodetreex* nodetreex :: getRightestLevel(short lvl){
	if(lvl == 0){
		return this;
	} else {
		if(this->hasNoChild()){
			return NULL;
		} else {
			nodetreex* x = this->right->getRightestLevel(lvl - 1);
			if(x == NULL){
				return this->left->getRightestLevel(lvl - 1);
			} else {
				return x;
			}
		}
	}
}

// Mendapatkan String
// I.S: Node berkarakter C ada di pohon
string nodetreex :: getString(char C){
	string Str;
	if(this->id != 'L'){
		if(this->left->searchTree(C) != NULL){
			Str = "0" + this->left->getString(C);
			return Str;
		} else {
			Str = "1" + this->right->getString(C);
			return Str;
		}
	} else {
		return "";
	}
}

/*
	Spawn_child: menghasilkan dua buah anak, anak kanan
	dan anak kiri. Anak kanan adalah node yang berisi byte 
	yang menjadi parameter dan NYT_node dipindahkan menjadi
	anak kiri.
*/
// I.S. berada di node NYT_node
void nodetreex :: spawnChild(_BYTE bc){
	this->right = new nodetreex;
	this->setid('P');
	this->left = new nodetreex;
	this->left->setid('N');
	this->left->setParent(this);
	(this->right)->setByte(bc);
	this->right->setid('L');
	this->right->setweight(1);
	this->right->setParent(this);
}

// Menset weight parent
void nodetreex :: PlusParent(){
	nodetreex* x = this->parent;
	x->setweight(x->getLeft()->getWeight() + x->getRight()->getWeight());
}

void nodetreex :: PrintTree(){
	
}

//---------------------------------------------------------------------------------------------//
//                                        TREE ITERATIF                                        //
//---------------------------------------------------------------------------------------------//

// Konstruktor Tree Manipulator

tree_iter :: tree_iter(){
	this->setByte(0);
	this->setid('R');
	this->setLeft(NULL);
	this->setRight(NULL);
	this->setweight(0);
	this->root = this;
	this->setParent(NULL);
}

// Updating Tree
// Hasil = String yang dicatat di hasil kompresi.
// Sinyal = Apakah terjadi penambahan node baru atau tidak.
// Sinyal = 0 => Ada penambahan. Sinyal = 1 => Tidak ada penambahan.
tree_iter& tree_iter :: update(char C, string& hasil, int& sinyal){
	nodetreex* N;
	N = this->searchTree(C);
	
	// PENAMBAHAN NODE BARU ATAU PENAMBAHAN WEIGHT
	
	if(N == NULL){
		nodetreex* T;
		T = this->getRoot()->searchid('N');
		T->spawnChild(C);
		T->setweight(T->getRight()->getWeight());
		N = T->getRight();
		sinyal = 0;
	} else {
		sinyal = 1;
		N->incrementWeight();
		N->PlusParent();
	}
	hasil = this->getRoot()->getString(C);
	
	// CHECK AND SWAP FROM HERE
	
	short nowlevel = this->getlevel(*N);
	while(nowlevel > 0){
		int i = N == this->getRightestLevel(nowlevel);
		if(i){
			nodetreex* Check = this->getLeftestLevel(nowlevel-1);
			if(Check->getWeight() < N->getWeight() && Check->getId() != 'R'){
				this->swapNodeTree(*N, *Check);
			} else if (Check->getId() == 'R'){
				Check->setweight(Check->getLeft()->getWeight() + Check->getRight()->getWeight());
				this->root->setweight(this->root->getLeft()->getWeight() + this->root->getRight()->getWeight());
			} else {
				N = Check;
			}
			nowlevel--;
		} else {
			nodetreex* Check = N->getLeftestNeighbour();
			if(Check->getWeight() < N->getWeight()){
				this->swapNodeTree(*N, *Check);
			} else {
				N->PlusParent();
				N = Check;
			}
		}
	}
	return *this;
}

// Getter

nodetreex* tree_iter :: getRoot(){
	return root;
}

nodetreex* tree_iter :: getNYTnode(){
	return this->searchid('N');
}	

// Menghapus Node NYT
// Hanya dilakukan di akhir
void tree_iter :: deleteNYT(){
	nodetreex* X = this->getRoot()->searchid('N')->getParent();
	X->setByte(X->getRight()->getByte());
	X->setid(X->getRight()->getId());
	X->setweight(X->getRight()->getWeight());
	X->getRight()->setParent(NULL);
	X->getLeft()->setParent(NULL);
	delete X->getRight();
	delete X->getLeft();
	X->setRight(NULL);
	X->setLeft(NULL);
}

// Modifiers
// Menukar Node untuk Swap
// I.S : Kedua node terdefinisi. Bukan Root. Salah satunya bukan Parent Node satunya.
void tree_iter :: swapNodeTree(nodetreex& srcNode, nodetreex& destNode){
	nodetreex* x = srcNode.getParent();
	nodetreex* y = destNode.getParent();
	nodetreex* tmp;
	if(x->getLeft() == &srcNode){
		if(y->getLeft() == &destNode){
			tmp = x->getLeft();
			x->setLeft(y->getLeft());
			y->setLeft(tmp);
		} else {
			tmp = x->getLeft();
			x->setLeft(y->getRight());
			y->setRight(tmp);
		}
	} else {
		if(y->getLeft() == &destNode){
			tmp = x->getRight();
			x->setRight(y->getLeft());
			y->setLeft(tmp);
		} else {
			tmp = x->getRight();
			x->setRight(y->getRight());
			y->setRight(tmp);
		}
	}
	tmp = srcNode.getParent();
	srcNode.setParent(destNode.getParent());
	destNode.setParent(tmp);
	srcNode.PlusParent();
	destNode.PlusParent();
}

// Menambah weight node
void tree_iter :: incrementWeightNode(nodetreex& T){
	T.incrementWeight();
}

// Spawn pertama yang harus dipanggil root untuk karakter pertama
void tree_iter :: spawnChild(_BYTE b){
	this->right = new nodetreex;
	this->left = new nodetreex;
	this->left->setid('N');
	this->left->setParent(this);
	this->right->setByte(b);
	this->right->setid('L');
	this->right->setweight(1);
	this->right->setParent(this);
	this->setweight(this->getLeft()->getWeight() + this->getRight()->getWeight());
}

// Metode untuk set NYT node.
void tree_iter :: setNYTnode(){
	this->setid('N');
}
