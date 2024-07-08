#include <WiFi.h>
#include <QuickEspNow.h>
#include "Localizator.h"

// Instancia o Localizator
Localizator localizator;

#define BUTTON_PIN 0  // Defina o pino do botão
unsigned long lastDebounceTime = 0;  // Último tempo de debounce
unsigned long debounceDelay = 50;  // Atraso de debounce
int buttonState = HIGH;  // Estado atual do botão
int lastButtonState = HIGH;  // Último estado do botão
int clickCount = 0;  // Contador de cliques
unsigned long lastClickTime = 0;  // Último tempo de clique

// Função de callback para receber dados
void dataReceived(uint8_t* address, uint8_t* data, uint8_t len, signed int rssi, bool broadcast) {
    localizator.receiveData(address, data, len, rssi);
}

// Função para piscar o LED
void piscaLed(int pin, int delayTime) {
    digitalWrite(pin, HIGH);
    delay(delayTime);
    digitalWrite(pin, LOW);
    delay(delayTime);
}

void setup() {
    Serial.begin(115200);

    // Configuração do pino do botão
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Imprime o endereço MAC do dispositivo atual
    String macAddress = WiFi.macAddress();
    Serial.print("Endereço MAC do dispositivo atual: ");
    Serial.println(macAddress);

    // Inicializa o Localizator
    localizator.initialize();

    // Configura o WiFi e o ESP-NOW
    WiFi.mode(WIFI_MODE_STA);
    WiFi.disconnect(false);
    quickEspNow.onDataRcvd(dataReceived); // Usa a função de callback definida
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
    // Leitura do estado do botão
    String id = localizator.getId();
    quickEspNow.send(ESPNOW_BROADCAST_ADDRESS, (uint8_t*)id.c_str(), id.length());

    int reading = digitalRead(BUTTON_PIN);

    // Verificação de debounce
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        // Se o estado do botão mudou
        if (reading != buttonState) {
            buttonState = reading;
            // Apenas conta cliques no botão quando ele é pressionado (estado LOW)
            if (buttonState == LOW) {
                if ((millis() - lastClickTime) < 500) {
                    clickCount++;
                } else {
                    clickCount = 1;  // Reinicia a contagem se o tempo entre cliques for maior que 500ms
                }
                lastClickTime = millis();
            }
        }
    }

    // Se o botão foi pressionado 5 vezes rapidamente
    if (clickCount == 5) {
        localizator.clearPreferences();
        clickCount = 0;  // Reseta o contador de cliques após limpar as preferências
    }

    lastButtonState = reading;

    // Verifica se o modo é de calibração
    if (localizator.getMode() == "CALIBRATE") {
        pinMode(2, OUTPUT);  // Assume que o LED azul está no pino 2
        // Pisca o LED azul para indicar o modo de calibração
        piscaLed(2, 500);
    }
}
