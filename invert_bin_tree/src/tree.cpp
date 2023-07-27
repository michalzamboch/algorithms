#include <iostream>
#include "tree.h"

Node::Node() {
    this->left = nullptr;
    this->right = nullptr;
    this->value = 0;
}

Node::Node(int value) : Node() {
    this->value = value;
}

Node::~Node() {
    delete this->left;
    delete this->right;
}

void Node::printValue()
{
    std::cout << this->value << std::endl;
}

void Node::invert()
{
    this->innerInvert(this);
}

void Node::innerInvert(Node *node)
{
    if (node == nullptr)
    {
        return;
    }
    else
    {
        this->innerInvert(node->left);
        this->innerInvert(node->right);

        auto tmp = node->left;
        node->left = node->right;
        node->right = tmp;
    }
}

void Node::printInOrder()
{
    this->printInOrderInner(this);
}

void Node::printInOrderInner(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    this->printInOrderInner(node->left);
    node->printValue();
    this->printInOrderInner(node->right);
}
