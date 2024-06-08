#ifndef LOCALIZATOR_H
#define LOCALIZATOR_H

#include <Arduino.h>
#include <Preferences.h>

// Declaração da variável global como extern
extern const char* CONFIG_NAMESPACE;

class Localizator {
public:
    Localizator();
    void initialize();
    void initialize_id();
    String getId();
private:
    Preferences preferences;
    String id;
};

#endif // LOCALIZATOR_H