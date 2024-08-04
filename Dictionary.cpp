//Kevin Gallegos 1858764 PA8

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

// Private Construct---------------------------

Dictionary::Node::Node(keyType k, valType v){
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = 0;
}

//classs construct and destruct
Dictionary::Dictionary(){
	nil = new Node("NIL", -1);
	root = nil;
	current = nil;
	num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
        nil = new Node("NIL", -1);
        root = nil;
        current = nil;
	//cout<<"size of deez"<<D.size()<<endl;
        num_pairs = 0;
	preOrderCopy(D.root, D.nil);
   	num_pairs = D.num_pairs;
}
Dictionary::~Dictionary(){
	clear();
	delete nil;
}
//helpers--------------------
void Dictionary::inOrderString(std::string& s, Node* R)const{
	if(R != nil){
		inOrderString(s, R->left);
		s.append(R->key);
		s.append(" : ");
		s.append(std::to_string(R->val));
		s.append("\n");
		inOrderString(s,R->right);
	}
}
void Dictionary::inOrderStringKeys(std::string& s, Node* R)const{
        if(R != nil){
                inOrderStringKeys(s, R->left);
                s.append(R->key);
                s.append("\n");
                inOrderStringKeys(s,R->right);
        }
}



void Dictionary::preOrderString(std::string& s, Node* R)const{
	if (R != nil) {
		s.append(R->key);
		s.append(" : ");
		s.append(std::to_string(R->val));
		s.append("\n");
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

void Dictionary::preOrderStringKeys(std::string& s, Node* R)const{
	if (R != nil) {
                s.append(R->key);
		if(R->color == 1){
			s.append(" (RED)");
		}
		//cout<<"color is "<<R->color<<endl;
                s.append("\n");
                preOrderStringKeys(s, R->left);
                preOrderStringKeys(s, R->right);
        }
}

void Dictionary::BST_insert(Node* M){
	Node* y = nil;
	Node* z = new Node(M->key,M->val);
	z->color = M->color;
	Node* x = root;
	while(x != nil){
		y = x;
		if(z->key < x->key){//key
			x = x->left;
		}
		else{
			x = x->right;
		}
	}
	z->parent = y;
	if(y == nil){
		root = z;
	}
	else if( z->key < y->key){
		y->left = z;
	}
	else{
		y->right = z;
	}
	z->left = nil;
	z->right = nil;
	z->color = 1;
	//cout<<"loop done"<<endl;
	RB_InsertFixUp(z);
}


void Dictionary::preOrderCopy(Node* R, Node* N){
	if (R != N) {//add copying the color too???
		//N->color = R->color;
		//Node* C = R;
		//BST_insert(R);
		setValue(R->key, R->val);
		preOrderCopy(R->left, N);
		preOrderCopy(R->right, N);
		//remove(N->key);
	}
}

void Dictionary::postOrderDelete(Node* R){
	if (R != nil) {
		postOrderDelete(R->left);
		postOrderDelete(R->right);
		delete R;
	}

}

Dictionary::Node* Dictionary::search(Node* R, keyType k)const{
	while(R != nil) {
		if(R == nil || k == R->key){return R;}
		else if (k < R->key){return search(R->left, k);}
		else if (k > R->key){return search(R->right, k);}
	}
	return nil;

}

Dictionary::Node* Dictionary::findMin(Node* R){
	while (R->left != nil){
		R = R->left;
	}
	return R;
}

Dictionary::Node* Dictionary::findMax(Node* R){
	while (R->right != nil){
		R = R->right;
	}
	return R;
}

Dictionary::Node* Dictionary::findNext(Node* N){
	if (N->right != nil) {
		return findMin(N->right);
	}
	Node* next = N->parent;
	while (next != nil && N == next->right){
		N = next;
		next = next->parent;
	}
	return next;
}

Dictionary::Node* Dictionary::findPrev(Node* N){
	if (N->left != nil) {
		return findMax(N->left);
	}
	Node* prev = N->parent;
	while (prev != nil && N == prev->left){
		N = prev;
		prev = prev->parent;
	}
	return prev;
}
///------RBT HELPERSSSSS-------------------------------------------------

void Dictionary::LeftRotate(Node* N){
	Node* y = N->right;
	N->right = y->left;
	if(y->left != nil){
		y->left->parent = N;
	}
	y->parent = N->parent;
	if(N->parent == nil){
		root = y;
	}
	else if(N == N->parent->left){
		N->parent->left = y;
	}
	else{
		N->parent->right = y;
	}
	y->left = N;
	N->parent = y;
}

void Dictionary::RightRotate(Node* N){
	Node* y = N->left;
	N->left = y->right;
	if(y->right != nil){
		y->right->parent = N;
	}
	y->parent = N->parent;
	if(N->parent == nil){
		root=y;
	}
	else if(N==N->parent->right){
		N->parent->right = y;
	}
	else{
		N->parent->left = y;
	}
	y->right = N;
	N->parent = y;
}

void Dictionary::RB_InsertFixUp(Node* N){
	while(N->parent->color == 1){
		if(N->parent == N->parent->parent->left){
			Node* y = N->parent->parent->right;
			if(y->color == 1){
				N->parent->color = 0;
				y->color = 0;
				N->parent->parent->color = 1;
				N = N->parent->parent;
			}
			else{
				if(N == N->parent->right){
					N = N->parent;
					LeftRotate(N);
				}
				N->parent->color = 0;
				N->parent->parent->color = 1;
				RightRotate(N->parent->parent);
			}
		}
		else{
			Node* y = N->parent->parent->left;
			if(y->color == 1){
				N->parent->color = 0;
				y->color =0;
				N->parent->parent->color = 1;
				N = N->parent->parent;
			}
			else{
				if(N == N->parent->left){
					N=N->parent;
					RightRotate(N);
				}
				N->parent->color = 0;
				N->parent->parent->color = 1;
				LeftRotate(N->parent->parent);
			}
		}
	}
	root->color = 0;
}

void Dictionary::RB_Transplant(Node* u, Node* v){
	if(u->parent == nil){
		root = v;
	}
	else if(u == u->parent->left){
		u->parent->left = v;
	}
	else{
		u->parent->right = v;
	}
	v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N){
	while(N != root && N->color == 0){
		if(N==N->parent->left){
			Node* w = N->parent->right;
			if(w->color==1){
				w->color = 0;
				N->parent->color = 1;
				LeftRotate(N->parent);
				w = N->parent->right;
			}
			if(w->left->color == 0 && w->right->color == 0){
				w->color = 1;
				N = N->parent;
			}
			else{
				if(w->right->color == 0){
					w->left->color = 0;
					w->color = 1;
					RightRotate(w);
					w = N->parent->right;
				}
				w->color = N->parent->color;
				N->parent->color = 0;
				w->right->color = 0;
				LeftRotate(N->parent);
				N = root;
			}
		}
		else{
			Node* w = N->parent->left;
			if(w->color==1){
				w->color = 0;
				N->parent->color = 1;
				RightRotate(N->parent);
				w = N->parent->left;
			}
			if(w->right->color == 0 && w->left->color == 0){
				w->color = 1;
				N=N->parent;
			}
			else{
				if(w->left->color == 0){
					w->right->color = 0;
					w->color = 1;
					LeftRotate(w);
					w = N->parent->left;
				}
				w->color = N->parent->color;
				N->parent->color = 0;
				w->left->color = 0;
				RightRotate(N->parent);
				N = root;
			}
		}
	}
	N->color = 0;
}

void Dictionary::RB_Delete(Node* N){
	Node* y =  N;
	Node* x;
	int y_ocolor = y->color;
	if(N->left == nil){
		x = N->right;
		RB_Transplant(N,N->right);
		//cout<<"delete case 1"<<endl;
	}
	else if(N->right == nil){
		x = N->left;
		RB_Transplant(N, N->left);
		//cout<<"delete case 2"<<endl;
	}
	else{
		y = findMin(N->right);
		y_ocolor = y->color;
		x = y->right;
		if(y->parent == N){
			x->parent = y;
		}
		else{
			RB_Transplant(y,y->right);
			y->right = N->right;
			y->right->parent = y;
		}
		RB_Transplant(N,y);
		y->left = N->left;
		y->left->parent = y;
		y->color = N->color;
		//cout<<"delete case 3"<<endl;
	}
	if(y_ocolor == 0){
		RB_DeleteFixUp(x);
		//cout<<"fixup case"<<endl;
	}
	//cout<<"deleted one"<<endl;
}


//access--------------------------
int Dictionary::size()const{
	return num_pairs;
}

bool Dictionary::contains(keyType k)const{
	if (search(root, k) != nil){return true;}
	return false;

}

valType& Dictionary::getValue(keyType k)const{
	if (contains(k)==false) {
		cout<<"Dictionary: getValue(): key "<<k;
		throw std::invalid_argument(" does not exist");
	}
	Node* result = search(root, k);
	return result->val;
}

bool Dictionary::hasCurrent()const{
	if(current == nil){return false;}
	else{return true;}
}

keyType Dictionary::currentKey()const{
	if(current->key == nil->key){
		throw std::logic_error("Dictionary: currentKey(): current undefined");
	}
	return current->key;
}

valType& Dictionary::currentVal() const{
	if(current->val == nil->val){
                throw std::logic_error("Dictionary: currentVal(): current undefined");
        }
	return current->val;
}
//manipulation-------------------------------
void Dictionary::clear() {
	if(num_pairs != 0 && root != this->nil){
		postOrderDelete(root);
		root = nil;
		current = nil;
		num_pairs = 0;
	}
}

void Dictionary::setValue(keyType k, valType v){
	Node* P = nil;
	Node* m = new Node(k, v);
	Node* R = root;
	while (R != nil) {
		P = R;
		if (m->key < R->key) {
			R = R->left;
		}
		else if(m->key > R->key) {
			R = R->right;
		}
		else {
			R->val = m->val;
			delete m;
			return;
		}
	}
	m->parent = P;
	if (P == nil) {
		root = m;
	}
	else if (m->key < P->key) {
		P->left = m;
	}
	else {
		P->right = m;
	}
	m->left = nil;
	m->right = nil;
	m->color = 1;
	//BST_insert(m);//????
	RB_InsertFixUp(m);//????
	num_pairs++;
}

void Dictionary::transplant(Node* u, Node* v) {
	if (u->parent == nil) {
		root = v;
		//delete u;
	}
	else if (u == u->parent->left) {
		u->parent->left = v;
		//delete u;
	}
	else {
		u->parent->right = v;
		//delete u;
	}
	if (v != nil) {
		v->parent = u->parent;
		//delete u;
	}
	//delete u;
}
/*
void Dictionary::remove(keyType k) {
	if (contains(k) == false) {
                cout<<"Dictionary: remove(): key "<<k;
                throw std::invalid_argument(" does not exist");
	}
	Node* m = search(this->root, k);
	if (m != this->nil) {
		if (this->current == m) {
			current = this->nil;
		}
		//RB_Delete(m);
		num_pairs--;
		delete m;
	}
}
*/

void Dictionary::remove(keyType k){//edited!!!
	if (contains(k) == false) {
		cout<<"Dictionary: remove(): key "<<k;
		throw std::invalid_argument(" does not exist");
	}
	//cout<<"key to delete is "<<k<<endl;
	Node* m = search(root, k);
	RB_Delete(m);
	delete m;
}

void Dictionary::begin() {
	if (num_pairs != 0) {
		current = findMin(root);
	}
}

void Dictionary::end() {
	if (num_pairs != 0) {
		current = findMax(root);
	}
}

void Dictionary::next() {
	if (hasCurrent() == false) {
		throw std::invalid_argument("Dictionary: next(): current undefined");
	}
	this->current = findNext(this->current);
}

void Dictionary::prev() {
	if (hasCurrent() == false) {
		throw std::invalid_argument("Dictionary: prev(): current undefined");
	}
	current = findPrev(current);
}

//---other---------

std::string Dictionary::to_string()const{
	std::string s;
	inOrderString(s, root);
	return s;
}

std::string Dictionary::pre_string()const{
	std::string s;
	//Node* N = root;
	//Dictionary D = *this;
	preOrderStringKeys(s, root);
	//delete D;
	return s;
}

bool Dictionary::equals(const Dictionary& D) const {
	std::string T1 = this->to_string();
	//cout<<"string is " << endl<<T1<< endl;
	std::string T2 = D.to_string();
	//cout<<"string is " << endl<< T2<< endl;
	if (T1 == T2 && num_pairs == D.num_pairs) {
		//cout<<"trueeeee"<<endl;
		return true;
	}
	else{
		return false;
	}
}

//---------operators------------

std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
	return stream << D.to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B) {
	return (A.equals(B));
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
	//clear();
	if(this==&D){
		return *this;
	}
	Dictionary tem = D;
	std::swap(nil, tem.nil);
   	std::swap(root, tem.root);
   	std::swap(current, tem.current);
   	std::swap(num_pairs, tem.num_pairs);
	//preOrderCopy(D.root, D.nil);//null D.root
	//remove("NIL");
	//postOrderDelete(this->root);	
	return *this;
}


