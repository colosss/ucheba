#ifndef STRUCTURES_AVLTREE_H
#define STRUCTURES_AVLTREE_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// АВЛ-дерево поиска. В проекте используется для клиентов, ключ - номер водительского удостоверения.
template <typename T>
class AvlTree {
private:
    struct Node {
        std::string key;
        T value;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        unsigned int height = 1;

        Node(std::string key, const T& value) : key(std::move(key)), value(value) {}
    };

    Node* root = nullptr;
    std::function<std::string(const T&)> keyExtractor;
    size_t count = 0;

    static unsigned int height(Node* node) { return node ? node->height : 0; }

    static int balanceFactor(Node* node) {
        return node ? static_cast<int>(height(node->left)) - static_cast<int>(height(node->right)) : 0;
    }

    static void updateHeight(Node* node) {
        if (node) node->height = std::max(height(node->left), height(node->right)) + 1;
    }

    Node* rotateRight(Node* node) {
        Node* newRoot = node->left;
        Node* temp = newRoot->right;

        newRoot->right = node;
        node->left = temp;

        newRoot->parent = node->parent;
        node->parent = newRoot;
        if (temp) temp->parent = node;

        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;
        Node* temp = newRoot->left;

        newRoot->left = node;
        node->right = temp;

        newRoot->parent = node->parent;
        node->parent = newRoot;
        if (temp) temp->parent = node;

        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    Node* balance(Node* node) {
        if (!node) return nullptr;
        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
                if (node->left) node->left->parent = node;
            }
            return rotateRight(node);
        }
        if (bf < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
                if (node->right) node->right->parent = node;
            }
            return rotateLeft(node);
        }
        return node;
    }

    Node* insert(Node* node, Node* parent, const std::string& key, const T& value, bool& inserted) {
        if (!node) {
            inserted = true;
            Node* created = new Node(key, value);
            created->parent = parent;
            return created;
        }
        if (key < node->key) {
            node->left = insert(node->left, node, key, value, inserted);
        } else if (key > node->key) {
            node->right = insert(node->right, node, key, value, inserted);
        } else {
            inserted = false;
            return node;
        }
        Node* balanced = balance(node);
        if (balanced) balanced->parent = parent;
        return balanced;
    }

    Node* findNode(Node* node, const std::string& key) const {
        if (!node) return nullptr;
        if (key < node->key) return findNode(node->left, key);
        if (key > node->key) return findNode(node->right, key);
        return node;
    }

    static Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, const std::string& key, bool& removed) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = remove(node->left, key, removed);
            if (node->left) node->left->parent = node;
        } else if (key > node->key) {
            node->right = remove(node->right, key, removed);
            if (node->right) node->right->parent = node;
        } else {
            removed = true;
            if (!node->left || !node->right) {
                Node* child = node->left ? node->left : node->right;
                if (child) child->parent = node->parent;
                delete node;
                return child;
            }
            Node* minRight = findMin(node->right);
            node->key = minRight->key;
            node->value = minRight->value;
            bool ignored = false;
            node->right = remove(node->right, minRight->key, ignored);
            if (node->right) node->right->parent = node;
        }

        return balance(node);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    template <typename Func>
    void traverseInOrder(Node* node, Func func) const {
        if (!node) return;
        traverseInOrder(node->left, func);
        func(node->value);
        traverseInOrder(node->right, func);
    }

    template <typename Func>
    void traversePostOrder(Node* node, Func func) const {
        if (!node) return;
        traversePostOrder(node->left, func);
        traversePostOrder(node->right, func);
        func(node->value);
    }

    void print(Node* node, int depth, const std::string& side) const {
        if (!node) return;
        print(node->right, depth + 1, "R");
        for (int i = 0; i < depth; ++i) std::cout << "    ";
        std::cout << side << ": " << node->key << " (h=" << node->height << ")" << std::endl;
        print(node->left, depth + 1, "L");
    }

public:
    explicit AvlTree(std::function<std::string(const T&)> keyExtractor)
        : keyExtractor(std::move(keyExtractor)) {}

    ~AvlTree() { clear(); }

    AvlTree(const AvlTree&) = delete;
    AvlTree& operator=(const AvlTree&) = delete;

    bool insert(const T& value) {
        bool inserted = false;
        root = insert(root, nullptr, keyExtractor(value), value, inserted);
        if (root) root->parent = nullptr;
        if (inserted) ++count;
        return inserted;
    }

    bool update(const T& value) {
        Node* node = findNode(root, keyExtractor(value));
        if (!node) return false;
        node->value = value;
        return true;
    }

    T* find(const std::string& key) {
        Node* node = findNode(root, key);
        return node ? &node->value : nullptr;
    }

    const T* find(const std::string& key) const {
        Node* node = findNode(root, key);
        return node ? &node->value : nullptr;
    }

    bool remove(const std::string& key) {
        bool removed = false;
        root = remove(root, key, removed);
        if (root) root->parent = nullptr;
        if (removed && count > 0) --count;
        return removed;
    }

    void clear() {
        clear(root);
        root = nullptr;
        count = 0;
    }

    size_t size() const { return count; }
    bool empty() const { return count == 0; }

    std::vector<T> toVectorInOrder() const {
        std::vector<T> result;
        result.reserve(count);
        traverseInOrder(root, [&result](const T& value) { result.push_back(value); });
        return result;
    }

    std::vector<T> toVectorPostOrder() const {
        std::vector<T> result;
        result.reserve(count);
        traversePostOrder(root, [&result](const T& value) { result.push_back(value); });
        return result;
    }

    template <typename Func>
    void forEachInOrder(Func func) const { traverseInOrder(root, func); }

    template <typename Func>
    void forEachPostOrder(Func func) const { traversePostOrder(root, func); }

    void printStructure() const {
        if (!root) {
            std::cout << "Дерево пусто." << std::endl;
            return;
        }
        print(root, 0, "Root");
    }
};

#endif
