#include <iostream>
#include <cstdio>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

class treap{
public:
	treap(){
		srand(time(0));
		root = nullptr;
	}

	void insert(int elem){
		insert(root, elem);	
	}

	void remove(int elem){
		remove(root, elem);
	}

	int searchKth(int K){
		return searchKth(root, K, 0, size - 1);
	}

	int searchCount(int x){
		return searchCount(root, x, 0, size - 1) + 1;
	}

	int getSize() const{
		return size;
	}

private:
	struct node_t{
		int elem;
		shared_ptr<node_t> left, right;
		int priority;
		int size;
	};

	shared_ptr<node_t> root;
	int size = 0;

	int searchKth(shared_ptr<node_t> node, int K, int L, int R){
		int curr = (node->left ? node->left->size : 0) + L;

		if (curr == K)
			return node->elem;
		else if (curr > K)
			return searchKth(node->left, K, L, curr - 1);
		else
			return searchKth(node->right, K, curr + 1, R);
	}

	int searchCount(shared_ptr<node_t> node, int x, int L, int R){
		if (!node)
			return -1;
		int curr = (node->left ? node->left->size : 0) + L;
		if (node->elem == x)
			return curr - 1;
		if (node->elem > x){
			if (node->left)
				return searchCount(node->left, x, L, curr - 1);
			else
				return curr - 1;
		}
		else{
			if (node->right)
				return searchCount(node->right, x, curr + 1, R);
			else
				return curr;
		}
	}

	inline void updateNode(shared_ptr<node_t> node){
		node->size = (node->left ? node->left->size : 0) + 1 + (node->right ? node->right->size : 0);
	}

	shared_ptr<node_t> rotateLeft(shared_ptr<node_t> node){
		shared_ptr<node_t> right = node->right, rightLeft = right->left;
		right->left = node;
		node->right = rightLeft;
		
		updateNode(node);
		updateNode(right);

		return right;
	}

	shared_ptr<node_t> rotateRight(shared_ptr<node_t> node){
		shared_ptr<node_t> left = node->left, leftRight = left->right;
		left->right = node;
		node->left = leftRight;

		updateNode(node);
		updateNode(left);
		return left;
	}



	void insert(shared_ptr<node_t>& node, int elem){
		if (node == nullptr){
			node = make_shared<node_t>();
			node->elem = elem;
			node->left = node->right = nullptr;
			node->priority = rand();
			node->size = 1;
			size++;
			return;
		}
		// We do not allow multiple keys with the same value
		if (node->elem == elem)
			return;

		if (node->elem > elem){
			insert(node->left, elem);
			updateNode(node);

			if (node->priority < node->left->priority)
				node = rotateRight(node);
		}else{
			insert(node->right, elem);
			updateNode(node);
			if (node->priority < node->right->priority)
				node = rotateLeft(node);
		}
	}

	void remove(shared_ptr<node_t>& node, int elem){
		if (node == nullptr)
			return;
		
		if (node->elem == elem){
			if (!node->left && !node->right){
				node = nullptr;
				size--;
				return;
			}
			// Keep rotating until the node to be deleted becomes a leaf node.
			else if (!node->left || (node->left && node->right && 
				node->left->priority < node->right->priority)){
				node = rotateLeft(node);
				remove(node->left, elem);
				updateNode(node);
			}
			else{
				node = rotateRight(node);
				remove(node->right, elem);
				updateNode(node);
			}
		}
		else if (node->elem > elem){
			remove(node->left, elem);
			updateNode(node);
		}
		else{
			remove(node->right, elem);
			updateNode(node);
		}
	}
};

int main(){
	treap Treap;
	int Q;
	scanf("%d", &Q);
	while (Q--){
		char cmd;
		scanf(" %c ", &cmd);
		switch (cmd){
		int i;
		case 'I':
			scanf("%d", &i);
			Treap.insert(i);
			break;
		case 'D':
			scanf("%d", &i);
			Treap.remove(i);
			break;
		case 'K':
			scanf("%d", &i);
			if (i > Treap.getSize())
				printf("invalid\n");
			else
				printf("%d\n", Treap.searchKth(i - 1));
			break;
		case 'C':
			scanf("%d", &i);
			printf("%d\n", Treap.searchCount(i));
			break;
		}
	}
}
