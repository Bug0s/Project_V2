#ifndef DISPLAYHANDLING_CPP
#define DISPLAYHANDLING_CPP
#include "Arduino.h"
#include "Arduino_GFX_Library.h"
#include "Networking.cpp"
#include "DataHandling.cpp"
#include "XPT2046_Touchscreen.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

using namespace DataHandling;
using namespace Networking;

namespace DisplayHandling
{
    struct TouchPoint
    {
        int x;
        int y;
        bool isValid;
        TouchPoint(int x, int y)
        {
            this->x = x;
            this->y = y;
            this->isValid = true;
        }
        TouchPoint(bool isValid)
        {
            this->x = 0;
            this->y = 0;
            this->isValid = isValid;
        }
    };

    enum Screens
    {
        Home,
        History,
        Downloading,
        Message,
        Love
    };

    class DisplayHandler
    {
    private:
        Arduino_DataBus *bus = create_default_Arduino_DataBus();
        JpegHandler jpegHandler = JpegHandler();
        Network network = Network();
        QueueItem queueItem;
        const char* localImage = "/image.jpg";
        struct Box
        {
        private:
            uint16_t color;
            Arduino_GFX *gfx;

            int width;
            int height;

        public:
            int x1;
            int y1;
            int x2;
            int y2;
            Box(int x, int y, int width, int height, uint16_t color, Arduino_GFX *gfx)
            {
                this->gfx = gfx;
                this->width = width;
                this->height = height;
                this->color = color;
                this->x1 = x;
                this->y1 = y;

                this->x2 = x1 + width;
                this->y2 = y1 + height;
            }
            void drawBox()
            {
                gfx->drawRect(x1, y1, width, height, color);
            }
        };


    public:
        Arduino_GFX *gfx = new Arduino_ILI9488_18bit(bus, DF_GFX_RST, 3 /* rotation */, false /* IPS */);
        XPT2046_Touchscreen ts = XPT2046_Touchscreen(21);

        int messageCount;
        void initTFT()
        {
            gfx->begin();
            gfx->fillScreen(BLACK);
            gfx->setTextSize(2);
            gfx->setTextColor(WHITE);
            pinMode(22, OUTPUT);
            setBackgroundLed(100);
            ts.begin();
            // xTaskCreatePinnedToCore(&drawHomeScreen, "HomeScreen", 1024, NULL, 2, NULL, 0);
            drawHomeScreen2();
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
            this->drawJpeg("/image.jpg", xpos, ypos);
        }

        // Draws a JPG from SPIFFS
        void drawJpeg(const char *filename, int xpos, int ypos)

        {
            Arduino_GFX *tft = this->gfx;
            /*
            Serial.println("===========================");
            Serial.print("Drawing file: ");
            Serial.println(filename);
            Serial.println("===========================");
            */
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
        void createHeadline()
        {
            gfx->fillRect(0, 0, 480, 20, WHITE);
            drawJpeg("/icons/batteryCharging.jpg", 480 - 40, 1);          // w: 33
            drawJpeg("/icons/WiFiOn.jpg", 440 - 33 - 15, 1);              // w: 24
            drawJpeg("/icons/syncArrow.jpg", 440 - 33 - 15 - 24 - 15, 0); // h: 9, w:11
        }

        void homeScreenTouch(Box b1, Box b2, Box b3, Box b4)
        {
            Box upperLeft = b1;
            Box lowerLeft = b2;
            Box upperRight = b3;
            Box lowerRight = b4;
        }
        void drawHomeScreen()
        {
            Box upperLeft = Box(110, 40, 100, 100, YELLOW, gfx);
            Box lowerLeft = Box(110, 200, 100, 100, YELLOW, gfx);
            Box upperRight = Box(270, 40, 100, 100, YELLOW, gfx);
            Box lowerRight = Box(270, 200, 100, 100, YELLOW, gfx);
            Box buttons[4] = {upperLeft, lowerLeft, upperRight, lowerRight};
            createHeadline();

            // Background
            drawJpeg("/backgrounds/homeBackground.jpg", 0, 20);
            for (int i = 0; i <= 3; i++)
            {
                buttons[i].drawBox();
            }
            drawJpeg("/buttonIcons/mail3p.jpg", 110, 40);

            // TOUCHSENSE
            while (true)
            {
                if (senseObject(upperLeft.x1, upperLeft.x2, upperLeft.y1, upperLeft.y2))
                {
                    makeTransition(Screens(Message));
                    break;
                }
                if (senseObject(lowerLeft.x1, lowerLeft.x2, lowerLeft.y1, lowerLeft.y2))
                {
                    makeTransition(Screens(Love));
                    break;
                }
                if (senseObject(upperRight.x1, upperRight.x2, upperRight.y1, upperRight.y2))
                {
                    makeTransition(Screens(History));
                    break;
                }
                if (senseObject(lowerRight.x1, lowerRight.x2, lowerRight.y1, lowerRight.y2))
                {
                    makeTransition(Screens(Downloading));
                    break;
                }
            }
        }
        void drawHomeScreen2()
        {
            Box upperLeft = Box(16, 200, 100, 100, YELLOW, gfx);
            Box lowerLeft = Box(132, 200, 100, 100, YELLOW, gfx);
            Box upperRight = Box(248, 200, 100, 100, YELLOW, gfx);
            Box lowerRight = Box(364, 200, 100, 100, YELLOW, gfx);
            Box buttons[4] = {upperLeft, lowerLeft, upperRight, lowerRight};
            createHeadline();
            drawJpeg("/backgrounds/homeBackground.jpg", 0, 20);
            for (int i = 0; i <= 3; i++)
            {
                buttons[i].drawBox();
            }
            drawJpeg("/buttonIcons/mail3p.jpg", upperLeft.x1, upperLeft.y1);

            // TOUCHSENSE
            void senseTouchHome(void* params) {
                
            }
            while (true)
            {
                if (senseObject(upperLeft.x1, upperLeft.x2, upperLeft.y1, upperLeft.y2))
                {
                    makeTransition(Screens(Downloading));
                    break;
                }
                if (senseObject(lowerLeft.x1, lowerLeft.x2, lowerLeft.y1, lowerLeft.y2))
                {
                    makeTransition(Screens(Love));
                    break;
                }
                if (senseObject(upperRight.x1, upperRight.x2, upperRight.y1, upperRight.y2))
                {
                    makeTransition(Screens(History));
                    break;
                }
                if (senseObject(lowerRight.x1, lowerRight.x2, lowerRight.y1, lowerRight.y2))
                {
                    makeTransition(Screens(Downloading));
                    break;
                }
            }
        }

        void drawDownloadScreen()
        {
            createHeadline();
            setBackgroundLed(100);
            gfx->drawRect(100, 60, 200, 280, RED);

            gfx->setCursor(120, 75);
            gfx->setTextColor(WHITE);
            gfx->setTextSize(2);
            gfx->println("Üzenet letöltése..."); // ??
            //gfx->drawChar(5, 30, 'é', WHITE, BLACK); // á
            //gfx->drawChar(50, 30, 'á', WHITE, BLACK); // é
            //gfx->drawChar(150, 30, 'ü', WHITE, BLACK); // ü
            delay(50);
            this->messageCount = network.getQueueStatus();
            queueItem = network.getLastQueue();
            Serial.println(queueItem.image);
            network.downloadImage(queueItem.image);
            //makeTransition(Screens(Message));
            
        }

        void drawMessageScreen()
        {
            createHeadline();

            //gfx->fillRect(50, 40, 380, 100, BLUE);

            // BUTTONS
            gfx->drawRect(420, 240, 60, 80, YELLOW); // may should be ROUNDED?
            gfx->drawFastHLine(420, 280, 60, YELLOW);

            drawJpeg(localImage, 40, 40);
            network.lastPostDisplayed();
        }

        void drawHistoryScreen()
        {
            createHeadline();
        }

        void drawLoveScreen()
        {
            createHeadline();
        }

        void makeTransition(Screens screenName)
        {
            // Transition backlight to 0
            for (int i = 100; i > 0;)
            {
                setBackgroundLed(--i);
                delay(1);
            }
            // reset screen
            resetScreen();
            // draw the new screen
            switch (screenName)
            {
            case Home:
                drawHomeScreen();
                break;
            case History:
                drawHistoryScreen();
                break;
            case Love:
                drawLoveScreen();
                break;
            case Message:
                drawMessageScreen();
                break;
            case Downloading:
                drawDownloadScreen();
                break;
            }
            // transition backlight to 100
            for (int i = 0; i < 100;)
            {
                setBackgroundLed(++i);
                delay(1);
            }
            setBackgroundLed(100);
        }

        TouchPoint senseTouch()
        {
            TS_Point point = ts.getPoint();
            int maxY = 3650;
            int maxX = 3600;

            double divisionY = 11.4;
            double divisionX = 7.5;

            if (point.z != 0)
            {
                TouchPoint corrigation = TouchPoint(point.x - 240, point.y - 260);
                int resultX = corrigation.x / divisionX;
                int resultY = corrigation.y / divisionY;
                if (resultX < 0 || resultY < 0)
                {
                    return TouchPoint(false);
                }
                return TouchPoint(corrigation.x / divisionX, corrigation.y / divisionY);
            }
            return TouchPoint(false);
        }
        bool senseObject(int x1, int x2, int y1, int y2)
        {
            TouchPoint tp = senseTouch();
            // Sense wether the tocuh happened within the coordinates
            if (tp.x > x1 && tp.x < x2 && tp.y > y1 && tp.y < y2)
            {
                Serial.println(" got touched!");
                return true;
            }
            return false;
        }
    };

}
#endif