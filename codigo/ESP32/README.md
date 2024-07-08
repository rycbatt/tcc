## Implementação

Insira no arquivo a ser compilado para o ESP32 o seguinte código:

```
#include <WiFi.h>
#include <QuickEspNow.h>
#include "Localizator.h"

// Instancia o Localizator
Localizator localizator;

```


Após isso, o setup do seu dispositivo deve conter as seguintes linhas:

```

// Função de callback para receber dados
void dataReceived(uint8_t* address, uint8_t* data, uint8_t len, signed int rssi, bool broadcast) {
    localizator.receiveData(address, data, len, rssi);
}

void setup() {
    Serial.begin(115200);

    // Inicializa o Localizator
    localizator.initialize();

    // Configura o WiFi e o QuickEspNow
    WiFi.mode(WIFI_MODE_STA);
    WiFi.disconnect(false);

    // Define a função de callback
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
```

A partir desse código é possível utiliza-lo para o envio, recebimento e cálculo de distância, pois o objeto Localizator irá realizar as inferências e printá-las no terminal.

Um exemplo mais detalhado de como o experimento foi realizado está na pasta Localizator deste repositório