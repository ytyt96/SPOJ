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

	int minDiff(int i, int j){
		return minDiff(root, i, j, 0, size - 1);
	}

	int maxDiff(int i, int j){
		return searchKth(j) - searchKth(i);
	}

	int searchKth(int K){
		return searchKth(root, K, 0, size - 1);
	}

private:
	struct node_t{
		int elem;
		shared_ptr<node_t> left, right;
		int priority;
		int minDiff;
		int minElem, maxElem;
		int size;
	};

	shared_ptr<node_t> root;
	int size = 0;

	int minDiff(shared_ptr<node_t> node, int i, int j, int L, int R){
		if (!node)
			return INT_MAX;
		if (L >= i && R <= j)
			return node->minDiff;
		if (i > R || j < L)
			return INT_MAX;

		int curr = L + (node->left ? node->left->size : 0);
		int p1 = minDiff(node->left, i, j, L, curr - 1);
		int p2 = minDiff(node->right, i, j, curr + 1, R);
		int p3 = INT_MAX, p4 = INT_MAX;
		if (curr > i && curr > L && curr <= j)
            p3 = node->elem - node->left->maxElem;
		if (curr < j && curr < R && curr >= i)
            p4 = node->right->minElem - node->elem;
			
		return min(min(p1, p2), min(p3, p4));
	}
		
	int searchKth(shared_ptr<node_t> node, int K, int L, int R){
		int curr = (node->left ? node->left->size : 0) + L;

		if (curr == K)
			return node->elem;
		else if (curr > K)
			return searchKth(node->left, K, L, curr - 1);
		else
			return searchKth(node->right, K, curr + 1, R);
	}

	inline void updateNode(shared_ptr<node_t> node){
		node->size = (node->left ? node->left->size : 0) + 1 + (node->right ? node->right->size : 0);

		node->minElem = node->left ? node->left->minElem : node->elem;
		node->maxElem = node->right ? node->right->maxElem : node->elem;

		node->minDiff = INT_MAX;
		if (node->left){
			node->minDiff = min(node->minDiff, node->left->minDiff);
			node->minDiff = min(node->minDiff, node->elem - node->left->maxElem);
		}
		if (node->right){
			node->minDiff = min(node->minDiff, node->right->minDiff);
			node->minDiff = min(node->minDiff, node->right->minElem - node->elem);
		}

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
			node->minDiff = INT_MAX;
			node->minElem = node->maxElem = elem;
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
		int i, j;
		case 'I':
			scanf("%d", &i);
			Treap.insert(i);
			break;
		case 'D':
			scanf("%d", &i);
			Treap.remove(i);
			break;
		case 'N':
			scanf("%d %d", &i, &j);
			printf("%d\n", i < j ? Treap.minDiff(i, j) : -1);
			break;
		case 'X':
			scanf("%d %d", &i, &j);
			printf("%d\n", i < j ? Treap.maxDiff(i, j) : -1);
			break;
		}
	}
}
