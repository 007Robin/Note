//XinSong 有upperbound,lowerbound功能的可含重复元素的红黑树
#include <iostream>	
#include <vector>
#include <utility>
using namespace std;

enum COLOR { RED, BLACK };

struct Node {
	int 	key;
	COLOR 	color;
	Node* 	p;
	Node* 	left;
	Node* 	right;
	int 	size;		//the total number of Nodes in current subtree (including itself)
	int 	dup;		//the number of duplicated keys
	Node(int k, COLOR c = RED, Node* parent = nullptr, Node* l = nullptr, Node* r = nullptr,int s = 1) 
		:key(k), color(c), p(parent), left(l), right(r), size(s), dup(0) {}
};

class EnhancedRBTree {
	Node* 	root;

	void leftRotate(Node* n) {
		if (!n || !n->right) {
			return;
		}
		Node* r = n->right;
		Node* p = n->p;
		if (p) {
			if (p->right == n)
				p->right = r;
			else
				p->left = r;
		}
		else
			root = r;
		r->p = p;
		n->right = r->left;
		if (n->right)
			n->right->p = n;
		r->left = n;
		n->p = r;
		//update size as the number of Nodes in current subtree
		r->size = n->size;
		n->size = (n->left ? n->left->size : 0) + (n->right ? n->right->size: 0) + 1;
	}

	void rightRotate(Node* n) {
		if (!n || !n->left) {
			return;
		}
		Node* l = n->left;
		Node* p = n->p;
		if (p) {
			if (p->left == n)
				p->left = l;
			else
				p->right = l;
		}
		else
			root = l;
		l->p = p;
		n->left = l->right;
		if (n->left)
			n->left->p = n;
		l->right = n;
		n->p = l;
		//update size as the number of Nodes in current subtree
		l->size = n->size;
		n->size = (n->left ? n->left->size : 0) + (n->right ? n->right->size : 0) + 1;
	}

	// fix red red voilaton if exists
	void fixRedRed(Node* newNode) {
		while (newNode->p && newNode->p->color == RED) {
			//if father is left child of grandparent
			if (newNode->p->p->left == newNode->p) {
				Node* father = newNode->p;
				Node* uncle = father->p->right;
				// uncle red, perform recoloring and recurse
				if (uncle && uncle->color == RED) {
					father->color = BLACK;
					uncle->color = BLACK;
					father->p->color = RED;
					newNode = father->p;
				}
				else {
					if (newNode == father->right) {
						leftRotate(father);
						newNode = father;
						father = father->p;
					}
					father->color = BLACK;
					father->p->color = RED;
					//for left left and left right
					rightRotate(father->p);
				}
			}
			else {
				Node* father = newNode->p;
				Node* uncle = father->p->left;
				if (uncle && uncle->color == RED) {
					uncle->color = BLACK;
					father->color = BLACK;
					father->p->color = RED;
					newNode = father->p;
				}
				else {
					if (newNode == father->left) {
						rightRotate(father);
						newNode = father;
						father = father->p;
					}
					father->color = BLACK;
					father->p->color = RED;
					// for right right and right left
					leftRotate(father->p);
				}
			}
		}
		root->color = BLACK;
	}

	ostream& preorder(ostream& o, Node* r) const {
		if (!r)
			return o;
		o << r->key << " ";
		preorder(o, r->left);
		preorder(o, r->right);
		return o;
	}
	ostream& inorder(ostream& o, Node* r) const {
		if (!r)
			return o;
		inorder(o, r->left);
		o << r->key << " ";
		inorder(o, r->right);
		return o;
	}
	ostream& postorder(ostream& o, Node* r) const {
		if (!r)
			return o;
		postorder(o, r->left);
		postorder(o, r->right);
		o << r->key << " ";
		return o;
	}
	ostream& inorderSize(ostream& o, Node* r)const {
		if (!r)
			return o;
		inorderSize(o, r->left);
		o << r->size << " ";
		inorderSize(o, r->right);
		return o;
	}

	Node* getKey(int key) const {
		Node* r = root;
		while (r) {
			if (r->key == key)
				break;
			if (r->key < key)
				r = r->right;
			else
				r = r->left;
		}
		if (!r)
			return nullptr;
		return r;
	}

	Node* getMin(Node* t) {
		Node* res = nullptr;
		while (t) {
			res = t;
			t = t->left;
		}
		return res;
	}

	Node* getNext(Node* t) {
		if (t && t->right) {
			return getMin(t->right);
		}
		else {
			while (t && t->p && t->p->left == t) {
				t = t->p;
			}
			if (t && t->p)
				return t->p;
			else
				return nullptr;
		}
	}

	void fixDoubleBlack(Node* x, Node* px) {
		while (x != root && (!x || x->color == BLACK)) {
			if (x == px->left) {
				Node* w = px->right;
				if (w->color == RED) {
					w->color = BLACK;
					px->color = RED;
					leftRotate(px);
					w = px->right;
				}
				if ((!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK)) {
					w->color = RED;
					x = px;
					px = px->p;
				}
				else {
					if (!w->right || w->right->color == BLACK) {
						w->color = RED;
						w->left->color = BLACK;
						rightRotate(w);
						w = px->right;
					}
					w->color = px->color;
					px->color = BLACK;
					w->right->color = BLACK;
					leftRotate(px);
					x = root;
				}
			}
			else {
				Node* w = px->left;
				if (w->color == RED) {
					w->color = BLACK;
					px->color = RED;
					rightRotate(px);
					w = px->left;
				}
				if ((!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK)) {
					w->color = RED;
					x = px;
					px = px->p;
				}
				else {
					if (!w->left || w->left->color == BLACK) {
						w->right->color = BLACK;
						w->color = RED;
						leftRotate(w);
						w = px->left;
					}
					w->color = px->color;
					px->color = BLACK;
					w->left->color = BLACK;
					rightRotate(px);
					x = root;
				}

			}
		}
		x->color = BLACK;
	}

	void clear(Node* root) {
		if (!root)
			return;
		clear(root->right);
		clear(root->left);
		delete root;
	}

	int index(Node* root, int i) const {
		int l = root->left ? root->left->size : 0;
		l += root->dup;
		int s = l + 1;
		if((s-i) >= 0 && (s-i)<=root->dup)
			return root->key;
		if (s == i)
			return root->key;
		else if (s > i)
			return index(root->left, i);
		else
			return index(root->right, i - s);
	}

	pair<int,int> rank(Node* root, int key, int sum = 0) const {
		if (!root)
			return {sum, sum};
		int l = (root->left ? root->left->size : 0) + 1;
		if (root->key == key)
			return {l + sum, l + sum + root->dup};
		if (root->key < key)
			return rank(root->right, key, sum + l + root->dup);
		else
			return rank(root->left, key, sum + root->dup);
	}

public:
	EnhancedRBTree(Node* r = nullptr) : root(r) {}

	//insert implement
	void insert(int key) {
		//find where the value is to be inserted
		Node* tr = root;
		Node* ti = nullptr;
		while (tr) {
			++(tr->size);
			ti = tr;
			if (tr->key < key)
				tr = tr->right;
			else if(tr->key == key) {
				//statistic duplicates key
				++(tr->dup);		
				break;
			}
			else 
				tr = tr->left;
		}
		//if it's null, simply insert value at root
		if (!ti)
			root = new Node(key, BLACK);
		else {
			//if the key is duplicated, no need insert again
			//otherwise, connect new node to correct node
			if(ti->key == key)
				return;
			Node* newNode = new Node(key, RED, ti);
			if (ti->key < key)
				ti->right = newNode;
			else 
				ti->left = newNode;
			//fix red red voilaton if exists
			fixRedRed(newNode);
		}
	}

	bool find(int key) const {
		return getKey(key) != nullptr;
	}

	//erase() implement
	void erase(int key) {
		Node* r = getKey(key);
		int color;
		Node* x = nullptr;
		Node* px = nullptr;
		if (!r)
			return;
		color = r->color;
		if (!r->left && !r->right) {
			x = nullptr;
			px = r->p;
			if (!px) {
				root = nullptr;
				//				free(r);
				delete r;
				return;
			}
			else {
				if (px->left == r) {
					px->left = x;
				}
				else {
					px->right = x;
				}
			}
		}
		else if (!r->left) {
			x = r->right;
			px = r->p;
			if (!px) {
				root = x;
			}
			else {
				if (px->right == r) {
					px->right = x;
				}
				else {
					px->left = x;
				}
			}
			x->p = px;
		}
		else if (!r->right) {
			x = r->left;
			px = r->p;
			if (!px) {
				root = x;
			}
			else {
				if (px->right == r) {
					px->right = x;
				}
				else {
					px->left = x;
				}
			}
			x->p = px;
		}
		else {
			Node* nr = getMin(r->right);
			color = nr->color;

			//update size 
			nr->size = r->size;

			x = nr->right;
			px = nr->p;
			if (px->left == nr) {
				px->left = x;
			}
			else {
				px->right = x;
			}
			if (x) {
				x->p = px;
			}
			if (px == r)
				px = nr;
			if (!r->p) {
				root = nr;
			}
			else if (r->p->left == r) {
				r->p->left = nr;
			}
			else {
				r->p->right = nr;
			}
			nr->p = r->p;
			nr->left = r->left;
			nr->left->p = nr;
			nr->right = r->right;
			if (nr->right)
				nr->right->p = nr;
		}
		//		free(r);
		delete r;

		//update size
		Node* tmppx = px;
		while (tmppx) {
			--(tmppx->size);
			tmppx = tmppx->p;
		}

		if (color == BLACK) {
			fixDoubleBlack(x, px);
		}
	}
	ostream& printSizeOnInorder(ostream& o) const{
		inorder(o,root)	<<endl;
		inorderSize(o, root) << endl;
		return o;
	}
	void clear() {
		clear(root);
		root = nullptr;
	}

	//index() implement
	int index(int i) const {
		i++;
		if (i <= 0)
			return INT_MIN;
		if (root->size < i)
			return INT_MAX;
		return index(root, i);
	}

	//rank() implement
	pair<int,int> rank(int key) const {
		auto res = rank(root, key);
		return {res.first - 1, res.second - 1};
	}

	~EnhancedRBTree() {
		clear();
	}

	friend ostream& operator<<(ostream& os, const EnhancedRBTree& t);
};

ostream& operator<<(ostream& o, const EnhancedRBTree &t) {
	t.preorder(o, t.root) << endl;
	t.inorder(o, t.root) << endl;
	t.postorder(o, t.root) << endl;
	return o;
}

int main() {
	//test insert()
	EnhancedRBTree t; 
	t.insert(3);
	t.insert(8);
	t.insert(9);
	t.insert(9);
	t.insert(9);
	t.insert(15);

	//print out tree's preorder, inorder, postorder
	cout << t << endl;
	t.printSizeOnInorder(cout);

	//test rank()
	cout << "---------------------\n";
	cout << "rank(3) = [" << t.rank(3).first  << "," << t.rank(3).second << "]" << endl;
	cout << "rank(8) = [" << t.rank(8).first  << "," << t.rank(8).second << "]" << endl;
	cout << "rank(9) = [" << t.rank(9).first  << "," << t.rank(9).second << "]" << endl;
	cout << "rank(15) = [" << t.rank(15).first  << "," << t.rank(15).second << "]" << endl;

	//test index()	
	cout << "---------------------\n";
	for(int i = 0; i < 6; ++i)
		cout  << "index(" << i << ") = " << t.index(i) << endl;

	//test erase()
	t.erase(15);
	t.erase(9);

	//print out tree's preorder, inorder, postorder
	cout << "---------------------\n";
	cout << t << endl;
	t.printSizeOnInorder(cout);
	return 0;
}


/*******print out of this program**********  
8 3 9 15 
3 8 9 15 
3 15 9 8 

3 8 9 15 
1 6 4 1 
---------------------
rank(3) = [0,0]
rank(8) = [1,1]
rank(9) = [2,4]
rank(15) = [5,5]
---------------------
index(0) = 3
index(1) = 8
index(2) = 9
index(3) = 9
index(4) = 9
index(5) = 15
---------------------
8 3 
3 8 
3 8 

3 8 
1 4
********/
