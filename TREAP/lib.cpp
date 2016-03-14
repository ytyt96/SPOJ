#include <iostream>
#include <cstdio>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

template<typename T>
class treap{
public:
	treap(){
		srand(time(0));
		root = nullptr;
	}

	void insert(const T& elem){
		insert(root, elem);	
	}

	void remove(const T& elem){
		remove(root, elem);
	}

	void print(){
		print(root);
		cout << "\n";
	}
	
private:
	struct node_t{
		T elem;
		shared_ptr<node_t> left, right;
		int priority;
	};

	void print(shared_ptr<node_t> node){
		if (node == nullptr)
			return;
		print(node->left);
		cout << node->elem << " ";
		print(node->right);
	}

	shared_ptr<node_t> root;

	shared_ptr<node_t> rotateLeft(shared_ptr<node_t> node){
		shared_ptr<node_t> right = node->right, rightLeft = right->left;
		right->left = node;
		node->right = rightLeft;
		return right;
	}

	shared_ptr<node_t> rotateRight(shared_ptr<node_t> node){
		shared_ptr<node_t> left = node->left, leftRight = left->right;
		left->right = node;
		node->left = leftRight;
		return left;
	}

	void insert(shared_ptr<node_t>& node, const T& elem){
		if (node == nullptr){
			node = make_shared<node_t>();
			node->elem = elem;
			node->left = node->right = nullptr;
			node->priority = rand();
			return;
		}
		// We do not allow multiple keys with the same value
		if (node->elem == elem)
			return;

		if (node->elem > elem){
			insert(node->left, elem);
			if (node->priority < node->left->priority)
				node = rotateRight(node);
		}else{
			insert(node->right, elem);
			if (node->priority < node->right->priority)
				node = rotateLeft(node);
		}
	}

	void remove(shared_ptr<node_t>& node, const T& elem){
		if (node == nullptr)
			return;
		
		if (node->elem == elem){
			if (!node->left && !node->right)
				node = nullptr;
			// Keep rotating until the node to be deleted becomes a leaf node.
			else if (!node->left || (node->left && node->right && 
				node->left->priority < node->right->priority)){
				node = rotateLeft(node);
				remove(node->left, elem);
			}
			else{
				node = rotateRight(node);
				remove(node->right, elem);
			}
		}
		else if (node->elem > elem)
			remove(node->left, elem);
		else
			remove(node->right, elem);
	}
};

