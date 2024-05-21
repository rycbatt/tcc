#include <Arduino.h>
#include "util.h"
#include "graficos.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

void maxPowerBLE(void)
{
  esp_err_t errRc=esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT,ESP_PWR_LVL_P9);
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_P9);
  //esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_SCAN ,ESP_PWR_LVL_P9);
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_P9);
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_CONN_HDL0, ESP_PWR_LVL_P9);
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_CONN_HDL1, ESP_PWR_LVL_P9);
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_CONN_HDL2, ESP_PWR_LVL_P9);
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_CONN_HDL3, ESP_PWR_LVL_P9);
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_CONN_HDL4, ESP_PWR_LVL_P9);
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_CONN_HDL5, ESP_PWR_LVL_P9);
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_CONN_HDL6, ESP_PWR_LVL_P9);
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_CONN_HDL8, ESP_PWR_LVL_P9);
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_P9);
}
void createSSID(char *s)
{
  union tipo_x{
    uint64_t chipid; 
    uint8_t  bytes[8];
  };

  union tipo_x dado; 
  dado.chipid=ESP.getEfuseMac()+((uint64_t)2<<40);
  sprintf(s,"%02X%02X%02X%02X%02X%02X",dado.bytes[0],dado.bytes[1],dado.bytes[2],dado.bytes[3],dado.bytes[4],dado.bytes[5]);
}

void atualizaDisplay (TipoMensagem minhaMensagem)
{     static int started=0;
     char str[50];
     char nome[32];

    if (started==0)
    {
    
     createSSID(nome);

      u8x8.clear();
      u8x8.drawString(0, 0, "  Mac-address:");
      
      sprintf(str, "  %s",nome);
      u8x8.drawString(0, 1, str);
      u8x8.drawString(0, 2, "----------------" );

      sprintf(str, "  Serial N.: %d",minhaMensagem.MEDIDOR);
      u8x8.drawString(0, 3, str);

      u8x8.drawString(0, 4, "----------------" );
    }
    started=1;
       sprintf(str,"  Consumida: %d",minhaMensagem.ENERGIA1);
      u8x8.drawString(0, 5, str );

       sprintf(str,"  Gerada   : %d",minhaMensagem.ENERGIA2);
      u8x8.drawString(0, 6, str );
 
}
