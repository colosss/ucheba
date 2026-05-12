#ifndef STRUCTURES_HASH_TABLE_H
#define STRUCTURES_HASH_TABLE_H

#include <functional>
#include <iostream>
#include <string>
#include <vector>

// Хеш-таблица с открытым хешированием: каждая ячейка хранит цепочку элементов.
template <typename T>
class HashTable {
private:
    struct Node {
        std::string key;
        T value;
        Node* next = nullptr;
        Node(std::string key, const T& value) : key(std::move(key)), value(value) {}
    };

    std::vector<Node*> buckets;
    std::function<std::string(const T&)> keyExtractor;
    size_t count = 0;

    size_t hashKey(const std::string& key) const {
        unsigned long hash = 0;
        for (unsigned char ch : key) hash = hash * 131 + ch;
        return buckets.empty() ? 0 : hash % buckets.size();
    }

public:
    explicit HashTable(size_t bucketCount, std::function<std::string(const T&)> keyExtractor)
        : buckets(bucketCount, nullptr), keyExtractor(std::move(keyExtractor)) {}

    ~HashTable() { clear(); }

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    bool insert(const T& value) {
        const std::string key = keyExtractor(value);
        size_t index = hashKey(key);
        Node* current = buckets[index];
        while (current) {
            if (current->key == key) return false;
            current = current->next;
        }
        Node* created = new Node(key, value);
        created->next = buckets[index];
        buckets[index] = created;
        ++count;
        return true;
    }

    bool update(const T& value) {
        const std::string key = keyExtractor(value);
        T* found = find(key);
        if (!found) return false;
        *found = value;
        return true;
    }

    T* find(const std::string& key) {
        size_t index = hashKey(key);
        Node* current = buckets[index];
        while (current) {
            if (current->key == key) return &current->value;
            current = current->next;
        }
        return nullptr;
    }

    const T* find(const std::string& key) const {
        size_t index = hashKey(key);
        Node* current = buckets[index];
        while (current) {
            if (current->key == key) return &current->value;
            current = current->next;
        }
        return nullptr;
    }

    bool remove(const std::string& key) {
        size_t index = hashKey(key);
        Node* current = buckets[index];
        Node* previous = nullptr;
        while (current) {
            if (current->key == key) {
                if (previous) previous->next = current->next;
                else buckets[index] = current->next;
                delete current;
                --count;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    void clear() {
        for (Node*& bucket : buckets) {
            Node* current = bucket;
            while (current) {
                Node* next = current->next;
                delete current;
                current = next;
            }
            bucket = nullptr;
        }
        count = 0;
    }

    size_t size() const { return count; }
    bool empty() const { return count == 0; }
    size_t bucketCount() const { return buckets.size(); }

    std::vector<T> toVector() const {
        std::vector<T> result;
        result.reserve(count);
        for (Node* bucket : buckets) {
            Node* current = bucket;
            while (current) {
                result.push_back(current->value);
                current = current->next;
            }
        }
        return result;
    }

    template <typename Func>
    void forEach(Func func) const {
        for (Node* bucket : buckets) {
            Node* current = bucket;
            while (current) {
                func(current->value);
                current = current->next;
            }
        }
    }

    void printStructure() const {
        std::cout << "Хеш-таблица, открытое хеширование, цепочки:" << std::endl;
        for (size_t i = 0; i < buckets.size(); ++i) {
            std::cout << i << ": ";
            Node* current = buckets[i];
            if (!current) std::cout << "empty";
            while (current) {
                std::cout << current->key;
                if (current->next) std::cout << " -> ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
};

#endif
