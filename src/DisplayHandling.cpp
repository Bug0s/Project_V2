#pragma once
#ifndef DISPLAYHANDLING_CPP
#define DISPLAYHANDLING_CPP
#include "Arduino.h"
#include "Arduino_GFX_Library.h"
#include "Networking.cpp"
#include "DataHandling.cpp"
#include "XPT2046_Touchscreen.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "TaskHandler.h"

using namespace DataHandling;
using namespace Networking;
using namespace TaskHandler;

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
        const char *localImage = "/image.jpg";
        // If true the user should not view any new messages!
        bool blockMessages = false;
        void badConnection()
        {
            this->blockMessages = true;
        }
        void goodConnection()
        {
            this->blockMessages = false;
        }

        wchar_t *segmentText(wchar_t *text, int lineStart)
        {
            int textLength = wcslen(text);
            int numLineBreaks = 0;

            // Count the number of line breaks in the text
            for (int i = 0; i < textLength; i++)
            {
                if (text[i] == '\n')
                {
                    numLineBreaks++;
                }
            }

            // Calculate the new text length with additional line breaks and whitespaces
            int newTextLength = textLength + (numLineBreaks * 2 + 1) * lineStart;

            // Create a new character array to store the segmented text
            wchar_t *segmentedText = new wchar_t[newTextLength + 1];

            int j = 0;
            for (int i = 0; i < textLength; i++)
            {
                segmentedText[j++] = text[i];
                if (text[i] == '\n')
                {
                    // Add the specified number of whitespaces after a line break
                    for (int k = 0; k < lineStart; k++)
                    {
                        segmentedText[j++] = L' ';
                    }
                    segmentedText[j++] = L'\n'; // Add an additional line break
                    for (int k = 0; k < lineStart; k++)
                    {
                        segmentedText[j++] = L' ';
                    }
                }
            }

            // Add a null-terminating character at the end of the segmented text
            segmentedText[j] = L'\0';

            return segmentedText;
        }
        bool isSpecialChar(wchar_t c)
        {
            const wchar_t *specialChars[] = {L"á", L"é", L"í", L"ó", L"ö", L"ő", L"ú", L"ü", L"ű", L"Á", L"É", L"Í", L"Ó", L"Ö", L"Ő", L"Ú", L"Ü", L"Ű"};
            int numSpecialChars = sizeof(specialChars) / sizeof(specialChars[0]);

            for (int i = 0; i < numSpecialChars; i++)
            {
                if (c == specialChars[i][0])
                {
                    return true;
                }
            }

            return false;
        }

        void displayComplexText(wchar_t *text)
        {
            for (int i = 0; i < wcslen(text); i++)
            {
                wchar_t currentChar = text[i];
                if (isSpecialChar(currentChar))
                {
                    // Not safe
                    int16_t cursorX = gfx->getCursorX();
                    int16_t cursorY = gfx->getCursorY();

                    if (currentChar == *L"á")
                    {
                        gfx->drawLine(cursorX + 3, cursorY - 0, cursorX + 3 + 2, cursorY - 0 - 2, WHITE);
                        gfx->drawLine(cursorX + 4, cursorY - 0, cursorX + 4 + 2, cursorY - 0 - 2, WHITE);
                        gfx->print("a");
                    }

                    else if (currentChar == *L"é")
                    {
                        gfx->drawLine(cursorX + 4, cursorY - 0, cursorX + 4 + 2, cursorY - 0 - 2, WHITE);
                        gfx->drawLine(cursorX + 5, cursorY - 0, cursorX + 5 + 2, cursorY - 0 - 2, WHITE);
                        gfx->print("e");
                    }
                    else if (currentChar == *L"í")
                    {
                        gfx->drawLine(cursorX + 4, cursorY - 0, cursorX + 4 + 2, cursorY - 0 - 2, WHITE);
                        gfx->drawLine(cursorX + 5, cursorY - 0, cursorX + 5 + 2, cursorY - 0 - 2, WHITE);
                        gfx->print("i");
                    }

                    else if (currentChar == *L"ó")
                    {
                        gfx->drawLine(cursorX + 4, cursorY - 0, cursorX + 4 + 2, cursorY - 0 - 2, WHITE);
                        gfx->drawLine(cursorX + 5, cursorY - 0, cursorX + 5 + 2, cursorY - 0 - 2, WHITE);
                        gfx->print("o");
                    }
                    else if (currentChar == *L"ö")
                    {
                        gfx->drawPixel(cursorX + 3, cursorY + 1, WHITE);
                        gfx->drawPixel(cursorX + 3, cursorY - 0, WHITE);
                        gfx->drawPixel(cursorX + 2, cursorY + 1, WHITE);
                        gfx->drawPixel(cursorX + 2, cursorY - 0, WHITE);

                        gfx->drawPixel(cursorX + 7, cursorY + 1, WHITE);
                        gfx->drawPixel(cursorX + 7, cursorY - 0, WHITE);
                        gfx->drawPixel(cursorX + 6, cursorY + 1, WHITE);
                        gfx->drawPixel(cursorX + 6, cursorY - 0, WHITE);

                        gfx->print("o");
                    }
                    else if (currentChar == *L"ő")
                    {
                        gfx->drawLine(cursorX + 3, cursorY - 0, cursorX + 3 + 2, cursorY - 0 - 2, WHITE);
                        gfx->drawLine(cursorX + 4, cursorY - 0, cursorX + 4 + 2, cursorY - 0 - 2, WHITE);

                        gfx->drawLine(cursorX + 6, cursorY - 0, cursorX + 6 + 2, cursorY - 0 - 2, WHITE);
                        gfx->drawLine(cursorX + 7, cursorY - 0, cursorX + 7 + 2, cursorY - 0 - 2, WHITE);

                        gfx->print("o");
                    }
                    else if (currentChar == *L"ú")
                    {
                        gfx->drawLine(cursorX + 4, cursorY - 0, cursorX + 4 + 2, cursorY - 0 - 2, WHITE);
                        gfx->drawLine(cursorX + 5, cursorY - 0, cursorX + 5 + 2, cursorY - 0 - 2, WHITE);
                        gfx->print("u");
                    }

                    else if (currentChar == *L"ü")
                    {
                        gfx->drawPixel(cursorX + 3, cursorY + 1, WHITE);
                        gfx->drawPixel(cursorX + 3, cursorY - 0, WHITE);
                        gfx->drawPixel(cursorX + 2, cursorY + 1, WHITE);
                        gfx->drawPixel(cursorX + 2, cursorY - 0, WHITE);

                        gfx->drawPixel(cursorX + 7, cursorY + 1, WHITE);
                        gfx->drawPixel(cursorX + 7, cursorY - 0, WHITE);
                        gfx->drawPixel(cursorX + 6, cursorY + 1, WHITE);
                        gfx->drawPixel(cursorX + 6, cursorY - 0, WHITE);
                        gfx->print("u");
                    }
                    else if (currentChar == *L"ű")
                    {
                        gfx->drawLine(cursorX + 2, cursorY - 0, cursorX + 2 + 2, cursorY - 0 - 2, WHITE);
                        gfx->drawLine(cursorX + 3, cursorY - 0, cursorX + 3 + 2, cursorY - 0 - 2, WHITE);

                        gfx->drawLine(cursorX + 5, cursorY - 0, cursorX + 5 + 2, cursorY - 0 - 2, WHITE);
                        gfx->drawLine(cursorX + 6, cursorY - 0, cursorX + 6 + 2, cursorY - 0 - 2, WHITE);

                        gfx->print("u");
                    }
                    else if (currentChar == *L"Á")
                    {
                        gfx->drawLine(cursorX + 4, cursorY - 0 - 3, cursorX + 4 + 2, cursorY - 0 - 2 - 3, WHITE);
                        gfx->drawLine(cursorX + 5, cursorY - 0 - 3, cursorX + 5 + 2, cursorY - 0 - 2 - 3, WHITE);
                        gfx->print("A");
                    }

                    else if (currentChar == *L"É")
                    {
                        gfx->drawLine(cursorX + 3, cursorY - 0 - 3, cursorX + 3 + 2, cursorY - 0 - 2 - 3, WHITE);
                        gfx->drawLine(cursorX + 4, cursorY - 0 - 3, cursorX + 4 + 2, cursorY - 0 - 2 - 3, WHITE);
                        gfx->print("E");
                    }
                    else if (currentChar == *L"Í")
                    {
                        gfx->drawLine(cursorX + 4, cursorY - 0 - 2, cursorX + 4 + 2, cursorY - 0 - 2 - 2, WHITE);
                        gfx->drawLine(cursorX + 5, cursorY - 0 - 2, cursorX + 5 + 2, cursorY - 0 - 2 - 2, WHITE);
                        gfx->print("I");
                    }

                    else if (currentChar == *L"Ó")
                    {
                        gfx->drawLine(cursorX + 4, cursorY - 0 - 2, cursorX + 4 + 2, cursorY - 0 - 2 - 2, WHITE);
                        gfx->drawLine(cursorX + 5, cursorY - 0 - 2, cursorX + 5 + 2, cursorY - 0 - 2 - 2, WHITE);
                        gfx->print("O");
                    }
                    else if (currentChar == *L"Ö")
                    {
                        gfx->drawPixel(cursorX + 3, cursorY - 2, WHITE);
                        gfx->drawPixel(cursorX + 3, cursorY - 3, WHITE);
                        gfx->drawPixel(cursorX + 2, cursorY - 3, WHITE);
                        gfx->drawPixel(cursorX + 2, cursorY - 2, WHITE);

                        gfx->drawPixel(cursorX + 7, cursorY - 2, WHITE);
                        gfx->drawPixel(cursorX + 7, cursorY - 3, WHITE);
                        gfx->drawPixel(cursorX + 6, cursorY - 3, WHITE);
                        gfx->drawPixel(cursorX + 6, cursorY - 2, WHITE);
                        gfx->print("O");
                    }
                    else if (currentChar == *L"Ő")
                    {
                        gfx->drawLine(cursorX + 3, cursorY - 0 - 2, cursorX + 3 + 2, cursorY - 0 - 2 - 2, WHITE);
                        gfx->drawLine(cursorX + 4, cursorY - 0 - 2, cursorX + 4 + 2, cursorY - 0 - 2 - 2, WHITE);

                        gfx->drawLine(cursorX + 6, cursorY - 0 - 2, cursorX + 6 + 2, cursorY - 0 - 2 - 2, WHITE);
                        gfx->drawLine(cursorX + 7, cursorY - 0 - 2, cursorX + 7 + 2, cursorY - 0 - 2 - 2, WHITE);

                        gfx->print("O");
                    }
                    else if (currentChar == *L"Ú")
                    {
                        gfx->drawLine(cursorX + 4, cursorY - 0 - 2, cursorX + 4 + 2, cursorY - 0 - 2 - 2, WHITE);
                        gfx->drawLine(cursorX + 5, cursorY - 0 - 2, cursorX + 5 + 2, cursorY - 0 - 2 - 2, WHITE);
                        gfx->print("U");
                    }

                    else if (currentChar == *L"Ü")
                    {
                        gfx->drawPixel(cursorX + 3, cursorY - 2, WHITE);
                        gfx->drawPixel(cursorX + 3, cursorY - 3, WHITE);
                        gfx->drawPixel(cursorX + 2, cursorY - 2, WHITE);
                        gfx->drawPixel(cursorX + 2, cursorY - 3, WHITE);

                        gfx->drawPixel(cursorX + 7, cursorY - 2, WHITE);
                        gfx->drawPixel(cursorX + 7, cursorY - 3, WHITE);
                        gfx->drawPixel(cursorX + 6, cursorY - 2, WHITE);
                        gfx->drawPixel(cursorX + 6, cursorY - 3, WHITE);
                        gfx->print("U");
                    }
                    else if (currentChar == *L"Ű")
                    {
                        gfx->drawLine(cursorX + 2, cursorY - 0 - 2, cursorX + 2 + 2, cursorY - 0 - 2 - 2, WHITE);
                        gfx->drawLine(cursorX + 3, cursorY - 0 - 2, cursorX + 3 + 2, cursorY - 0 - 2 - 2, WHITE);

                        gfx->drawLine(cursorX + 5, cursorY - 0 - 2, cursorX + 5 + 2, cursorY - 0 - 2 - 2, WHITE);
                        gfx->drawLine(cursorX + 6, cursorY - 0 - 2, cursorX + 6 + 2, cursorY - 0 - 2 - 2, WHITE);

                        gfx->print("U");
                    }
                    else
                    {
                        Serial.println("UNIDENTIFIED CHAR!");
                    }
                }
                else
                {
                    // safe
                    gfx->print((char)text[i]);
                    continue;
                }
            }
        }

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
            // It should be HOMESCREEN to drawn!!! / testCase
            drawHomeScreen();
            // xTaskCreate(DisplayHandler::taskDrawHomeScreen, "Drawing home screen, and sensing touch", 1200000, NULL, 1, TaskHandlers::drawHomeScreen);
            //vTaskStartScheduler();

            
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
            try
            {
                network.downloadImage(link);
            }
            catch (const std::exception &err)
            {
                onErrorThrown(L"Nem sikerült letölteni a képet.\nPróbáld újra!");
                return;
            }
            this->drawJpeg("/image.jpg", xpos, ypos);
        }

        // Draws a JPG from SPIFFS
        void drawJpeg(const char *filename, int xpos, int ypos)

        {
            Arduino_GFX *tft = this->gfx;
            fs::File jpegFile = SPIFFS.open(filename, "r"); // File handle reference for SPIFFS
            if (!jpegFile)
            {
                Serial.print("ERROR: File \"");
                Serial.print(filename);
                Serial.println("\" not found!");
                return;
            }

            boolean decoded = JpegDec.decodeFsFile(filename); // or pass the filename (leading / distinguishes SPIFFS files)

            if (decoded)
            {
                JpegHandler::jpegRender(xpos, ypos, tft);
            }
            else
            {
                Serial.println("Jpeg file format not supported!");
            }
        }

        // SCREENS

        // Draws the status bar; It should be the first thing that renders at a new screen!
        void createHeadline()
        {
            DataHandling::ProcessHandler::ConnectionStatusCheck connectionStatus = ProcessHandler::checkConnectionStatuses();
            if (connectionStatus.networkCorrect && connectionStatus.serverCorrect)
            {
                this->goodConnection();
            }
            else
            {
                this->badConnection();
            }

            gfx->fillRect(0, 0, 480, 20, WHITE);

            drawJpeg("/icons/batteryCharging.jpg", 480 - 40, 1); // w: 33

            if (connectionStatus.networkCorrect)
            {
                drawJpeg("/icons/WiFiOn.jpg", 440 - 33 - 15, 1); // w: 24
            }
            else
            {
                drawJpeg("/icons/WiFiOff.jpg", 440 - 33 - 15, 1); // w: 24
            }

            if (connectionStatus.serverCorrect)
            {
                drawJpeg("/icons/connectedS.jpg", 480 - 33 - 15 - 24 - 15 - 30, 0);
            }
            else
            {
                drawJpeg("/icons/notConnectedS.jpg", 480 - 33 - 15 - 24 - 15 - 30, 0);
            }
        }

        // @brief Needs to stop via taskHandler 'drawHomeScreen'!
        static void taskDrawHomeScreen(void *params)
        {
            DisplayHandler dp = DisplayHandler();
            dp.drawHomeScreen();
        }
        void drawHomeScreen()
        {
            Box messageButton = Box(45, 200, 100, 100, YELLOW, gfx);
            Box loveButton = Box(190, 200, 100, 100, YELLOW, gfx);
            Box historyButton = Box(335, 200, 100, 100, YELLOW, gfx);

            Box buttons[3] = {messageButton, loveButton, historyButton};
            createHeadline();
            drawJpeg("/backgrounds/homeBackground.jpg", 0, 20);
            for (int i = 0; i < 3; i++)

            {
                buttons[i].drawBox();
            }
            messageCount = network.getQueueStatus();
            if (messageCount == 0)
            {
                this->blockMessages = true;
            }
            else if (messageCount == 1)
            {
                drawJpeg("/buttonIcons/mail1.jpg", messageButton.x1, messageButton.y1);
            }
            else if (messageCount == 2)
            {
                drawJpeg("/buttonIcons/mail2.jpg", messageButton.x1, messageButton.y1);
            }
            else if (messageCount == 3)
            {
                drawJpeg("/buttonIcons/mail3.jpg", messageButton.x1, messageButton.y1);
            }
            else if (messageCount > 3)
            {
                drawJpeg("/buttonIcons/mail3p.jpg", messageButton.x1, messageButton.y1);
            }
            drawJpeg("/buttonIcons/loveButton.jpg", loveButton.x1, loveButton.y1);
            drawJpeg("/buttonIcons/historyButton.jpg", historyButton.x1, historyButton.y1);
            wchar_t *testText = L"Ez egy teljesen\nmintájááraű készült tesztelés.";
            wchar_t *segmented = segmentText(testText, 6);
            gfx->setCursor(130, 65);
            this->displayComplexText(segmented);

            while (true)
            {
                if (senseObject(messageButton) && !blockMessages)
                {
                    makeTransition(Screens(Downloading));
                    break;
                }
                if (senseObject(loveButton))
                {
                    makeTransition(Screens(Love));
                    break;
                }
                if (senseObject(historyButton))
                {
                    makeTransition(Screens(History));
                    break;
                }
            };
        }

        void drawDownloadScreen()
        {
            createHeadline();
            setBackgroundLed(100);
            gfx->drawRect(100, 60, 300, 80, RED);

            gfx->setCursor(120, 75);
            gfx->setTextColor(WHITE);
            gfx->setTextSize(2);
            this->displayComplexText(L"Üzenet letöltése...");
            delay(50);
            try
            {
                messageCount = network.getQueueStatus();
                queueItem = network.getLastQueue();
                network.downloadImage(queueItem.image);
            }
            catch (std::exception &err)
            {
                onErrorThrown(L"Hiba a kép letöltése közben.\nPróbáld újra Baby!");
            }
            makeTransition(Screens(Message));
        }

        static void taskDrawMessageScreen(void *params)
        {
            Serial.println("taskDrawMessageScreen started");
            TaskHandler::TaskHandlers::terminateAllTasks(TaskHandlers::drawMessageScreen);
            DisplayHandler dp = DisplayHandler();
            dp.drawMessageScreen();
        }
        void drawMessageScreen()
        {
            createHeadline();

            // gfx->fillRect(50, 40, 380, 100, BLUE);
            Box homeButton = Box(380, 220, 100, 100, YELLOW, gfx);
            homeButton.drawBox();
            drawJpeg("/buttonIcons/homeButton.jpg", homeButton.x1, homeButton.y1);

            Box nextButton = Box(380, 120, 100, 100, YELLOW, gfx);
            if (--messageCount > 0)
            {
                nextButton.drawBox();
                drawJpeg("/buttonIcons/arrowOn.jpg", nextButton.x1, nextButton.y1);
            }
            else
            {
                nextButton.drawBox();
                drawJpeg("/buttonIcons/arrowOff.jpg", nextButton.x1, nextButton.y1);
            }
            gfx->drawFastHLine(380, 220, 100, BLACK);
            drawJpeg(localImage, 40, 40);
            network.lastPostDisplayed();
            while (true)
            {
                if (senseObject(homeButton))
                {
                    makeTransition(Screens(Home));
                    break;
                }
                if (senseObject(nextButton) && messageCount > 0)
                {
                    makeTransition(Screens(Downloading));
                    break;
                }
            }
        }

        static void taskDrawHistoryScreen(void *params)
        {
            DisplayHandler dp = DisplayHandler();
            dp.drawHistoryScreen();
        }
        void drawHistoryScreen()
        {
            createHeadline();
        }

        static void taskDrawLoveScreen(void *params)
        {
            Serial.println("Love task launched!");
            DisplayHandler dp = DisplayHandler();
            dp.drawLoveScreen();
        }
        void drawLoveScreen()
        {
            Box homeButton = Box(380, 220, 100, 100, YELLOW, gfx);
            homeButton.drawBox();
            this->drawJpeg("/buttonIcons/homeButton.jpg", homeButton.x1, homeButton.y1);
            createHeadline();
            gfx->setCursor(100, 100);
            gfx->println("");
            this->displayComplexText(segmentText(network.getLoveText(), 8));
            while (true)
            {
                if (senseObject(homeButton))
                {
                    makeTransition(Screens(Home));
                    break;
                }
            }

            // this->displayComplexText(L"teszt A Á E É I Í O Ó Ö Ő U Ú Ü Ű. Teszt VÉGE");
            // this->displayComplexText(L"teszt O Ö Ő U Ú Ü Ű");
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
            for (int i = 0; i < 100;)
            {
                setBackgroundLed(++i);
                delay(1);
            }
            setBackgroundLed(100);

            TaskHandlers th = TaskHandler::TaskHandlers();

            switch (screenName)
            {
            case Home:
                drawHomeScreen();
                xTaskCreate(DisplayHandler::taskDrawHomeScreen, "Draw Home screen and sense touches on it", 1200000, NULL, 1, TaskHandlers::drawHomeScreen);
                th.terminateAllTasks(th.drawHomeScreen);
                break;
            case History:
                drawHistoryScreen();
                break;
            case Love:
                drawLoveScreen();
                xTaskCreate(DisplayHandler::taskDrawLoveScreen, "Draw Love Screen and sense touches on it", 1200000, NULL, 1, TaskHandlers::drawLoveScreen);
                th.terminateAllTasks(th.drawLoveScreen);
                break;
            case Message:
                drawMessageScreen();
                xTaskCreate(DisplayHandler::taskDrawMessageScreen, "Draw Message screen and sense touches on it", 1200000, NULL, 1, TaskHandlers::drawMessageScreen);
                th.terminateAllTasks(th.drawMessageScreen);
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
        void onErrorThrown(wchar_t *errorMessage)
        {
            Box background = Box(90, 50, 300, 160, BLACK, gfx);
            Box homeButton = Box((background.x2 - background.x1) / 2 + 90 - 25, background.y2 - 50 - 20, 50, 50, YELLOW, gfx);
            background.drawBox();
            gfx->fillRect(90, 50, 300, 160, BLACK);
            gfx->drawRect(90, 50, 300, 160, RED);

            gfx->setCursor(100, 55);
            displayComplexText(segmentText(errorMessage, 8));
            drawJpeg("/alert/homeButtonSmall.jpg", (background.x2 - background.x1) / 2 + 90 - 25, background.y2 - 50 - 20);
            while (true)
            {
                if (senseObject(homeButton))
                {
                    drawHomeScreen();
                    return;
                }
            }
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
                return true;
            }
            return false;
        }
        bool senseObject(Box box)
        {
            TouchPoint tp = senseTouch();
            // Sense wether the tocuh happened within the coordinates
            if (tp.x > box.x1 && tp.x < box.x2 && tp.y > box.y1 && tp.y < box.y2)
            {
                return true;
            }
            return false;
        }
    };
}
#endif