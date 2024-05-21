#include <QuickEspNow_esp32.h>
#include <Comms_hal.h>
#include <RingBuffer.h>
#include <QuickEspNow.h>
#include <QuickEspNow.h>
#include <WiFi.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define DEST_ADDR ESPNOW_BROADCAST_ADDRESS 


typedef struct{
    uint8_t* address;
    signed int rssi;
    uint8_t* data;
    uint8_t dataLen;
    int code;
}Agent;

int TAMANHO = 3;
Agent MAS[3];
int agentCount = 0;
int codigoAgente = 0;


uint8_t* generateAleatoryAddress() {
    uint8_t* codigo; 
    int numero = rand() % 900000 + 100000;

    // Converte o número em um array de uint8_t
    for (int i = 5; i >= 0; i--) {
        codigo[i] = numero % 10;
        numero /= 10;
    }

    return codigo;
}

Agent selfAgent(){
    Agent self; 
    self.address = generateAleatoryAddress();
    self.rssi = 0;
    return self;
}


void appendAgent(Agent A) {
    if (agentCount >= TAMANHO) {
        printf("Limite máximo de agentes atingido.\n");
        return;
    }
    int exists = 0;
    exists = addressExists(A.address);
    if (exists >= 0 && agentCount == 0){
        Serial.printf("Incluindo o primeiro agente na lista\n");
        MAS[exists] = A;
    }
    else if(exists >= 0 && agentCount != 0){
      Serial.printf("Agente já presente, atualizando dados\n");
    }
    else{
      Serial.printf("O agente não existe na lista, adicionando...\n");
      MAS[agentCount] = A;
      agentCount++;
    }
}

int addressExists(uint8_t* address) {
    for (int i = 0; i < agentCount; i++) {
        Serial.printf("Comparando...%d e %d \n", MAS[i].address, address);
        if (memcmp(MAS[i].address, address, sizeof(uint8_t)) == 0) {
          Serial.printf("Endereço encontrado\n");
            return i;  // Endereço encontrado
        }
    }
    return -1;  // Endereço não encontrado
}

void dataReceived (uint8_t* address, uint8_t* data, uint8_t len, signed int rssi, bool broadcast) {
    Agent A;
    A = setAgent(address, data, len, rssi, broadcast);
    // printAgent(A);
    // appendAgent(A);
}

Agent setAgent(uint8_t* address, uint8_t* data, uint8_t len, signed int rssi, bool broadcast)
{ 
    Agent P;
    P.address = address; 
    P.rssi = rssi;   
    P.data = data;
    P.dataLen = len;
    P.code = extractData(data, len);
    return P;
}

int extractData(uint8_t* data, uint8_t data_len) {

    char finalStr[data_len + 1];  // +1 para o caractere nulo

    for (size_t i = 0; i < data_len; ++i) {
        finalStr[i] = (char) data[i];
    }
    finalStr[data_len] = '\0';  // Adicionando o terminador nulo

    printf("String convertida: %s\n", finalStr);

    int codigo;
    if (sscanf(finalStr, "cd=%d", &codigo) == 1) {
        printf("O valor do código é: %d\n", codigo);
        return codigo;
    } else {
        printf("Não foi possível extrair o valor.\n");
    }

    return 0;
}

void printAgent(Agent P)
{
  //Serial.printf("MSG: %.*s, FROM: " MACSTR ", RSSI: %d dBm \n",P.dataLen, P.data, MAC2STR(P.address), P.rssi);
}

void leMac(){
    uint8_t mac[6];
    ESP_ERROR_CHECK(esp_read_mac(mac, ESP_MAC_WIFI_SOFTAP));
    Serial.printf("Meu endereço: %d\n", mac);
}

int processData() {
    char str[] = "cd=1";  // String contendo a chave e o valor
    int codigo;

    // Usando sscanf para extrair o valor após "cd="
    if (sscanf(str, "cd=%d", &codigo) == 1) {
        printf("O valor do código é: %d\n", codigo);
    } else {
        printf("Não foi possível extrair o valor.\n");
    }

    return 0;
}

char* uint8ToString(uint8_t* var, int length) {

    char* result = (char*)malloc((length * 2) + 4 + 1);
    strcpy(result, "cd=");

    for (int i = 0; i < length; i++) {
        sprintf(result + strlen(result), "%02X", var[i]);
    }

    return result;
}
//uint8_t* CODE = generateAleatoryAddress();
uint8_t* CODE = 1234;
void setup () {
    Serial.begin (115200);
    WiFi.mode (WIFI_MODE_STA);
    WiFi.disconnect (false);
    quickEspNow.onDataRcvd(dataReceived);
    quickEspNow.begin (1);
    leMac();
}

void loop () {
    char* message = uint8ToString(CODE, sizeof(CODE));
    quickEspNow.send (DEST_ADDR, (uint8_t*)message, strlen(message));
    free(message);
    delay (1000);
}