#pragma once
// #ifndef NETWORKING_CPP
// #define NETWORKING_CPP
#include "Arduino.h"
#include "WiFi.h"
#include "SPI.h"
#include "FS.h"
#include "SPIFFS.h"
#include "HTTPClient.h"

namespace Networking
{
    class ImageData
    {
    public:
        uint8_t imageData;
        size_t imageSize;
        const uint8_t* imageDataPtr;
        ImageData(uint8_t data, size_t size)
        {
            this->imageData = data;
            this->imageSize = size;
            this->imageDataPtr = &imageData;
            Serial.println("Class contruct:!");
            Serial.println(sizeof(*imageDataPtr));
        }
    };

    class Network
    {
    public:
        void connectToWiFi(char *ssid, char *password)
        {
            WiFi.begin(ssid, password);
            while (WiFi.status() != WL_CONNECTED)
            {
                delay(1000);
                Serial.println("Connecting to WiFi...");
            }
            // Connected!
            Serial.print("Connected to WiFi: ");
            Serial.println((String)ssid);
        }

        ImageData donwloadImage(char *link)
        {
            // File file = SPIFFS.open("/downloads/testt.png", "w");
            HTTPClient downloadImage;
            downloadImage.begin(link);
            int httpCode = downloadImage.GET();
            WiFiClient *stream = downloadImage.getStreamPtr();
            size_t downloaded_data_size = 0;
            const size_t imageSize = downloadImage.getSize();
            uint8_t returnImage;
            while (downloaded_data_size < imageSize)
            {
                size_t available_data_size = stream->available();
                if (available_data_size > 0)
                {
                    uint8_t *imageData = (uint8_t *)malloc(available_data_size);
                    stream->readBytes(imageData, available_data_size);
                    // file.write(imageData, available_data_size);
                    returnImage += *imageData;
                    downloaded_data_size += available_data_size;
                    // Serial.println(file.readString());
                    return ImageData(*imageData, imageSize);
                    free(imageData);
                }

                // file.close();
            }
        }
    };
}
// #endif