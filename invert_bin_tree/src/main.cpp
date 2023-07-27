#include <iostream>
#include "tree.h"

Node *createTree()
{
	auto root = new Node(2); 
	root->left = new Node(1); 
	root->right = new Node(4); 
	root->right->left = new Node(3); 
	root->right->right = new Node(5);

	return root;
}

void treeDemo()
{
    auto n = createTree();
    n->printInOrder();

    std::cout << std::endl << "Inverted:" << std::endl;

    n->invert();
    n->printInOrder();
}

int main(int argc, char** argv)
{
    std::cout << "Invert binary tree..." << std::endl;
    
    treeDemo();
    
    return 0;
}
