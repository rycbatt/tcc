#include <Arduino.h>
#include "medidor.h"
#include "protocolo.h"
#include "util.h"

TipoMensagem fakeData;
static HardwareSerial medidor(2);
static char buffer[500];

void meter_task (void *pvParameter);
void meter_task_fake (void *pvParameter);

void meter_processChar(uint8_t c);

TaskHandle_t meter_task_ID;
char nome[32];

void meter_start_fake(TipoMensagem m)
{
     createSSID(nome);

  fakeData = m;
  xTaskCreatePinnedToCore (
      meter_task_fake,     //Function to implement the task
      "fake",            //Name of the task
      10000,                      //Stack size in words
      NULL,                       //Task input parameter
      0,                          //Priority of the task
      &meter_task_ID,             //Task handle.
      0); 
}


void meter_task_fake (void *pvParameter)
{
  
  while (1)
  {
    vTaskDelay(5000 / portTICK_PERIOD_MS);
     protocol_update(fakeData);
     atualizaDisplay(fakeData);

     fakeData.ENERGIA1++;
     fakeData.ENERGIA2++;

  }
}
void meter_start(int speed)
{   
  createSSID(nome);

  medidor.begin(speed);
  
  xTaskCreatePinnedToCore (
      meter_task,     //Function to implement the task
      "capturaSerial",            //Name of the task
      10000,                      //Stack size in words
      NULL,                       //Task input parameter
      0,                          //Priority of the task
      &meter_task_ID,             //Task handle.
      0);                         //Core where the task should run
}

void meter_readD ( char *b )
{
  strcpy(b, buffer);  
}

void meter_task (void *pvParameter)
{
  while (1)
  {
    vTaskDelay(pdMS_TO_TICKS(10));
    if (medidor.available())
    {
      int a = medidor.read();
      meter_processChar(a);
    }
  
  }
}
uint32_t meter_captureSerial(byte a, byte b, byte c, byte d, byte e)
{
  return ((b<<24)|(c<<16)|(d<<8)|(e) );
}
uint32_t meter_captureNumber(byte a, byte b, byte c)
{
  return ((a<<16)|(b<<8)|(c) );
}

void meter_processFrame(TypeFrame frame)
{
  static TipoMensagem tmpMSG;
  static int cont=0;
  char st[20];
  sprintf(buffer, "%s Frame: |AA 55|%02X %02X %02X %02X %02X|%02X|%02X %02X|%02X %02X %02X|%02X %02X|",st,frame.ID[0],frame.ID[1],frame.ID[2],frame.ID[3],frame.ID[4],frame.Size,frame.Scope[0],frame.Scope[1],frame.Data[0],frame.Data[1],frame.Data[2],frame.CRC[0],frame.CRC[1]);
  if ((frame.Scope[0]==0x0A) && (frame.Scope[1]==0x02)) {
    tmpMSG.ENERGIA1  = meter_captureNumber(frame.Data[0],frame.Data[1],frame.Data[2]);
    strcat(buffer,"\nTotalizador de energia ativa direta\n");
  }
  if ((frame.Scope[0]==0x0A) && (frame.Scope[1]==0x07)) strcat(buffer,"\nTotalizador de energia reativa indutiva Total\n");
  if ((frame.Scope[0]==0x0A) && (frame.Scope[1]==0x0C)) strcat(buffer,"\nTotalizador de energia reativa capacitiva Total\n");
  if ((frame.Scope[0]==0x0A) && (frame.Scope[1]==0x51)) {
    tmpMSG.ENERGIA2  = meter_captureNumber(frame.Data[0],frame.Data[1],frame.Data[2]);
    strcat(buffer,"\nTotalizador de energia ativa sentido reverso Total\n");
  }
  Serial.println(buffer);
  tmpMSG.TIMESTAMP = 0;
  tmpMSG.TIPO      = 99;
  tmpMSG.MEDIDOR   = meter_captureSerial(frame.ID[0],frame.ID[1],frame.ID[2],frame.ID[3],frame.ID[4]);

  if (cont==5 )
  {
    protocol_update(tmpMSG);
    atualizaDisplay(tmpMSG);

    cont=0;
  } else cont++;
  
}
void meter_processChar(uint8_t c)
{
  enum statesType {START, PRE1, ID, SIZE, SCOPE, DATA, CRC};
  static enum statesType currentState = START;
  static enum statesType nextState = START;
  static TypeFrame frame;
  static uint8_t counterID;
  static uint8_t counterSCOPE;
  static uint8_t counterDATA;
  static uint8_t counterCRC;

  switch (currentState)
      {
        case START:
          if (c == 0xAA) nextState = PRE1;
          else nextState = START;
          counterID=0;
          counterSCOPE=0;
          counterDATA=0;
          counterCRC=0;
          break;
        case PRE1:
          if (c == 0x55) nextState = ID;
          if ((c != 0x55) && (c != 0xAA) ) nextState = START;
          break;
        case ID:
         frame.ID[counterID] = c;
         counterID++;
         if (counterID==5) nextState = SIZE;
         break;
        case SIZE:
          frame.Size = c;
          nextState = SCOPE;
          break;
        case SCOPE:
          frame.Scope[counterSCOPE]=c;
          counterSCOPE++;
          if (counterSCOPE==2) nextState = DATA;
          break;
        case DATA:
          frame.Data[counterDATA]=c;
          counterDATA++;
          if (counterDATA>=(frame.Size-2)) nextState = CRC;
          break;
        case CRC:
          frame.CRC[counterCRC]=c;
          counterCRC++;
          if (counterCRC==2)
          {
            nextState = START;
          }
          break;
      }
        if (counterCRC==2)
          {
            meter_processFrame(frame);
          }
      currentState = nextState;
}
