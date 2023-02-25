#include "Arduino.h"
#include "WiFi.h"
#include "SPI.h"
#include "FS.h"
#include "SPIFFS.h"
#include "HTTPClient.h"

namespace Networking
{
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
        void donwloadImage(char *link)
        {
            File file = SPIFFS.open("/downloads/testt.png", "w");
            HTTPClient downloadImage;
            downloadImage.begin(link);
            int httpCode = downloadImage.GET();
            WiFiClient *stream = downloadImage.getStreamPtr();
            size_t downloaded_data_size = 0;
            const size_t SONG_SIZE = downloadImage.getSize();
            while (downloaded_data_size < SONG_SIZE)
            {
                size_t available_data_size = stream->available();
                if (available_data_size > 0)
                {
                    uint8_t *audio_data = (uint8_t *)malloc(available_data_size);
                    stream->readBytes(audio_data, available_data_size);
                    file.write(audio_data, available_data_size);
                    downloaded_data_size += available_data_size;
                    Serial.println(file.readString());
                    free(audio_data);
                }
            }

            file.close();
        }
    };

}