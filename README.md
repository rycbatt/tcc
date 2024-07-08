# Cálculo de Distância entre Dispositivos IoT Utilizando RSSI de Maneira Distribuída e em Tempo Real

Este repositório visa conter todos os dados utilizados para o trabalho de conclusão de curso, a fim de disponibilizar para a comunidade todo o trabalho realizado. Também é disponibilizado o código utilizado durante os experimentos, e o objeto Localizator, que foi deselvolvido para realizar os cálculos de distância.

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
