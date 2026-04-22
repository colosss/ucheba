#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <vector>
using namespace std;

int sred = 0;
int countSteps = 0;
int znach = 0;
int countLeafs = 0;
vector<int> keysToDelete;

struct Tree {
    int key;
    Tree* left = nullptr;
    Tree* right = nullptr;
    Tree* parent = nullptr;
    unsigned int height = 1;
    Tree(int k) : key(k) {}
};

int height(Tree* t) {
    return t ? t->height : 0;
}

int balanceFactor(Tree* t) {
    if (t) return height(t->left) - height(t->right);
    return 0;
}

void updateHeight(Tree*& t) {
    if (t) t->height = max(height(t->left), height(t->right)) + 1;
}

Tree* rotateRight(Tree* t) {
    Tree* q = t->left;
    Tree* B = q->right;
    q->right = t;
    t->left = B;
    q->parent = t->parent;
    t->parent = q;
    if (B) B->parent = t;
    if (q->parent) {
        if (q->parent->left == t) q->parent->left = q;
        else if (q->parent->right == t) q->parent->right = q;
    }
    updateHeight(t);
    updateHeight(q);
    return q;
}

Tree* rotateLeft(Tree* t) {
    Tree* q = t->right;
    Tree* B = q->left;
    q->left = t;
    t->right = B;
    q->parent = t->parent;
    t->parent = q;
    if (B) B->parent = t;
    if (q->parent) {
        if (q->parent->left == t) q->parent->left = q;
        else if (q->parent->right == t) q->parent->right = q;
    }
    updateHeight(t);
    updateHeight(q);
    return q;
}

Tree* balance(Tree*& t) {
    if (!t) return t;
    updateHeight(t);
    int bf = balanceFactor(t);
    if (bf > 1) {
        if (balanceFactor(t->left) < 0) {
            t->left = rotateLeft(t->left);
        }
        return rotateRight(t);
    }
    else if (bf < -1) {
        if (balanceFactor(t->right) > 0) {
            t->right = rotateRight(t->right);
        }
        return rotateLeft(t);
    }
    return t;
}

Tree* addNode(Tree*& t, int k) {
    if (t) {
        if (k < t->key) {
            t->left = addNode(t->left, k);
            if (t->left) t->left->parent = t;
        }
        else if (k > t->key) {
            t->right = addNode(t->right, k);
            if (t->right) t->right->parent = t;
        }
        else return t;
        updateHeight(t);
    }
    else {
        t = new Tree(k);
        return t;
    }
    return balance(t);
}

Tree* findElement(Tree* t, int k) {
    if (!t) return nullptr;
    if (k < t->key) return findElement(t->left, k);
    else if (k > t->key) return findElement(t->right, k);
    else return t;
}

Tree* findMin(Tree* t) {
    while (t && t->left) t = t->left;
    return t;
}

Tree* deleteNode(Tree*& t, int k) {
    if (!t) return t;
    if (k < t->key) {
        t->left = deleteNode(t->left, k);
        if (t->left) t->left->parent = t;
    }
    else if (k > t->key) {
        t->right = deleteNode(t->right, k);
        if (t->right) t->right->parent = t;
    }
    else {
        if (!t->left || !t->right) {
            Tree* temp = t->left ? t->left : t->right;
            if (!temp) {
                delete t;
                t = nullptr;
            }
            else {
                temp->parent = t->parent;
                delete t;
                t = temp;
            }
        }
        else {
            Tree* min = findMin(t->right);
            t->key = min->key;
            t->right = deleteNode(t->right, min->key);
            if (t->right) t->right->parent = t;
        }
    }
    if (!t) return t;
    return balance(t);
}

void printTreeBox(Tree* t, string prefix = "", bool isRight = true) {
    if (!t) return;
    printTreeBox(t->right, prefix + (isRight ? "    " : "│   "), true);
    cout << prefix;
    cout << (isRight ? "┌── " : "└── ");
    cout << t->key << endl;
    printTreeBox(t->left, prefix + (isRight ? "│   " : "    "), false);
}

void collectLeafSum(Tree* t) {
    if (!t) return;
    if (!t->left && !t->right) {
        znach += t->key;
        countLeafs++;
    }
    collectLeafSum(t->left);
    collectLeafSum(t->right);
}

void subtractAverage(Tree* t) {
    if (!t) return;
    t->key = (t->key - sred >= 0) ? t->key - sred : 0;
    subtractAverage(t->left);
    subtractAverage(t->right);
}

void collectMultiplesOfThree(Tree* t) {
    if (!t) return;
    if (t->key % 3 == 0) {
        keysToDelete.push_back(t->key);
    }
    collectMultiplesOfThree(t->left);
    collectMultiplesOfThree(t->right);
}

void treeMove(Tree* t, void func(Tree*)) {
    if (!t) return;
    queue<Tree*> q;
    q.push(t);
    while (!q.empty()) {
        countSteps++;
        Tree* current = q.front();
        q.pop();
        func(current);
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    cout << "Steps: " << countSteps << endl;
    countSteps = 0;
}

void func3(Tree*& root, bool flag_draw = true) {
    if (!root) return;

    znach = 0;
    countLeafs = 0;
    collectLeafSum(root);
    if (countLeafs == 0) return;
    sred = znach / countLeafs;
    cout << "Srednee znachenie listev: " << sred << endl;

    subtractAverage(root);

    keysToDelete.clear();
    collectMultiplesOfThree(root);

    for (int k : keysToDelete) {
        cout << "Udalyaem element: " << k << endl;
        root = deleteNode(root, k);
    }

    if (flag_draw) {
        printTreeBox(root);
    }
}

int main() {
    srand(time(NULL));
    int count = 0;
    bool cikl = true;
    int key = 0;
    Tree* tree = nullptr;
    tree = addNode(tree, rand() % 100);

    while (cikl) {
        switch (count) {
        case 0:
            cout << "***************************************************" << endl;
            cout << "1-add, 2-delete, 3-Find/Print, 4-Functions, 5-Exit" << endl;
            cin >> count;
            break;

        case 1:
            cout << "***************************************************" << endl;
            cout << "1-addElement, 2-AddRandom, 3-Back, 4-Exit" << endl;
            cin >> count;
            count = (count == 3) ? 0 : (count == 4) ? 5 : count + 10;
            break;

        case 2:
            cout << "***************************************************" << endl;
            cout << "1-deleteElement, 2-deleteRandomElement, 3-Back, 4-Exit" << endl;
            cin >> count;
            count = (count == 3) ? 0 : (count == 4) ? 5 : count + 20;
            break;

        case 3:
            cout << "***************************************************" << endl;
            cout << "1-FindElement, 2-PrintTree, 3-Back, 4-Exit" << endl;
            cin >> count;
            count = (count == 3) ? 0 : (count == 4) ? 5 : count + 30;
            break;

        case 4:
            cout << "***************************************************" << endl;
            cout << "1-FuncWithTreeDraw, 2-Func, 3-Back, 4-Exit" << endl;
            cin >> count;
            count = (count == 3) ? 0 : (count == 4) ? 5 : count + 40;
            break;

        case 5:
            cikl = false;
            count = 0;
            break;

        case 11:
            cout << "Enter key to add: ";
            cin >> key;
            tree = addNode(tree, key);
            count = 0;
            break;

        case 12:
            cout << "How many random elements to add?: ";
            int n;
            cin >> n;
            for (int i = 0; i < n; i++) {
                key = rand() % 100;
                tree = addNode(tree, key);
                cout << "Added: " << key << endl;
            }
            count = 0;
            break;

        case 21:
            cout << "Enter key to delete: ";
            cin >> key;
            tree = deleteNode(tree, key);
            count = 0;
            break;

        case 22:
            key = rand() % 100;
            tree = deleteNode(tree, key);
            cout << "Popytka udalit sluchayniy element: " << key << endl;
            count = 0;
            break;

        case 31:
            cout << "Enter key to find: ";
            cin >> key;
            {
                Tree* found = findElement(tree, key);
                if (found) cout << "Element nayden: " << found->key << endl;
                else cout << "Element ne nayden" << endl;
            }
            count = 0;
            break;

        case 32:
            cout << "Box representation:" << endl;
            printTreeBox(tree);
            count = 0;
            break;

        case 41:
            cout << "Function with tree drawing:" << endl;
            func3(tree, true);
            count = 0;
            break;

        case 42:
            cout << "Function without tree drawing:" << endl;
            func3(tree, false);
            count = 0;
            break;

        default:
            cout << "Necorrectniy vvod, povtorite vvod zanovo" << endl;
            count = 0;
            break;
        }
        cout << endl;
    }
    return 0;
}