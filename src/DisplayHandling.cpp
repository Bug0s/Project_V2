#ifndef DISPLAYHANDLING_CPP
#define DISPLAYHANDLING_CPP
#include "Arduino.h"
#include "Arduino_GFX_Library.h"
#include "Networking.cpp"
#include "DataHandling.cpp"

using namespace DataHandling;

namespace DisplayHandling {
    class DisplayHandler {
        private:
        Arduino_DataBus* bus = create_default_Arduino_DataBus();
        JpegHandler jpegHandler = JpegHandler();
            
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
            jpegHandler.drawJpeg("/batteryCharging.jpg", 480-15, 0, gfx);
            
        }
    };
}
#endif