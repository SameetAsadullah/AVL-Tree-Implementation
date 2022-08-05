#pragma once
#include<iostream>
using namespace std;

template<class DT>
class Node {
public:
	DT data;
	Node* left;
	Node* right;
	int height;

	Node() :left(NULL), right(NULL), height(-1) {
	}
};

template<class DT>
class AVLTree {
	Node<DT>* root;

	Node<DT>* SingleRotateWithRight(Node<DT>* K1) {
		Node<DT>* K2;
		K2 = K1->right; // K1: node whose balance factor is violated
		K1->right = K2->left;
		K2->left = K1;
		K1->height = getMax(calculateHeight(K1->left), calculateHeight(K1->right)) + 1;
		K2->height = getMax(calculateHeight(K2->right), K1->height) + 1;
		return K2; /* New root */
	}

	Node<DT>* SingleRotateWithLeft(Node<DT>* K1) {
		Node<DT>* K2;
		K2 = K1->left; // K1: node whose balance factor is violated
		K1->left = K2->right;
		K2->right = K1;
		K1->height = getMax(calculateHeight(K1->left), calculateHeight(K1->right)) + 1;
		K2->height = getMax(calculateHeight(K2->left), K1->height) + 1;
		return K2; /* New root */
	}

	Node<DT>* DoubleRotateWithRight(Node<DT>* K1)
	{
		/* RR rotation between K3 and K2 */
		K1->right = SingleRotateWithLeft(K1->right);
		/* LL rotation between K1 and K2 */
		return SingleRotateWithRight(K1);
	}

	Node<DT>* DoubleRotateWithLeft(Node<DT>* K3)
	{
		/* LL rotation between K1 and K2 */
		K3->left = SingleRotateWithRight(K3->left);
		/* RR rotation between K3 and K2 */
		return SingleRotateWithLeft(K3);
	}

	Node<DT>* traverseForInserting(Node<DT>* temp, const DT& newDataItem) {
		if (temp == NULL) {
			temp = new Node<DT>;
			temp->data = newDataItem;
			return temp;
		}

		else if (newDataItem < temp->data) {
			temp->left = traverseForInserting(temp->left, newDataItem);

			if (calculateHeight(temp->left) - calculateHeight(temp->right) == 2)
				if (newDataItem < temp->left->data)
					temp = SingleRotateWithLeft(temp); // RR rotation
				else
					temp = DoubleRotateWithLeft(temp); // RL rotation
		}

		else if (newDataItem > temp->data) {
			temp->right = traverseForInserting(temp->right, newDataItem);

			if (calculateHeight(temp->right) - calculateHeight(temp->left) == 2)
				if (newDataItem > temp->right->data)
					temp = SingleRotateWithRight(temp); // LL rotation
				else
					temp = DoubleRotateWithRight(temp); // LR rotation
		}

		else {
			cout << "Duplicates are present" << endl;
		}

		temp->height = getMax(calculateHeight(temp->left), calculateHeight(temp->right)) + 1;
		return temp;
	}

	bool traverseForSearching(Node<DT>* temp, const DT& searchDataItem) {
		if (temp == NULL) {
			return false;
		}

		else if (searchDataItem == temp->data) {
			return true;
		}

		else if (searchDataItem < temp->data) {
			return traverseForSearching(temp->left, searchDataItem);
		}

		else if (searchDataItem > temp->data) {
			return traverseForSearching(temp->right, searchDataItem);
		}
	}

	int getMax(const int& num1, const int& num2) {
		if (num1 == num2) {
			return num1;
		}

		else if (num1 > num2) {
			return num1;
		}

		return num2;
	}

	int calculateHeight(Node<DT>* temp) {
		if (temp == NULL) {
			return -1;
		}
		int leftHeight = calculateHeight(temp->left);
		int rightHeight = calculateHeight(temp->right);

		return getMax(leftHeight, rightHeight) + 1;
	}

	void deleteNode(Node<DT>*& nodePtr) {
		Node<DT>* temp;

		if (nodePtr->right == NULL) {
			temp = nodePtr;
			nodePtr = nodePtr->left;
			delete temp;
		}

		else if (nodePtr->left == NULL) {
			temp = nodePtr;
			nodePtr = nodePtr->right;
			delete temp;
		}

		else {
			temp = nodePtr->right;

			while (temp->left != NULL) {
				temp = temp->left;
			}

			nodePtr->data = temp->data;

			Node<DT>* prev = nodePtr->right;

			if (prev->left != NULL) {

				while (prev->left != temp) {
					prev = prev->left;
				}

				if (temp->right == NULL) {
					delete temp;
					prev->left = NULL;
				}

				else {
					prev->left = temp->right;
					delete temp;
				}
			}

			else {
				delete temp;
				nodePtr->right = NULL;
			}
		}
	}

	bool traverseForRemove(Node<DT>*& temp, const DT& deleteDataItem) {
		if (temp == NULL) {
			return false;
		}

		else if (temp->data == deleteDataItem) {
			deleteNode(temp);
			return true;
		}

		else if (deleteDataItem < temp->data) {
			return traverseForRemove(temp->left, deleteDataItem);
		}

		else if (deleteDataItem > temp->data) {
			return traverseForRemove(temp->right, deleteDataItem);
		}

		temp->height = getMax(calculateHeight(temp->left), calculateHeight(temp->right)) + 1;

		if (calculateHeight(temp->left) - calculateHeight(temp->right) == 2)
		{
			if (calculateHeight(temp->left->left) - calculateHeight(temp->left->right) == 1)
				temp = SingleRotateWithLeft(temp);
			else
				temp = DoubleRotateWithLeft(temp);
		}

		else if (calculateHeight(temp->right) - calculateHeight(temp->left) == 2)
		{
			if (calculateHeight(temp->right->right) - calculateHeight(temp->right->left) == 1)
				temp = SingleRotateWithRight(temp);

			else
				temp = DoubleRotateWithRight(temp);
		}
	}

public:
	AVLTree() : root(NULL) {
	}

	Node<DT>* getRoot() {
		return root;
	}

	void insert(const DT& newDataItem) {
		root = traverseForInserting(root, newDataItem);
	}

	bool retrieve(const DT& searchDataItem) {
		return traverseForSearching(root, searchDataItem);
	}

	bool isEmpty() {
		if (root == NULL) {
			return true;
		}
		return false;
	}

	int getHeight() {
		return calculateHeight(root);
	}

	bool remove(const DT& deleteDataItem) {
		return traverseForRemove(root, deleteDataItem);
	}

	void inOrderDisplay(Node<DT>* temp) {
		if (temp != NULL) {
			inOrderDisplay(temp->left);
			cout << temp->data << " ";
			inOrderDisplay(temp->right);
		}
	}

	void preOrderDisplay(Node<DT>* temp) {
		if (temp != NULL) {
			cout << temp->data << " ";
			preOrderDisplay(temp->left);
			preOrderDisplay(temp->right);
		}
	}

	void postOrderDisplay(Node<DT>* temp) {
		if (temp != NULL) {
			postOrderDisplay(temp->left);
			postOrderDisplay(temp->right);
			cout << temp->data << " ";
		}
	}

	bool FullBinaryTree(Node<DT>* temp) {

		if (!temp) {
			return true;
		}
		if (!(temp->right) && !(temp->left)) {
			return true;
		}
		else if (temp->right != NULL && temp->left != NULL) {
			FullBinaryTree(temp->right);
			FullBinaryTree(temp->left);
		}
		else {
			return false;
		}
	}

	bool PerfectBinaryTree(Node<DT>* temp) {

		bool check = FullBinaryTree(temp);

		if (temp == NULL) {
			return 1;
		}

		int left = PerfectBinaryTree(temp->left);
		int right = PerfectBinaryTree(temp->right);

		if (check) {
			if ((left == right)) {
				return true;
			}
		}
		else {
			return false;
		}
	}

	int Count(Node<DT>* temp) {
		if (!temp) {
			return 0;
		}

		return 1 + Count(temp->left) + Count(temp->right);
	}

	bool CompleteBinaryTree(Node<DT>* temp, int curr = 0)
	{

		int total = Count(root);
		if (!temp) {
			return true;
		}
		if (total <= curr) {
			return false;
		}
		CompleteBinaryTree(temp->right, ((2 * curr) + 2));
		CompleteBinaryTree(temp->left, ((2 * curr) + 1));
	}

	bool BalancedBinaryTree(Node<DT>* temp) {

		if (!temp) {
			return 1;
		}

		int left = calculateHeight(temp->left);
		int right = calculateHeight(temp->right);

		if (abs(right - left) <= 1) {
			if (BalancedBinaryTree(temp->left)) {
				if (BalancedBinaryTree(temp->right)) {
					return true;
				}
			}
		}
		else {
			return false;
		}
	}

	bool DegenerateTree(Node<DT>* temp) {

		if (temp->left) {
			if (temp->right) {
				return false;
			}
			else {
				DegenerateTree(temp->left);
			}
		}
		else {
			if (temp->right) {
				DegenerateTree(temp->right);
			}
			else {
				return true;
			}
		}
	}

	~AVLTree() {
		while (root != NULL) {
			remove(root->data);
		}
	}
};