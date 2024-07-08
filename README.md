## Localizator

Esta biblioteca cria um objeto chamado de Localizator, que irá enviar e receber mensagens via ESP-NOW para calcular a distância de outros dispositivos ESP32 que estão enviando mensagens.

Seu uso é bastante simples:

```
#include <WiFi.h>
#include <QuickEspNow.h>
#include "Localizator.h"

// Instancia o Localizator
Localizator localizator;

```

Mais detalhes da implementação no ESP32 estão na pasta [codigo/Esp32](/codigo/ESP32/README.md)
