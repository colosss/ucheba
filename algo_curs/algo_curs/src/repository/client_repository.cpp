#include "repository/client_repository.h"
#include <fstream>

ClientRepository::ClientRepository()
    : tree([](const Client& client) { return client.getLicenseNumber(); }) {}

bool ClientRepository::add(const Client& client) { return tree.insert(client); }
bool ClientRepository::remove(const std::string& licenseNumber) { return tree.remove(licenseNumber); }
Client* ClientRepository::find(const std::string& licenseNumber) { return tree.find(licenseNumber); }
const Client* ClientRepository::find(const std::string& licenseNumber) const { return tree.find(licenseNumber); }
bool ClientRepository::exists(const std::string& licenseNumber) const { return find(licenseNumber) != nullptr; }
void ClientRepository::clear() { tree.clear(); }
size_t ClientRepository::size() const { return tree.size(); }
std::vector<Client> ClientRepository::getAllInOrder() const { return tree.toVectorInOrder(); }
std::vector<Client> ClientRepository::getAllPostOrder() const { return tree.toVectorPostOrder(); }

bool ClientRepository::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;
    clear();
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        Client client;
        if (Client::deserialize(line, client)) add(client);
    }
    return true;
}

bool ClientRepository::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return false;
    for (const Client& client : getAllInOrder()) out << client.serialize() << '\n';
    return true;
}

void ClientRepository::printStructure() const { tree.printStructure(); }
