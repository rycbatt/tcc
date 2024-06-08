#include <WiFi.h>

//C MAC Address: 30:AE:A4:0B:09:0C
//A MAC Address: 30:AE:A4:9D:16:B0
//B MAC Address: E8:68:E7:29:05:A0


void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);
  delay(1000); // Pequena pausa para garantir que o monitor serial esteja pronto

  // Inicializa o módulo WiFi no modo STA (Station)
  WiFi.mode(WIFI_MODE_STA);
  WiFi.disconnect(); // Garante que o ESP32 não esteja conectado a nenhuma rede

  // Obtém o endereço MAC
  String macAddress = WiFi.macAddress();

  // Exibe o endereço MAC no monitor serial
  Serial.print("MAC Address: ");
  Serial.println(macAddress);
}

void loop() {
  // Não é necessário código no loop para esta funcionalidade
}