#include "Inferences.h"
#include <Preferences.h>
#include <iostream>

Node::Node(char id) : id(id) {}

void Node::addConnection(Node* other, int distance) {
    knownNodes.push_back(std::make_pair(other, distance));
}

void Node::printConnections() const {
    Serial.print("Nó ");
    Serial.print(id);
    Serial.println(" conexões:");
    for (const auto& connection : knownNodes) {
        Serial.print("  - Conectado ao nó ");
        Serial.print(connection.first->id);
        Serial.print(" com distância RSSI ");
        Serial.println(connection.second);
    }
}

Inferences::Inferences() {
    preferences.begin("inferences", false); // Iniciar Preferences com namespace "inferences"
}

void Inferences::addInput(const String& input) {
    std::string connKey = input.substring(0, 2).c_str();
    nodeIds.insert(connKey[0]);
    nodeIds.insert(connKey[1]);
    receivedConnections.insert(connKey); // Adiciona ao conjunto, eliminando duplicatas
    inputs.push_back(input.c_str());
}

void Inferences::processConnections(String nodeId, int distance) {
    //Serial.println("Processando conexões...");

    auto requiredConnections = generateRequiredConnections(nodeIds);

    // Verificar se todas as conexões necessárias foram recebidas
    if (std::includes(receivedConnections.begin(), receivedConnections.end(),
                      requiredConnections.begin(), requiredConnections.end())) {
        //Serial.println("Todas as conexões necessárias foram recebidas.");
        for (const auto& conn : inputs) {
            //Serial.print("Processando input: ");
            Serial.println(conn.c_str());
            parseAndAddConnection(conn, distance);
        }
    } else {
        //Serial.println("Nem todas as conexões necessárias foram recebidas.");
    }
}

void Inferences::saveToMemory() {
    preferences.clear(); // Limpa todos os valores armazenados anteriormente
    preferences.putUInt("size", inputs.size()); // Salva o tamanho do vetor

    for (size_t i = 0; i < inputs.size(); ++i) {
        String key = "input" + String(i);
        preferences.putString(key.c_str(), inputs[i].c_str());
    }
}

void Inferences::loadFromMemory() {
    inputs.clear(); // Limpa o vetor de inputs
    uint32_t size = preferences.getUInt("size", 0); // Recupera o tamanho do vetor

    for (uint32_t i = 0; i < size; ++i) {
        String key = "input" + String(i);
        String value = preferences.getString(key.c_str(), "");
        if (value.length() > 0) {
            addInput(value);
        }
    }
}

void Inferences::parseAndAddConnection(const std::string& input, int measuredDistance) {
    char nodeId = input[0];
    char knownNodeId = input[1];
    int distance = std::stoi(input.substr(3));

    //Serial.print("Processando conexão: ");
    //Serial.print(nodeId);
    //Serial.print(" -> ");
    //Serial.print(knownNodeId);
    //Serial.print(" com distância ");
    //Serial.println(distance);

    if (nodes.find(nodeId) == nodes.end()) {
        nodes[nodeId] = new Node(nodeId);
        Serial.print("Nó criado: ");
        Serial.println(nodeId);
    }
    if (nodes.find(knownNodeId) == nodes.end()) {
        nodes[knownNodeId] = new Node(knownNodeId);
        Serial.print("Nó criado: ");
        Serial.println(knownNodeId);
    }
    nodes[nodeId]->addConnection(nodes[knownNodeId],measuredDistance, distance);
    //Serial.print("Conexão adicionada: ");
    //Serial.print(nodeId);
    //Serial.print(" -> ");
    //Serial.print(knownNodeId);
    //Serial.print(" com distância ");
    //Serial.println(distance);
}

void Inferences::printAllNodes() const {
    //Serial.println("Imprimindo todos os nós:");
    for (const auto& pair : nodes) {
        pair.second->printConnections();
    }
}

void Inferences::printInputs() const {
    //Serial.println("Inputs armazenados:");
    for (const auto& input : inputs) {
        //Serial.println(input.c_str());
    }
}

size_t Inferences::getSize() const {
    return inputs.size();
}

std::set<std::string> Inferences::generateRequiredConnections(const std::set<char>& nodeIds) {
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