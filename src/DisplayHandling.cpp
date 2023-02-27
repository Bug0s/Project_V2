#pragma once
#include "Arduino.h"
#include "Arduino_GFX_Library.h"
#include "Networking.cpp"
#include "DataHandling.cpp"


namespace DisplayHandling {
    class DisplayHandler {
        private:
        Arduino_DataBus* bus = create_default_Arduino_DataBus();
            
        public:
        Arduino_GFX *gfx = new Arduino_ILI9488_18bit(bus, DF_GFX_RST, 3 /* rotation */, false /* IPS */);
        void initTFT() {
            gfx->begin();
            gfx->fillScreen(BLACK);
            gfx->setTextColor(2);
            gfx->setTextColor(WHITE);
            pinMode(22, OUTPUT);
            setBackgroundLed(255);
            createHeadline();
        }

        void setBackgroundLed(int value) {
            analogWrite(22,value);
        }

        void createHeadline() {
            gfx->fillRect(0,0,480,20, RED);
        }
        void downloadAndDisplayImage(char* link, int pos_x, int pos_y) {
            Networking::ImageData data = Networking::Network().donwloadImage(link);
            if (DataHandling::JpegHandler::decodeArray((const uint8_t*)data.imageData, data.imageSize)) {
                
            }
        }
    };
}
