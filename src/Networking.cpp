#pragma once
// #ifndef NETWORKING_CPP
// #define NETWORKING_CPP
#include "Arduino.h"
#include "WiFi.h"
#include "SPI.h"
#include "FS.h"
#include "SPIFFS.h"
#include "HTTPClient.h"
#include "ArduinoJson.h"

namespace Networking
{

    class QueueItem
    {
    public:
        int id;
        String message;
        String image;
        String time;

        QueueItem(int id, String message, String image, String time)
        {
            this->id = id;
            this->message = message;
            this->image = image;
            this->time = time;
        }
        QueueItem()
        {
            this->id = -1;
        }
    };

    class Network
    {
    private:
        String baseUrl = "http://80.99.154.229:5000";

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

        void downloadImage(String link)
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
        }

        int getQueueStatus()
        {
            HTTPClient http;
            http.begin("http://80.99.154.229:5000/queueStatus");
            int httpCode = http.GET();
            if (httpCode == 200)
            {
                String payload = http.getString();
                DynamicJsonDocument doc(1024);
                deserializeJson(doc, payload);
                JsonObject obj = doc.as<JsonObject>();

                // Access JSON data
                int count = obj["count"];
                http.end();
                return count;
            }
            else
            {
                Serial.print("Wrong request! CODE: ");
                Serial.println(httpCode);
            }
            http.end();
            return -1;
        }

        QueueItem getLastQueue()
        {
            int queueStatus = getQueueStatus();
            bool check = queueStatus > 0;
            if (check)
            {
                HTTPClient http;
                http.begin(baseUrl + "/get/queue/last");
                int httpCode = http.GET();
                if (httpCode == 200)
                {
                    String payload = http.getString();
                    DynamicJsonDocument doc(1024);
                    deserializeJson(doc, payload);
                    JsonObject obj = doc.as<JsonObject>();

                    int id = obj["id"];
                    String message = obj["message"];
                    String image = obj["image"];
                    String time = obj["time"];
                    http.end();
                    return QueueItem(id, message, image, time);
                }
                else
                {
                    Serial.print("Wrong request on getLastQueue! CODE: ");
                    Serial.println(httpCode);
                    http.end();
                    return QueueItem();
                }
            }
            return QueueItem();
        }
        bool lastPostDisplayed()
        {
            HTTPClient http;
            http.begin(baseUrl + "/lastPostDisplayed");
            http.GET();
            String payload = http.getString();
            DynamicJsonDocument doc(128);
            deserializeJson(doc, payload);
            JsonObject obj = doc.as<JsonObject>();
            http.end();
            return obj["success"];
        }

        
        wchar_t* getLoveText()
        {
            HTTPClient http;
            http.begin(baseUrl + "/get/loveText");
            int httpCode = http.GET();
            if (httpCode == 200)
            {
                String payload = http.getString();
                DynamicJsonDocument doc(512);
                deserializeJson(doc, payload);
                JsonObject obj = doc.as<JsonObject>();

                ///The required JSON Data:
                const String loveTextStr = obj["loveText"];
                
                //TODO: Need to prepare predefined love texts, based on enum cases coming from the server.
                http.end();
                return L"   Gréta manócskám nagyon \n\n     szeretlek! <3";

                
            }
            else
            {
                Serial.print("Wrong request! CODE: ");
                Serial.println(httpCode);
            }
            http.end();
            return L"Connection error!";
        }
    };
}
// #endif