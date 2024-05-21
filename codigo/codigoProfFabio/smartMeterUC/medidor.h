#ifndef _MEDIDOR_
#define _MEDIDOR_
#include "definicoes.h"
#include "Mensagem.h"

#include <HardwareSerial.h>

#pragma pack(1);

typedef struct {
  uint8_t ID[5];
  uint8_t Size;
  uint8_t Scope[2];
  uint8_t Data[255];
  uint8_t CRC[2];
}TypeFrame;

void meter_start(int speed);
void meter_start_fake(TipoMensagem medidaFake);


#endif
