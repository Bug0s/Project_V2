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
            drawJpeg("/batteryCharging.jpg", 480-15, 0, gfx);
            
        }

        void downloadAndDisplayImage(char* link, int xpos, int ypos) {
            Networking::Network().downloadImage(link);
            this->drawJpeg("/image.jpg", xpos, ypos, this->gfx);
        }


        void drawJpeg(const char *filename, int xpos, int ypos, Arduino_GFX* tft)
        {

            Serial.println("===========================");
            Serial.print("Drawing file: ");
            Serial.println(filename);
            Serial.println("===========================");

            // Open the named file (the Jpeg decoder library will close it after rendering image)
            fs::File jpegFile = SPIFFS.open(filename, "r"); // File handle reference for SPIFFS
            //  File jpegFile = SD.open( filename, FILE_READ);  // or, file handle reference for SD library

            // ESP32 always seems to return 1 for jpegFile so this null trap does not work
            if (!jpegFile)
            {
                Serial.print("ERROR: File \"");
                Serial.print(filename);
                Serial.println("\" not found!");
                return;
            }

            // Use one of the three following methods to initialise the decoder,
            // the filename can be a String or character array type:

            // boolean decoded = JpegDec.decodeFsFile(jpegFile); // Pass a SPIFFS file handle to the decoder,
            // boolean decoded = JpegDec.decodeSdFile(jpegFile); // or pass the SD file handle to the decoder,
            boolean decoded = JpegDec.decodeFsFile(filename); // or pass the filename (leading / distinguishes SPIFFS files)

            if (decoded)
            {
                // print information about the image to the serial port
                // jpegInfo();

                // render the image onto the screen at given coordinates
                JpegHandler::jpegRender(xpos, ypos, tft);
            }
            else
            {
                Serial.println("Jpeg file format not supported!");
            }
        }
    };
}
#endif