#pragma once
using namespace std;
#include <iostream>


template <typename T>
struct TNode {
	T data;
	TNode<T>* left, * right;

	TNode(T _data, TNode<T>* _left = nullptr, TNode<T>* _right = nullptr) : data(_data), left(_left), right(_right) {};
};

template <typename T>
class BinTree {
private:
	TNode<T>* root;
	void copyTree(TNode<T>*&, TNode<T>* const&) const;
	void deleteTree(TNode<T>*&);
	void createTree(TNode<T>*&);
	void printTree(TNode<T>*) const;
public:
	BinTree();
	BinTree(BinTree<T> const&);
	BinTree<T>& operator=(BinTree<T> const&);
	~BinTree();

	void create();
	void createWithData(T const&, BinTree<T> const&, BinTree<T> const&);

	T getRootData() const;
	TNode<T>* getRootPtr() const;
	BinTree<T> getLeftTree() const;
	BinTree<T> getRightTree() const;

	bool isEmpty() const;
	void print() const;
};

template <typename T>
BinTree<T>::BinTree() {
	root = nullptr;
}

template <typename T>
BinTree<T>::BinTree(BinTree<T> const& t) {
	copyTree(root, t.root);
}

template <typename T>
BinTree<T>& BinTree<T>::operator=(BinTree<T> const& t) {
	if (this != &t) {
		deleteTree(root);
		copyTree(root, t.root);
	}
	return *this;
}

template <typename T>
BinTree<T>::~BinTree() {
	deleteTree(root);
}

template <typename T>
void BinTree<T>::copyTree(TNode<T>*& destRoot, TNode<T>* const& sourceRoot) const {
	if (sourceRoot == nullptr) {
		destRoot = nullptr;
		return;
	}
	destRoot = new TNode<T>(sourceRoot->data);
	copyTree(destRoot->left, sourceRoot->left);
	copyTree(destRoot->right, sourceRoot->right);
}

template <typename T>
void BinTree<T>::deleteTree(TNode<T>*& root) {
	if (root == nullptr)
		return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

template <typename T>
void BinTree<T>::createTree(TNode<T>*& root) {
	std::cout << "Enter root: ";
	T rootData;
	char answer;
	std::cin >> rootData;
	root = new TNode<T>(rootData);
	std::cout << "Add left tree for " << rootData << "(y/n): ";
	std::cin >> answer;
	if (answer == 'y')
		createTree(root->left);


	std::cout << "Add right tree for " << rootData << "(y/n): ";
	std::cin >> answer;
	if (answer == 'y')
		createTree(root->right);
}

template <typename T>
void BinTree<T>::create() {
	createTree(root);
}

template <typename T>
void BinTree<T>::createWithData(T const& x, BinTree<T> const& leftTree, BinTree<T> const& rightTree) {
	root = new TNode<T>(x);
	copyTree(root->left, leftTree.root);
	copyTree(root->right, rightTree.root);
}

template <typename T>
T BinTree<T>::getRootData() const {
	if (isEmpty()) {
		std::cerr << "Error: empty tree";
		return T();
	}

	return root->data;
}

template <typename T>
TNode<T>* BinTree<T>::getRootPtr() const {
	if (isEmpty()) {
		std::cerr << "Error: empty tree";
		return nullptr;
	}

	return root;
}

template <typename T>
BinTree<T> BinTree<T>::getLeftTree() const {
	BinTree<T> t;

	if (isEmpty()) {
		std::cerr << "Error: empty tree";
		return t;
	}

	copyTree(t.root, root->left);
	return t;
}

template <typename T>
BinTree<T> BinTree<T>::getRightTree() const {
	BinTree<T> t;

	if (isEmpty()) {
		std::cerr << "Error: empty tree";
		return t;
	}

	copyTree(t.root, root->right);
	return t;
}

template <typename T>
bool BinTree<T>::isEmpty() const {
	return root == nullptr;
}

template <typename T>
void BinTree<T>::print() const {
	printTree(root);
}

template <typename T>
void BinTree<T>::printTree(TNode<T>* root) const {
	if (root == nullptr)
		return;
	std::cout << root->data << ' ';
	printTree(root->left);
	printTree(root->right);
}