#ifndef LOCALIZATOR_H
#define LOCALIZATOR_H

#include <Arduino.h>
#include <Preferences.h>
#include <map>
#include <vector>
#include <math.h>

// Declaração da variável global como extern
extern const char* CONFIG_NAMESPACE;
extern const char* CALIBRATION_NAMESPACE;

struct RSSIRecord {
    String mac;
    String id;
    int distance; // Distância em metros
    int rssi;
};

class Localizator {
public:
    Localizator();
    void initialize();
    void initialize_id();
    void initialize_calibration();
    void receiveData(uint8_t* address, uint8_t* data, uint8_t len, int rssi);
    void addNode(const String& id, const String& mac);
    void collectRSSISample(const String& id, const String& mac, int rssi);
    String getId();
    String getMode();
    void saveSamples(const String& id);
    bool hasSavedSamples(const String& id);
    void activateCalibrationMode();
    std::vector<RSSIRecord> getSavedRecords(const String& id);
    std::vector<String> getSavedKeys(const String& id);
    String rssiRecordToJson(const RSSIRecord& record);
    RSSIRecord jsonToRssiRecord(const String& jsonString);
    void printSavedSamples(const String& id);
    void clearPreferences();
    std::vector<int> getRSSIValues(const String& id);
    void printSavedRSSIs(const String& id);


private:
    Preferences preferences;
    String id;
    String mode;
    std::map<String, String> nodes;
    std::map<String, std::vector<RSSIRecord>> rssiSamples;
    float calculateMean(const std::vector<int>& data);
    float calculateVariance(const std::vector<int>& data);
    float calculateMahalanobisDistance(int x, const std::vector<int> &data);
    float calculateDistance(int rssi, const std::vector<int> &data);
};

#endif // LOCALIZATOR_H
