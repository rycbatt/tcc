#ifndef __PROTOCOL__
#define __PROTOCOL__

#include "freertos/FreeRTOS.h"
#include "definicoes.h"
#include <ArduinoJson.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>
#include "Mensagem.h"


#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#pragma pack(1);


void protocol_start(void);
void protocol_update(TipoMensagem m);

#endif
