#include "Localizator.h"
#include <ArduinoJson.h>


// Definição das variáveis globais
const char* CONFIG_NAMESPACE = "config";
const char* CALIBRATION_NAMESPACE = "calibration";
const char* SAMPLES_NAMESPACE = "samples";


Localizator::Localizator() : mode("NORMAL") {}

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

void Localizator::clearPreferences() {
    preferences.begin(SAMPLES_NAMESPACE, false);
    preferences.clear();
    preferences.end();
    Serial.println("Todos os registros foram apagados.");
}

void Localizator::initialize_calibration() {
    preferences.begin(CALIBRATION_NAMESPACE, false);

    Serial.printf("Modo de calibração: %s\n", preferences.getBool("calibrated", false) ? "Inativo" : "Ativado");

    // Verifica se há registros de calibração
    if (!preferences.getBool("calibrated", false)) {
        mode = "CALIBRATE";
    } else {
        mode = "NORMAL";
    }

    preferences.end();
    Serial.printf("Modo de operação: %s\n", mode.c_str());
}

float Localizator::calculateDistance(int rssi, const std::vector<int> &data) {
    float measuredPower = calculateMean(data);
    int n = 2;
    return pow(10.0, (measuredPower - rssi) / (10.0 * n));
}

bool isId(int len, uint8_t* data){
  if (len == 1 && isupper(data[0])) {
    return true;
  }
  return false;
  }

void Localizator::receiveData(uint8_t* address, uint8_t* data, uint8_t len, int rssi) {
    if (isId(len, data)) {
        String id = String((char)data[0]);

        char macStr[18];
        snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X", address[0], address[1], address[2], address[3], address[4], address[5]);
        String mac = String(macStr);

        Serial.printf("Mensagem do nó %s recebida\n", id);
        Serial.println(getSavedKeys(id).size());
        if (getSavedKeys(id).size() >= 50) {
          Serial.printf("Nó %s já calibrado\n", id);
          //printSavedSamples(id);
          //printSavedRSSIs(id);
          float distanceMahalanobis = calculateMahalanobisDistance(rssi, getRSSIValues(id));
          float distance = calculateDistance(rssi, getRSSIValues(id));
          Serial.printf("Distância Mahalanobis estimada: %f, distancia estimada: %f\n", distanceMahalanobis, distance);
        }
        else{
          if(nodes.find(id) == nodes.end()){
            collectRSSISample(id, mac, rssi); 
          }
          else{
            Serial.printf("Novo nó encontrado! id: %s, mac: %s, adicionado à memória RAM e entrando no modo de calibração\n");
            addNode(id, mac);
            initialize_calibration(); 
            }
        }
    }
}

float Localizator::calculateMean(const std::vector<int>& data) {
    float sum = 0.0;
    for (int value : data) {
        sum += value;
    }
    return sum / data.size();
}

float Localizator::calculateVariance(const std::vector<int>& data) {
    float sum = 0.0;
    float mean = calculateMean(data);
    for (int value : data) {
        float diff = value - mean;
        sum += diff * diff;
    }
    return sum / (data.size() - 1);
}

// Função para calcular a distância de Mahalanobis para um único dispositivo
float Localizator::calculateMahalanobisDistance(int x, const std::vector<int> &data) {
    float mean = calculateMean(data);
    float variance = calculateVariance(data);
    float diff = x - mean;
    float distance = diff * diff / variance;
    return sqrt(distance);
}



void Localizator::collectRSSISample(const String& id, const String& mac, int rssi) {
    if (rssiSamples[id].size() < 50) {
        RSSIRecord sample = {mac, id, 1, rssi}; // 1 metro é a distância inicial
        rssiSamples[id].push_back(sample);
        Serial.printf("Amostra RSSI coletada: ID = %s, MAC = %s, RSSI = %d, Total de Amostras = %d\n", 
                      id.c_str(), mac.c_str(), rssi, rssiSamples[id].size());
        if (rssiSamples[id].size() == 50) {
            Serial.printf("Total de amostras atingidas para o o id %s, salvando na memória Flash", id), 
            saveSamples(id);
        }
    } else {
        Serial.printf("50 amostras já coletadas para o nó: ID = %s, MAC = %s\n", id.c_str(), mac.c_str());
    }
}

std::vector<int> Localizator::getRSSIValues(const String& id) {
    preferences.begin(SAMPLES_NAMESPACE, true);
    std::vector<int> rssiValues;
    size_t i = 0;
    while (true) {
        String key = id + "_" + String(i);
        if (preferences.isKey(key.c_str())) {
            String value = preferences.getString(key.c_str(), "");
            if (!value.isEmpty()) {
                RSSIRecord record = jsonToRssiRecord(value);
                rssiValues.push_back(record.rssi);
            }
            i++;
        } else {
            break;
        }
    }
    preferences.end();
    return rssiValues;
}

void Localizator::saveSamples(const String& id) {
    preferences.begin(SAMPLES_NAMESPACE, false); // Abre o namespace samples para escrita
    const std::vector<RSSIRecord>& samples = rssiSamples[id];
    for (size_t i = 0; i < samples.size(); ++i) {
        String key = id + "_" + String(i);
        String value = rssiRecordToJson(samples[i]);
        preferences.putString(key.c_str(), value);
    }
    preferences.end();
}

std::vector<RSSIRecord> Localizator::getSavedRecords(const String& id) {
    preferences.begin(SAMPLES_NAMESPACE, true);
    std::vector<RSSIRecord> records;
    size_t i = 0;
    while (true) {
        String key = id + "_" + String(i);
        if (preferences.isKey(key.c_str())) {
            String value = preferences.getString(key.c_str(), "");
            if (!value.isEmpty()) {
                RSSIRecord record = jsonToRssiRecord(value);
                records.push_back(record);
            }
            i++;
        } else {
            break;
        }
    }
    preferences.end();
    return records;
}

void Localizator::printSavedRSSIs(const String& id) {
    std::vector<int> records = getRSSIValues(id);
    Serial.printf("Samples para ID = %s:\n", id.c_str());
    for (const int& record : records) {
        Serial.printf("RSSI: %d\n", record);
    }
}

void Localizator::printSavedSamples(const String& id) {
    std::vector<RSSIRecord> records = getSavedRecords(id);
    Serial.printf("Samples para ID = %s:\n", id.c_str());
    for (const RSSIRecord& record : records) {
        Serial.printf("MAC: %s, Distance: %d, RSSI: %d\n", record.mac.c_str(), record.distance, record.rssi);
    }
}

std::vector<String> Localizator::getSavedKeys(const String& id) {
    preferences.begin(SAMPLES_NAMESPACE, true);
    std::vector<String> keys;
    size_t i = 0;
    while (true) {
        String key = id + "_" + String(i);
        if (preferences.isKey(key.c_str())) {
            keys.push_back(key);
            i++;
        } else {
            break;
        }
    }
    preferences.end();
    return keys;
}

void Localizator::addNode(const String& id, const String& mac) {
    nodes[id] = mac;
}

String Localizator::rssiRecordToJson(const RSSIRecord& record) {
    StaticJsonDocument<200> doc;
    doc["mac"] = record.mac;
    doc["id"] = record.id;
    doc["distance"] = record.distance;
    doc["rssi"] = record.rssi;
    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}

// Verifica se um nó tem registros salvos
bool Localizator::hasSavedSamples(const String& id) {
    preferences.begin(SAMPLES_NAMESPACE, true);
    bool hasSamples = preferences.isKey((id + "_0").c_str());
    preferences.end();
    return hasSamples;
}

// Ativa o modo de calibração
void Localizator::activateCalibrationMode() {
    mode = "CALIBRATE";
    preferences.begin(CALIBRATION_NAMESPACE, false);
    preferences.putBool("calibrated", false); // Define como false para indicar que a calibração está ativa
    preferences.end();
    Serial.println("Modo de calibração ativado.");
}

RSSIRecord Localizator::jsonToRssiRecord(const String& jsonString) {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, jsonString);
    RSSIRecord record;
    record.mac = doc["mac"].as<String>();
    record.id = doc["id"].as<String>();
    record.distance = doc["distance"];
    record.rssi = doc["rssi"];
    return record;
}


String Localizator::getId() {
    return id;
}

String Localizator::getMode() {
    return mode;
}
