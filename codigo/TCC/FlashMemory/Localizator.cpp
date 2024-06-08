#include "Localizator.h"

// Definição da variável global
const char* CONFIG_NAMESPACE = "config";

Localizator::Localizator() {}

void Localizator::initialize() {
    Serial.begin(115200);

    // Inicializa o ID
    preferences.begin(CONFIG_NAMESPACE, false);
    initialize_id();
    preferences.end();
}

void Localizator::initialize_id() {
    // Recupera o valor do ID ou define como uma string vazia se não existir
    id = preferences.getString("id", "");

    if (id == "") {
        // Se o ID não existir na memória, solicita a inserção pelo usuário
        Serial.println("ID não encontrado na memória. Insira um novo ID:");
        
        // Espera o usuário inserir um novo ID
        while (Serial.available() == 0) {
            // Aguarda a entrada do usuário
        }

        // Lê o novo ID do monitor serial
        id = Serial.readStringUntil('\n');
        id.trim(); // Remove espaços em branco

        // Salva o novo ID na memória
        preferences.putString("id", id);
        Serial.println("Novo ID salvo: " + id);
    } else {
        // Se o ID já existir, exibe o valor recuperado
        Serial.println("ID recuperado da memória: " + id);
    }
}

String Localizator::getId() {
    return id;
}