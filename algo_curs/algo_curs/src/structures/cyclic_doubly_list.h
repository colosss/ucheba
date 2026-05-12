#ifndef STRUCTURES_CYCLIC_DOUBLY_LIST_H
#define STRUCTURES_CYCLIC_DOUBLY_LIST_H

#include <functional>
#include <iostream>
#include <utility>
#include <vector>

// Циклический двунаправленный список. Для упорядочивания используется шейкерная сортировка.
template <typename T>
class CyclicDoublyList {
private:
    struct Node {
        T value;
        Node* next = nullptr;
        Node* prev = nullptr;
        explicit Node(const T& value) : value(value) {}
    };

    Node* head = nullptr;
    size_t count = 0;

    Node* nodeAt(size_t index) const {
        if (!head || index >= count) return nullptr;
        Node* current = head;
        for (size_t i = 0; i < index; ++i) current = current->next;
        return current;
    }

public:
    ~CyclicDoublyList() { clear(); }

    CyclicDoublyList() = default;
    CyclicDoublyList(const CyclicDoublyList&) = delete;
    CyclicDoublyList& operator=(const CyclicDoublyList&) = delete;

    void pushBack(const T& value) {
        Node* created = new Node(value);
        if (!head) {
            head = created;
            head->next = head;
            head->prev = head;
        } else {
            Node* tail = head->prev;
            tail->next = created;
            created->prev = tail;
            created->next = head;
            head->prev = created;
        }
        ++count;
    }

    bool removeIf(std::function<bool(const T&)> predicate) {
        if (!head) return false;
        Node* current = head;
        for (size_t i = 0; i < count; ++i) {
            Node* next = current->next;
            if (predicate(current->value)) {
                if (count == 1) {
                    delete current;
                    head = nullptr;
                    count = 0;
                    return true;
                }
                current->prev->next = current->next;
                current->next->prev = current->prev;
                if (current == head) head = current->next;
                delete current;
                --count;
                return true;
            }
            current = next;
        }
        return false;
    }

    T* findIf(std::function<bool(const T&)> predicate) {
        if (!head) return nullptr;
        Node* current = head;
        for (size_t i = 0; i < count; ++i) {
            if (predicate(current->value)) return &current->value;
            current = current->next;
        }
        return nullptr;
    }

    const T* findIf(std::function<bool(const T&)> predicate) const {
        if (!head) return nullptr;
        Node* current = head;
        for (size_t i = 0; i < count; ++i) {
            if (predicate(current->value)) return &current->value;
            current = current->next;
        }
        return nullptr;
    }

    bool anyIf(std::function<bool(const T&)> predicate) const {
        return findIf(predicate) != nullptr;
    }

    std::vector<T> findAllIf(std::function<bool(const T&)> predicate) const {
        std::vector<T> result;
        if (!head) return result;
        Node* current = head;
        for (size_t i = 0; i < count; ++i) {
            if (predicate(current->value)) result.push_back(current->value);
            current = current->next;
        }
        return result;
    }

    void clear() {
        if (!head) return;
        Node* current = head->next;
        while (current != head) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        delete head;
        head = nullptr;
        count = 0;
    }

    size_t size() const { return count; }
    bool empty() const { return count == 0; }

    std::vector<T> toVector() const {
        std::vector<T> result;
        result.reserve(count);
        if (!head) return result;
        Node* current = head;
        for (size_t i = 0; i < count; ++i) {
            result.push_back(current->value);
            current = current->next;
        }
        return result;
    }

    template <typename Func>
    void forEach(Func func) const {
        if (!head) return;
        Node* current = head;
        for (size_t i = 0; i < count; ++i) {
            func(current->value);
            current = current->next;
        }
    }

    void shakerSort(std::function<bool(const T&, const T&)> less) {
        if (count < 2) return;
        bool swapped = true;
        size_t start = 0;
        size_t end = count - 1;

        while (swapped) {
            swapped = false;
            for (size_t i = start; i < end; ++i) {
                Node* left = nodeAt(i);
                Node* right = left->next;
                if (less(right->value, left->value)) {
                    std::swap(left->value, right->value);
                    swapped = true;
                }
            }
            if (!swapped) break;
            swapped = false;
            if (end == 0) break;
            --end;
            for (size_t i = end; i > start; --i) {
                Node* left = nodeAt(i - 1);
                Node* right = left->next;
                if (less(right->value, left->value)) {
                    std::swap(left->value, right->value);
                    swapped = true;
                }
            }
            ++start;
        }
    }

    void printStructure(std::function<std::string(const T&)> key) const {
        std::cout << "Циклический двунаправленный список:" << std::endl;
        if (!head) {
            std::cout << "empty" << std::endl;
            return;
        }
        Node* current = head;
        for (size_t i = 0; i < count; ++i) {
            std::cout << key(current->value);
            if (i + 1 < count) std::cout << " <-> ";
            current = current->next;
        }
        std::cout << " <-> first" << std::endl;
    }
};

#endif
