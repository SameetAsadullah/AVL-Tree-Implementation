#include"AVLTree.h"
#include<iostream>
using namespace std;

int main() {
	AVLTree<int> t1;
	t1.insert(1);
	t1.insert(2);
	t1.insert(3);
	t1.insert(4);
	t1.insert(5);
	t1.insert(6);
	t1.insert(10);
	t1.insert(8);
	t1.insert(7);
	t1.insert(9);
	cout << "========== Post Order Display ===========" << endl;
	t1.postOrderDisplay(t1.getRoot());
	cout << endl << endl << "========== In Order Display ===========" << endl;
	t1.inOrderDisplay(t1.getRoot());
	cout << endl << endl << "Is Tree a Full Binary Tree: " << t1.FullBinaryTree(t1.getRoot()) << endl;
}