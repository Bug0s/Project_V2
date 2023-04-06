#ifndef DISPLAYHANDLING_CPP
#define DISPLAYHANDLING_CPP
#include "Arduino.h"
#include "Arduino_GFX_Library.h"
#include "Networking.cpp"
#include "DataHandling.cpp"
#include "XPT2046_Touchscreen.h"

using namespace DataHandling;

namespace DisplayHandling
{
    struct TouchPoint {
        int x;
        int y;
        bool isValid;
        TouchPoint(int x, int y) {
            this->x = x;
            this->y = y;
            this->isValid = true;
        }
        TouchPoint(bool isValid) {
            this->x = 0;
            this->y = 0;
            this->isValid = isValid;
        }
    };
    class DisplayHandler
    {
    private:
        Arduino_DataBus *bus = create_default_Arduino_DataBus();
        JpegHandler jpegHandler = JpegHandler();

        

    public:
        Arduino_GFX *gfx = new Arduino_ILI9488_18bit(bus, DF_GFX_RST, 3 /* rotation */, false /* IPS */);
        XPT2046_Touchscreen ts = XPT2046_Touchscreen(21);
        void initTFT()
        {
            gfx->begin();
            gfx->fillScreen(BLACK);
            gfx->setTextSize(2);
            gfx->setTextColor(WHITE);
            pinMode(22, OUTPUT);
            setBackgroundLed(100);
            drawHomeScreen();
            ts.begin();
            
            
        }

        // Sets the background led strongness by percentage
        void setBackgroundLed(int value)
        {
            analogWrite(22, 255 * value / 100);
        }

        void resetScreen()
        {
            gfx->fillScreen(BLACK);
        }

        // Downloads a JPG and displays it to the TFT
        void downloadAndDisplayImage(char *link, int xpos, int ypos)
        {
            Networking::Network().downloadImage(link);
            this->drawJpeg("/image.jpg", xpos, ypos, this->gfx);
        }

        // Draws a JPG from SPIFFS
        void drawJpeg(const char *filename, int xpos, int ypos, Arduino_GFX *tft)

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

        // SCREENS

        // Draws the status bar
        void createHeadline() {
            gfx->fillRect(0,0,480,20, RED);
            drawJpeg("/batteryCharging.jpg", 480-40, 1, gfx);
        }
        void drawHomeScreen()
        {
            createHeadline();

            //Background
            drawJpeg("/backgrounds/homeBackground.jpg", 0, 20, this->gfx);

            gfx->drawRect(35, 40, 100, 100, YELLOW);   // Messages Upper left
            gfx->drawRect(140, 170, 100, 100, YELLOW); // Heart Lower left
            gfx->drawRect(245, 40, 100, 100, YELLOW);  // History Upper right
            gfx->drawRect(350, 170, 100, 100, YELLOW); // ??? Lower right

            
        }

        void drawDownloadScreen()
        {
            createHeadline();

            gfx->drawRect(100, 60, 200, 280, RED);

            gfx->setCursor(120, 75);
            gfx->setTextColor(WHITE);
            gfx->setTextSize(2);
            gfx->println("Üzenet letöltése..."); // ??
        }

        void drawMessageScreen()
        {
            createHeadline();

            gfx->fillRect(50, 40, 380, 100, BLUE);

            // BUTTONS
            gfx->drawRect(420, 240, 60, 80, YELLOW); // may should be ROUNDED?
            gfx->drawFastHLine(420, 280, 60, YELLOW);
        }

        void drawHistoryScreen() {
            createHeadline();
        }

        void drawLoveScreen() {
            createHeadline();
        }

        void makeTransition(void (*to)()) {
            //Transition backlight to 0
            for (int i = 100; i<=0;) {
                setBackgroundLed(--i);
                delay(1);
            }
            //reset screen
            resetScreen();
            //draw the new screen
            to();
            //transition backlight to 100
            for (int i = 0; i>=100;) {
                setBackgroundLed(++i);
                delay(1);
            }
        }

        TouchPoint senseTouch() {
            TS_Point point = ts.getPoint();
            int maxY = 3650;
            int maxX = 3600;

            double divisionY = 11.4;
            double divisionX = 7.5;

            if (point.z != 0) {
                TouchPoint corrigation = TouchPoint(point.x - 240, point.y - 260);
                int resultX = corrigation.x / divisionX;
                int resultY = corrigation.y / divisionY;
                if (resultX < 0 || resultY < 0) {
                    return TouchPoint(false);
                }
                return TouchPoint(corrigation.x / divisionX, corrigation.y / divisionY);

                
            }
            return TouchPoint(false);
        }
        bool senseObject(int x1, int x2, int y1, int y2) {
            TouchPoint tp = senseTouch();
            //Sense wether the tocuh happened within the coordinates
            return false;
        }
        
    };
}
#endif