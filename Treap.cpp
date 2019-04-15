#include <iostream>
using namespace std;

struct treap {
	int x, y;

	treap *left, *right;
	treap(int key) {
		x = key;
		y = rand() % 1000000000;
		left = nullptr;
		right = nullptr;
	}
	

	void setLeft(treap *in) {
		left = in;
	}

	void setRight(treap *in) {
		right = in;
	}

} *root;

pair<treap*, treap*> split(treap *root, int key) {
	if (root == nullptr)  {
		return pair<treap*, treap*>(nullptr, nullptr);
	}
	
	if (root->x < key) {
		pair<treap*, treap*> tmp = split(root->right, key);
		root->setRight(tmp.first);
		return pair<treap*, treap*>(root, tmp.second);
	}
	else {
		pair<treap*, treap*> tmp = split(root->left, key);
		root->setLeft(tmp.second);
		return pair<treap*, treap*>(tmp.first, root);
	}
}

treap* insert(treap *root, treap *node) {
	if (root == nullptr) {
		return node;
	} 

	if (root->y < node->y) {
		pair<treap*, treap*> tmp = split(root, node->x);
		node->setLeft(tmp.first);
		node->setRight(tmp.second);
		return node;
	}
	
	if (root->x < node->x) {
		root->setRight(insert(root->right, node));
	}
	else {
		root->setLeft(insert(root->left, node));
	}
	return root;
}

treap* merge(treap *a, treap *b) {
	if (a == nullptr) return b;
	if (b == nullptr) return a;

	if (a->y > b->y) {
		a->setRight(merge(a->right, b));
		return a;
	}
	else {
		b->setLeft(merge(a, b->left));
		return b;
	}
}

bool check(treap* root, int key) {
	if (root == nullptr)
		return false;
	if (root->left != nullptr && key < root->x) {
		return check(root->left, key);
	}
	if (root->right != nullptr && key > root->x) {
		return check(root->right, key);
	}
	return root->x == key;
}

treap* del(treap* root, int key) {
	if (root == nullptr) return nullptr;

	if (root->x == key) {
		treap *tmp = merge(root->left, root->right);
		return tmp;
	}

	if (root->x < key) {
		root->setRight(del(root->right, key));
	}
	else {
		root->setLeft(del(root->left, key));
	}
	return root;
}

treap* next(treap* in, int key) {
	treap *suc = nullptr, *cur = in;
	while (cur != nullptr) {
		if (cur->x > key) {
			suc = cur;
			cur = cur->left;
		} else {
			cur = cur->right;
		}
	}
	return suc;
}

treap* prev(treap* in, int key) {
	treap *suc = nullptr, *cur = in;
	while (cur != nullptr) {
		if (cur->x < key) {
			suc = cur;
			cur = cur->right;
		} else {
			cur = cur->left;
		}
	}
	return suc;
}

void sout(treap* in) {
	if (in == nullptr)
		return;
	cout << in->x << " " << in->y << endl;
	cout << "go left" << endl;
	sout(in->left);
	cout << "go right" << endl;
	sout(in->right);
}

int x;
string s;

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	while (cin >> s) {
		cin >> x;
		if (s == "insert") {
			if (!check(root, x))
				root = insert(root, new treap(x));
			continue;
		}
		if (s == "delete") {
				root = del(root, x);
				continue;
		}
		if (s == "exists") {
				if (check(root, x)) {
					cout << "true" << endl;
				} else {
					cout << "false" << endl;
				}
				continue;
		}
		if (s == "next") {
			treap *res = next(root, x);
			if (res == nullptr)
				cout << "none" << endl;
			else 
				cout << res->x << endl;
			continue;
		}
		if (s == "prev") {
			treap *res = prev(root, x);
			if (res == nullptr)
				cout << "none" << endl;
			else 
				cout << res->x << endl;
			continue;
		}
  	}
	return 0;
}
