
#include "tree_manipulator.h"
#include <iostream>

using namespace std;

//----------------------------------------------------------------------------------------------//
//                                           NODETREE                                           //
//----------------------------------------------------------------------------------------------//

// Konstruktor-Destruktor kelas nodetree
nodetree :: nodetree(){
	b = 0;
	weight = 0;
	left = NULL;
	right = NULL;
	id = 'L';
}

nodetree :: nodetree(char c){
	b = 0;
	weight = 0;
	left = NULL;
	right = NULL;
	id = c;
}

nodetree :: nodetree(const nodetree& T){
	left = T.left;
	right = T.right;
	id = T.id;
	b = T.b;
	weight = T.weight;
}

nodetree :: ~nodetree(){
	delete left;
	delete right;
}
	
nodetree& nodetree :: operator= (const nodetree& T){
	left = T.left;
	right = T.right;
	id = T.id;
	b = T.b;
	weight = T.weight;
	return *this;
}

// Operasi Dasar Kelas Tree

// Getter

_BYTE nodetree :: getByte(){
	return b;
}

nodetree*  nodetree :: getLeft(){
	return left;
}

nodetree*  nodetree :: getRight(){
	return right;
}

long nodetree :: getWeight(){
	return weight;
}

char nodetree :: getId(){
	return id;
}

// Getter Spesial. Untuk mengetahui kedalaman simpul
short nodetree :: getlevel(nodetree& T){
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
void nodetree :: incrementWeight(){
	weight++;
}

// Setter
	
void nodetree :: setByte(_BYTE bc){
	b = bc;
}

void nodetree :: setid(char c){
	id = c;
}

void nodetree :: setLeft(nodetree* ptr){
	left = ptr;
}

void nodetree :: setRight(nodetree* ptr){
	right = ptr;
}

void nodetree :: setweight(long i){
	weight = i;
}
	
// Informasi anak dan isi node

int nodetree :: hasOnlyLeftChild(){
	return this->right == NULL && this->left != NULL;
}

int nodetree :: hasOnlyRightChild(){
	return this->left == NULL && this->right != NULL;
}

int nodetree :: hasNoChild(){
	return this->left == NULL && this->right == NULL;
}
	
int nodetree :: hasThisByte(_BYTE& bc){
	return this->b == bc;
}

// Searching
	
nodetree* nodetree :: searchTree(_BYTE bc){
	nodetree* x;
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
	
nodetree* nodetree :: searchid(char idx){
	nodetree* x;
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
	
nodetree* nodetree :: searchParent(nodetree* P){
	nodetree* x;
	if(this == P){
		return NULL;
	} else {
		if (this->right != NULL){
			if(this->left != NULL){
				if(this->left == P){
					return this;
				} else {
					x = this->left->searchParent(P);
					if(x != NULL){
						return x;
					} else {
						x = this->right->searchParent(P);
						if(this->right == P){
							return this;
						} else {
							if(x != NULL){
								return x;
							} else {
								return NULL;
							}
						}
					}
				}
			} else {
				if(this->right == P){
					return this;
				} else {
					return this->right->searchParent(P);
				}
			}
		} else {
			if(this->left != NULL){
				if(this->left == P){
					return this;
				} else {
					return this->left->searchParent(P);
				}
			} else {
				return NULL;
			}
		}
	}
}

// Tetangga
// I.S: Bukan yang paling kanan di levelnya.
// Mengembalikan node selevel yang paling kiri yang berada di kanan node ini.
nodetree* nodetree :: getLeftestNeighbour(nodetree* root){
	nodetree* x = root->searchParent(this);
	if(this == x->getLeft()){
		return x->getRight();
	} else {
		nodetree* y = x->getLeftestNeighbour(root);
		int i = y->hasNoChild();
		while(i){
			x = y;
			y = x->getLeftestNeighbour(root);
			i = y->hasNoChild();
		}
		return y->getLeft();
		/*
		if(y->hasNoChild()){
			return y->getLeftestNeighbour(root)->getLeft();
		} else {
			return y->getLeft();
		}*/
	}
}

// I.S: Bukan yang paling kiri di levelnya.
// Mengembalikan node selevel yang paling kanan yang berada di kiri node ini.
nodetree* nodetree :: getRightestNeighbour(nodetree* root){
	nodetree* x = root->searchParent(this);
	if(this == x->getRight()){
		return x->getLeft();
	} else {
		nodetree* y = x->getRightestNeighbour(root);
		if(y->hasNoChild()){
			return y->getRightestNeighbour(root)->getRight();
		} else {
			return y->getRight();
		}
	}
}

// Node paling kanan/kiri di suatu kedalaman
// Harus dipanggil di root. lvl >= 0. Ada kedalaman sedalam minimal level.
// Mengembalikan node paling kiri di level tersebut.
nodetree* nodetree :: getLeftestLevel(short lvl){
	if(lvl == 0){
		return this;
	} else {
		if(this->hasNoChild()){
			return NULL;
		} else {
			nodetree* x = this->left->getLeftestLevel(lvl - 1);
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
nodetree* nodetree :: getRightestLevel(short lvl){
	if(lvl == 0){
		return this;
	} else {
		if(this->hasNoChild()){
			return NULL;
		} else {
			nodetree* x = this->right->getRightestLevel(lvl - 1);
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
string nodetree :: getString(char C){
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
void nodetree :: spawnChild(_BYTE bc){
	this->right = new nodetree;
	this->setid('P');
	this->left = new nodetree;
	this->left->setid('N');
	(this->right)->setByte(bc);
	this->right->setid('L');
	this->right->setweight(1);
}

// Menjumlahkan seluruh parent dari nodetree T sampai dengan root
// Harus dipanggil di Root
void nodetree :: PlusParent(nodetree& T){
	nodetree* x;
	x = this->searchParent(&T);
	x->setweight(x->getLeft()->getWeight() + x->getRight()->getWeight());
}

void nodetree :: PrintTree(){
	
}

//----------------------------------------------------------------------------------------------//
//                                       TREE MANIPULATOR                                       //
//----------------------------------------------------------------------------------------------//

// Konstruktor Tree Manipulator

tree_manipulator :: tree_manipulator(){
	this->setByte(0);
	this->setid('R');
	this->setLeft(NULL);
	this->setRight(NULL);
	this->setweight(0);
	this->root = this;
}

// Updating Tree
// Hasil = String yang dicatat di hasil kompresi.
// Sinyal = Apakah terjadi penambahan node baru atau tidak.
// Sinyal = 0 => Ada penambahan. Sinyal = 1 => Tidak ada penambahan.
tree_manipulator& tree_manipulator :: update(char C, string& hasil, int& sinyal){
	nodetree* N;
	N = this->searchTree(C);
	
	// PENAMBAHAN NODE BARU ATAU PENAMBAHAN WEIGHT
	
	if(N == NULL){
		nodetree* T;
		T = this->getRoot()->searchid('N');
		T->spawnChild(C);
		this->root->PlusParent(*(T->getRight()));
		N = T->getRight();
		sinyal = 0;
	} else {
		sinyal = 1;
		N->incrementWeight();
		this->root->PlusParent(*N);
	}
	hasil = this->getRoot()->getString(C);
	
	// CHECK AND SWAP FROM HERE
	
	short nowlevel = this->getlevel(*N);
	while(nowlevel > 0){
		int i = N == this->getRightestLevel(nowlevel);
		if(i){
			nodetree* Check = this->getLeftestLevel(nowlevel-1);
			if(Check->getWeight() < N->getWeight() && Check->getId() != 'R'){
				this->swapNodeTree(*N, *Check);
				this->root->PlusParent(*Check);
			} else if (Check->getId() == 'R'){
				Check->setweight(Check->getLeft()->getWeight() + Check->getRight()->getWeight());
				this->root->setweight(this->root->getLeft()->getWeight() + this->root->getRight()->getWeight());
			} else {
				N = Check;
			}
			nowlevel--;
		} else {
			nodetree* Check = N->getLeftestNeighbour(this->root);
			if(Check->getWeight() < N->getWeight()){
				this->swapNodeTree(*N, *Check);
				this->root->PlusParent(*Check);
			} else {
				this->root->PlusParent(*N);
				N = Check;
			}
		}
	}
	return *this;
}

// Getter

nodetree* tree_manipulator :: getRoot(){
	return root;
}

nodetree* tree_manipulator :: getNYTnode(){
	return this->searchid('N');
}	

// Menghapus Node NYT
// Hanya dilakukan di akhir
void tree_manipulator :: deleteNYT(){
	nodetree* X = this->getRoot()->searchParent(this->getRoot()->searchid('N'));
	X->setByte(X->getRight()->getByte());
	X->setid(X->getRight()->getId());
	X->setweight(X->getRight()->getWeight());
	delete X->getRight();
	delete X->getLeft();
	X->setRight(NULL);
	X->setLeft(NULL);
}

// Modifiers
// Menukar Node untuk Swap
// I.S : Kedua node terdefinisi. Bukan Root. Salah satunya bukan Parent Node satunya.
void tree_manipulator :: swapNodeTree(nodetree& srcNode, nodetree& destNode){
	nodetree* x = this->root->searchParent(&srcNode);
	nodetree* y = this->root->searchParent(&destNode);
	nodetree* tmp;
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
	this->root->PlusParent(srcNode);
	this->root->PlusParent(destNode);
}

// Menambah weight node
void tree_manipulator :: incrementWeightNode(nodetree& T){
	T.incrementWeight();
}

// Spawn pertama yang harus dipanggil root untuk karakter pertama
void tree_manipulator :: spawnChild(_BYTE b){
	this->right = new nodetree;
	this->left = new nodetree;
	this->left->setid('N');
	(this->right)->setByte(b);
	this->right->setid('L');
	this->right->setweight(1);
	this->root->PlusParent(*(this->right));
}

// Metode untuk set NYT node.
void tree_manipulator :: setNYTnode(){
	this->setid('N');
}
