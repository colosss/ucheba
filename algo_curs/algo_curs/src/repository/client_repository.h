#ifndef REPOSITORY_CLIENT_REPOSITORY_H
#define REPOSITORY_CLIENT_REPOSITORY_H

#include "domain/client.h"
#include "structures/avltree.h"
#include <string>
#include <vector>

class ClientRepository {
private:
    AvlTree<Client> tree;

public:
    ClientRepository();

    bool add(const Client& client);
    bool remove(const std::string& licenseNumber);
    Client* find(const std::string& licenseNumber);
    const Client* find(const std::string& licenseNumber) const;
    bool exists(const std::string& licenseNumber) const;
    void clear();
    size_t size() const;

    std::vector<Client> getAll() const;

    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;

    void printStructure() const;
};

#endif
