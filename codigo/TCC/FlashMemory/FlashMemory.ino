#include <WiFi.h>
#include <QuickEspNow.h>
#include "Localizator.h"

// Função de callback para receber dados
void dataReceived(uint8_t* address, uint8_t* data, uint8_t len, signed int rssi, bool broadcast) {
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X", address[0], address[1], address[2], address[3], address[4], address[5]);
    Serial.printf("Mensagem recebida de %s: %.*s\n", macStr, len, data);
}

// Instancia o Localizator
Localizator localizator;

void setup() {
    Serial.begin(115200);

    // Imprime o endereço MAC do dispositivo atual
    String macAddress = WiFi.macAddress();
    Serial.print("Endereço MAC do dispositivo atual: ");
    Serial.println(macAddress);

    // Inicializa o Localizator
    localizator.initialize();

    // Configura o WiFi e o ESP-NOW
    WiFi.mode(WIFI_MODE_STA);
    WiFi.disconnect(false);
    quickEspNow.onDataRcvd(dataReceived);
    quickEspNow.begin();

    // Envia o ID do dispositivo via ESP-NOW
    String id = localizator.getId();
    if (quickEspNow.send(ESPNOW_BROADCAST_ADDRESS, (uint8_t*)id.c_str(), id.length()) != 0) {
        Serial.println("Erro ao enviar ID via ESP-NOW");
    } else {
        Serial.println("ID enviado via ESP-NOW: " + id);
    }
}

void loop() {
    // Código para loop principal (se necessário)
}