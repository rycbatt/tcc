#include <WiFi.h>

#include <Comms_hal.h>
#include <QuickEspNow.h>
#include <QuickEspNow_esp32.h>
#include <QuickEspNow_esp8266.h>
#include <RingBuffer.h>

#define DEST_ADDR ESPNOW_BROADCAST_ADDRESS 

char id = 'B';


void dataReceived (uint8_t* address, uint8_t* data, uint8_t len, signed int rssi, bool broadcast) {
    
    
    if(len==1){
      char senderId = *(char*) data;
      char* result = appendChars(id, senderId);
      char* strRssi = intToString(rssi);
      String idRssi = appendString(result, strRssi);
      Serial.printf("%s\n", idRssi);
      quickEspNow.send (DEST_ADDR, (uint8_t*)idRssi.c_str(), sizeof(idRssi));
      return;
    }
    Serial.printf("%.*s\n", len, data);  
}

char* appendString(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        fprintf(stderr, "One of the strings is NULL.\n");
        return NULL;  // Handle NULL strings appropriately
    }

    // Calculate the total length of the resulting string
    int totalLength = strlen(str1) + strlen(str2) + 1;

    // Dynamically allocate memory for the concatenated result
    char* result = (char*)malloc(totalLength * sizeof(char));
    if (result == NULL) {
        perror("Failed to allocate memory");
        return NULL;  // Return NULL on allocation failure
    }

    // Initialize the result and concatenate the strings
    strcpy(result, str1);  // Copy the first string
    strcat(result, str2);  // Append the second string

    return result;
}

char* intToString(int num) {
    // Allocate a buffer dynamically
    char* buffer = (char*)malloc(12 * sizeof(char)); // Allocate enough for any 32-bit int
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Convert integer to string
    sprintf(buffer, "%d", num);

    return buffer;
}

char* appendChars(char id, char senderId) {
    // Allocate memory for 3 characters (2 chars + '\0')
    char* result = (char*)malloc(6 * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Assign characters and null terminate the string
    result[0] = id;
    result[1] = senderId;
    result[2] = '\0';
    return result;
}


void setup () {
    Serial.begin (115200);
    WiFi.mode (WIFI_MODE_STA);
    WiFi.disconnect (false);
    quickEspNow.onDataRcvd (dataReceived);
    quickEspNow.begin (1); // If you are not connected to WiFi, channel should be specified
}

void loop () {
    quickEspNow.send (DEST_ADDR, (uint8_t*)&id,1);
    delay (1000);
}