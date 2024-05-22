#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>

struct Node {
    char id;
    std::vector<std::pair<Node*, int>> knownNodes;
    Node(char id) : id(id) {}
    void addConnection(Node* other, int distance) {
        knownNodes.push_back(std::make_pair(other, distance));
    }
};

void parseAndAddConnection(const std::string& input, std::map<char, Node*>& nodes) {
    char nodeId = input[0];
    char knownNodeId = input[1];
    int distance = std::stoi(input.substr(3));

    if (nodes.find(nodeId) == nodes.end()) {
        nodes[nodeId] = new Node(nodeId);
    }
    if (nodes.find(knownNodeId) == nodes.end()) {
        nodes[knownNodeId] = new Node(knownNodeId);
    }
    nodes[nodeId]->addConnection(nodes[knownNodeId], distance);
}

std::set<std::string> generateRequiredConnections(const std::set<char>& nodeIds) {
    std::set<std::string> requiredConnections;
    for (auto it = nodeIds.begin(); it != nodeIds.end(); ++it) {
        for (auto jt = nodeIds.begin(); jt != nodeIds.end(); ++jt) {
            if (*it != *jt) {
                requiredConnections.insert(std::string(1, *it) + *jt);
            }
        }
    }
    return requiredConnections;
}

int main() {
    std::map<char, Node*> nodes;
    std::set<char> nodeIds;
    std::set<std::string> receivedConnections;
    std::vector<std::string> inputs = {"AB-55", "CB-66", "BC-70", "AC-88", "BA-60", "CA-92"};

    // Extrair identificadores de nó e preparar dados
    for (const auto& input : inputs) {
        std::string connKey = input.substr(0, 2);
        nodeIds.insert(connKey[0]);
        nodeIds.insert(connKey[1]);
        receivedConnections.insert(connKey); // Adiciona ao conjunto, eliminando duplicatas
    }

    // Gerar todas as conexões necessárias com base nos nós identificados
    auto requiredConnections = generateRequiredConnections(nodeIds);

    // Verificar se todas as conexões necessárias foram recebidas
    if (std::includes(receivedConnections.begin(), receivedConnections.end(),
                      requiredConnections.begin(), requiredConnections.end())) {
        for (const auto& conn : inputs) {
            parseAndAddConnection(conn, nodes);
        }
    }

    // Imprimir as conexões para verificação
    for (auto& pair : nodes) {
        std::cout << "Nó " << pair.first << " conexões:" << std::endl;
        for (auto& conn : pair.second->knownNodes) {
            std::cout << "  - Conectado ao nó " << conn.first->id << " com distância RSSI " << conn.second << std::endl;
        }
    }

    // Limpeza
    for (auto& pair : nodes) {
        delete pair.second;
    }
    nodes.clear();

    return 0;
}