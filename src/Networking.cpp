#pragma once
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
        bool isLandscape;

        QueueItem(int id, String message, String image, String time, bool isLandscape)
        {
            this->id = id;
            this->message = message;
            this->image = image;
            this->time = time;
            this->isLandscape = isLandscape;
        }
        QueueItem()
        {
            this->id = -1;
        }
    };

    typedef struct {
        int type;
        String serverContent;
        int year;
        int month;
        int day;

    } LoveTextData;
    class Network
    {
    private:
        String baseUrl = "http://80.99.154.229:5000";
        String backgroundImageURL = "http://80.99.154.229:5000/static/background/heartBackground.jpg";

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
            bool isBackground = false;

            if (link == backgroundImageURL) isBackground = true;

            HTTPClient http;

            // Send HTTP GET request
            http.begin(link);
            int httpCode = http.GET();

            // Check HTTP status code
            if (httpCode == HTTP_CODE_OK)
            {
                // Open file for writing
                File file; 
                if (!isBackground) {
                    file = SPIFFS.open("/image.jpg", FILE_WRITE);
                } else {
                    file = SPIFFS.open("/background/heartBackground.jpg", FILE_WRITE);
                }
                if (!file)
                {
                    throw std::runtime_error("Download not success. FileWriteError");
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
                if (isBackground) this->backgroundDownloaded();
            }
            else
            {
                Serial.printf("HTTP GET failed, error code: %d\n", httpCode);
                http.end();
                throw std::runtime_error("Download not success. HTTPError");
                return;
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
            http.end();
            throw std::runtime_error("Problem with the queue status download.");
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
                    bool isLandscape = obj["isLandscape"];
                    http.end();
                    return QueueItem(id, message, image, time, isLandscape);
                }
                else
                {
                    Serial.print("Wrong request on getLastQueue! CODE: ");
                    Serial.println(httpCode);
                    http.end();
                    throw std::runtime_error("Get last queue problem");
                }
            }
            throw std::runtime_error("There is no queue item to download.");
        }
        bool lastPostDisplayed()
        {
            HTTPClient http;
            http.begin(baseUrl + "/lastPostDisplayed");
            int httpCode = http.GET();
            if (httpCode) {
                String payload = http.getString();
                DynamicJsonDocument doc(128);
                deserializeJson(doc, payload);
                JsonObject obj = doc.as<JsonObject>();
                http.end();
                return obj["success"];
            } else throw std::runtime_error("Problem with lastPostDisplayed.");
        }

        LoveTextData getLoveText()
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

                /// The required JSON Data:
                int type = obj["type"];
                String loveTextStr = obj["loveText"];
                int year = obj["year"];
                int month = obj["month"];
                int day = obj["day"];

                LoveTextData result = {type, loveTextStr, year, month, day};

                // TODO: Need to prepare predefined love texts, based on enum cases coming from the server.
                http.end();
                return result;
            }
            else
            {
                Serial.println(httpCode);
                throw std::runtime_error("Problem with getLoveText");
            }
            http.end();
            throw std::runtime_error("Problem with getLoveText");
        }
        
        bool updateBackground() {
            HTTPClient http;
            http.begin(baseUrl + "/get/backgroundHandler");
            int httpCode = http.GET();
            
            if (httpCode == 200) {
                String payload = http.getString();
                DynamicJsonDocument doc(512);
                deserializeJson(doc, payload);
                JsonObject obj = doc.as<JsonObject>();

                bool isDownloaded = obj["isDownloaded"];
                if (isDownloaded) {
                    return true;
                } else {
                    this->downloadImage(backgroundImageURL);
                    return true;
                }
            }
            return false;
        }
        bool backgroundDownloaded() {
            HTTPClient http;
            http.begin(baseUrl + "/newBackgroundDownloaded");
            int httpCode = http.GET();

            return httpCode == 200;
        }
    };
}