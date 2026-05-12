#include <iostream>

using namespace std;

struct Node{
    int key;
    Node* left;
    Node* right;
    Node* parent;
    unsigned int height=1;
    Node(int k): key(k) {}
};

int height(Node* node) {
    return node ? node->height : 0;
}

int balanceFactor(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

void updateHeight(Node* node) {
    if (node) {
        node->height = 1 + max(height(node->left), height(node->right));
    }
}

Node* rotateRight(Node* n){
    Node* newRoot= n->left;
    Node* temp= newRoot->right;
    newRoot->right= n;
    n->left= temp;
    newRoot->parent= n->parent;
    n->parent= newRoot;
    if(temp) temp->parent= n;
    if (newRoot->parent) {
        if (newRoot->parent->left == n) newRoot->parent->left = newRoot;
        else newRoot->parent->right = newRoot;
    }
    updateHeight(n);
    updateHeight(newRoot);
    return newRoot;
}

Node* rotateLeft(Node* n){
    Node* newRoot= n->right;
    Node* temp= newRoot->left;
    newRoot->left= n;
    n->right= temp;
    newRoot->parent= n->parent;
    n->parent= newRoot;
    if(temp) temp->parent= n;
    if (newRoot->parent) {
        if (newRoot->parent->left == n) newRoot->parent->left = newRoot;
        else newRoot->parent->right = newRoot;
    }
    updateHeight(n);
    updateHeight(newRoot);
    return newRoot;
}

Node* balance(Node*& node){
    if (!node) return node;
    updateHeight(node);
    int bf= balanceFactor(node);
    if (bf > 1) {
        if (balanceFactor(node->left) < 0) {
            node->left= rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    else if (bf < -1) {
        if (balanceFactor(node->right) > 0) {
            node->right= rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node;
}

Node* addNode(Node*& node, int key) {
    if (!node) return new Node(key);
    if (key < node->key) {
        node->left= addNode(node->left, key);
        node->left->parent= node;
    }
    else if (key > node->key) {
        node->right= addNode(node->right, key);
        node->right->parent= node;
    }
    return balance(node);
}

Node* findElement(Node* node, int key) {
    if (!node) return nullptr;
    if (key < node->key) return findElement(node->left, key);
    else if (key > node->key) return findElement(node->right, key);
    else return node;
}

Node* findMin(Node* node) {
    while (node->left) node= node->left;
    return node;
}

Node* removeNode(Node*& node, int key) {
    if (!node) return node;
    if (key < node->key) {
        node->left= removeNode(node->left, key);
        if (node->left) node->left->parent= node;
    }
    else if (key > node->key) {
        node->right= removeNode(node->right, key);
        if (node->right) node->right->parent= node;
    }
    else {
        if (!node->left || !node->right) {
            Node* temp= node->left ? node->left : node->right;
            if (!temp) {
                temp= node;
                node= nullptr;
            }
            else {
                *node= *temp;
            }
            delete temp;
        }
        else {
            Node* temp= findMin(node->right);
            node->key= temp->key;
            node->right= removeNode(node->right, temp->key);
            if (node->right) node->right->parent= node;
        }
    }
    if (!node) return node;
    return balance(node);
}

