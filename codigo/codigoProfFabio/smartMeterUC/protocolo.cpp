#include "protocolo.h"
#include "util.h"

     Mensagem MSG;
     TipoMensagem minhaMensagem;
    BLEServer* pServer;
    BLECharacteristic* pCharacteristic;
    BLEAdvertising *pAdvertising;
    TaskHandle_t task_serialID;
    SemaphoreHandle_t xMutex;




class MyCallbacks: public BLECharacteristicCallbacks {
    void onRead(BLECharacteristic *pCharacteristic) {
    }
    void onWrite(BLECharacteristic *pCharacteristiclocal) {
     
    }
};



class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer , esp_ble_gatts_cb_param_t *param) {
      BLEDevice::startAdvertising();
   
    };
    void onDisconnect(BLEServer* pServer) {
    }
};


void faz_envio_fragmento(void);
void myTask(void *pvParameter);
void atualizaDados  (char dados[]);




void protocol_update(TipoMensagem m)
{
  
      m.TIMESTAMP = 0;
    m.TIPO      = 99;
    for (int x=0;x<56;x++)  m.ASSINATURA[x]=x;
  xSemaphoreTake(xMutex, portMAX_DELAY);
    MSG.update(m);
     
  xSemaphoreGive(xMutex);


}

void protocol_start(void)
{
  char nome[32];
 xMutex = xSemaphoreCreateMutex();


     createSSID(nome);

    
      
      
      
  printf("Mac address do medidor: %s\n",nome);
  pServer  = NULL;
  pCharacteristic = NULL;
  xTaskCreatePinnedToCore(myTask,"protocolo",10000,NULL,0,&task_serialID,0);


  BLEDevice::init("Medidor");
    maxPowerBLE();

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setCallbacks(new MyCallbacks());     
  pService->start();

   pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x00); 
 pAdvertising->start();


  
}



void faz_envio_fragmento(void)
{
  pAdvertising->stop();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  std::string dados;
   xSemaphoreTake(xMutex, portMAX_DELAY);
    MSG.getFragment(dados);
   xSemaphoreGive(xMutex);


  BLEAdvertisementData *frag = new BLEAdvertisementData();
  frag->setManufacturerData(dados);
  dados.clear();
   
  pAdvertising->setScanResponseData(*frag);
  pAdvertising->start();
  delete (frag);
}
void myTask(void *pvParameter)
{
  int a;
  while (1)
  {
    vTaskDelay(pdMS_TO_TICKS(200));
    xSemaphoreTake(xMutex, portMAX_DELAY);
      a = MSG.temMensagem();
   xSemaphoreGive(xMutex);
      if (a) faz_envio_fragmento();  
  }
}
