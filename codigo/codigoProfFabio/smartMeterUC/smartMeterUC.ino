// Os kits Esp32 COM display devem ser configurados como: Hitek WiFi32
// Os kits Esp32 SEM display devem ser configurados como: WEMOS LOLIN32


#include "definicoes.h"
#include <HardwareSerial.h>
#include <Arduino.h>
#include "rom/gpio.h"
#include <stdint.h>
#include "medidor.h"
#include "protocolo.h"
#include "Mensagem.h"



void setup() {
  Serial.begin(115200);
  /*u8x8.begin();
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
  u8x8.drawString(0, 0, "Funcionando...");*/

  Serial.println("RODANDO");
  delay(2000);


#ifdef MEDIDOR_FAKE
  TipoMensagem medidaFake;
  medidaFake.ENERGIA1  = 80;
  medidaFake.ENERGIA2  = 81;
  medidaFake.MEDIDOR   = 8;
  meter_start_fake(medidaFake);
#else
  meter_start(2400);
#endif
  protocol_start();
}

void loop()
{
  delay(0);
}
