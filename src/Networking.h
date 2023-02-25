#include "Arduino.h"

class ImageData {
    public:
    uint8_t imageData;
    size_t imageSize;
    ImageData(uint8_t data, size_t size);
};

class Network {
    public:
    void connectToWiFi(char *ssid, char *password);
    ImageData donwloadImage(char *link);
};