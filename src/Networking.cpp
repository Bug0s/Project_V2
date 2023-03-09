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
        const uint8_t *imageDataPtr;
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

        void downloadImage(char *link)
        {
            // File file = SPIFFS.open("/downloads/breakpoint.png", "w");
            HTTPClient http;

            // Send HTTP GET request
            http.begin(link);
            int httpCode = http.GET();

            // Check HTTP status code
            if (httpCode == HTTP_CODE_OK)
            {
                // Open file for writing
                File file = SPIFFS.open("/image.jpg", FILE_WRITE);
                if (!file)
                {
                    Serial.println("Failed to open file for writing");
                    return;
                }

                // Read response into buffer and write to file
                WiFiClient *stream = http.getStreamPtr();
                const size_t bufferSize = 1024;
                uint8_t buffer[bufferSize];
                int bytesRead;
                while ((bytesRead = stream->readBytes(buffer, bufferSize)) > 0)
                {
                    file.write(buffer, bytesRead);
                }

                // Close file
                file.close();
                Serial.println("Image downloaded");
            }
            else
            {
                Serial.printf("HTTP GET failed, error code: %d\n", httpCode);
            }
            http.end();
            //return ImageData(buffer, imageSize);
        }
    };
}
// #endif