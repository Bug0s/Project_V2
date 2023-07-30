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
#include "LedDriver.cpp"
#include "vector"

using namespace DataHandling;
using namespace Networking;
using namespace TaskHandler;
using namespace LedDriver;

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
    struct DrawSpecialCharacters
    {
    private:
        Arduino_GFX *gfx;
        int16_t cursorX()
        {
            return gfx->getCursorX();
        }
        int16_t cursorY()
        {
            return gfx->getCursorY();
        }

    public:
        DrawSpecialCharacters(Arduino_GFX *gfx)
        {
            this->gfx = gfx;
        }
        void draw_aLong()
        {
            gfx->drawLine(cursorX() + 3, cursorY() - 0, cursorX() + 3 + 2, cursorY() - 0 - 2, WHITE);
            gfx->drawLine(cursorX() + 4, cursorY() - 0, cursorX() + 4 + 2, cursorY() - 0 - 2, WHITE);
            gfx->print("a");
        }
        void draw_eLong()
        {
            gfx->drawLine(cursorX() + 4, cursorY() - 0, cursorX() + 4 + 2, cursorY() - 0 - 2, WHITE);
            gfx->drawLine(cursorX() + 5, cursorY() - 0, cursorX() + 5 + 2, cursorY() - 0 - 2, WHITE);
            gfx->print("e");
        }
        void draw_iLong()
        {
            gfx->drawLine(cursorX() + 4, cursorY() - 0, cursorX() + 4 + 2, cursorY() - 0 - 2, WHITE);
            gfx->drawLine(cursorX() + 5, cursorY() - 0, cursorX() + 5 + 2, cursorY() - 0 - 2, WHITE);
            gfx->print("i");
        }

        void draw_oLong()
        {
            gfx->drawLine(cursorX() + 4, cursorY() - 0, cursorX() + 4 + 2, cursorY() - 0 - 2, WHITE);
            gfx->drawLine(cursorX() + 5, cursorY() - 0, cursorX() + 5 + 2, cursorY() - 0 - 2, WHITE);
            gfx->print("o");
        }

        void draw_oDoubleShort()
        {
            gfx->drawPixel(cursorX() + 3, cursorY() + 1, WHITE);
            gfx->drawPixel(cursorX() + 3, cursorY() - 0, WHITE);
            gfx->drawPixel(cursorX() + 2, cursorY() + 1, WHITE);
            gfx->drawPixel(cursorX() + 2, cursorY() - 0, WHITE);

            gfx->drawPixel(cursorX() + 7, cursorY() + 1, WHITE);
            gfx->drawPixel(cursorX() + 7, cursorY() - 0, WHITE);
            gfx->drawPixel(cursorX() + 6, cursorY() + 1, WHITE);
            gfx->drawPixel(cursorX() + 6, cursorY() - 0, WHITE);

            gfx->print("o");
        }

        void draw_oDoubleLong()
        {
            gfx->drawLine(cursorX() + 3, cursorY() - 0, cursorX() + 3 + 2, cursorY() - 0 - 2, WHITE);
            gfx->drawLine(cursorX() + 4, cursorY() - 0, cursorX() + 4 + 2, cursorY() - 0 - 2, WHITE);

            gfx->drawLine(cursorX() + 6, cursorY() - 0, cursorX() + 6 + 2, cursorY() - 0 - 2, WHITE);
            gfx->drawLine(cursorX() + 7, cursorY() - 0, cursorX() + 7 + 2, cursorY() - 0 - 2, WHITE);

            gfx->print("o");
        }

        void draw_uLong()
        {
            gfx->drawLine(cursorX() + 4, cursorY() - 0, cursorX() + 4 + 2, cursorY() - 0 - 2, WHITE);
            gfx->drawLine(cursorX() + 5, cursorY() - 0, cursorX() + 5 + 2, cursorY() - 0 - 2, WHITE);
            gfx->print("u");
        }

        void draw_uDoubleShort()
        {
            gfx->drawPixel(cursorX() + 3, cursorY() + 1, WHITE);
            gfx->drawPixel(cursorX() + 3, cursorY() - 0, WHITE);
            gfx->drawPixel(cursorX() + 2, cursorY() + 1, WHITE);
            gfx->drawPixel(cursorX() + 2, cursorY() - 0, WHITE);

            gfx->drawPixel(cursorX() + 7, cursorY() + 1, WHITE);
            gfx->drawPixel(cursorX() + 7, cursorY() - 0, WHITE);
            gfx->drawPixel(cursorX() + 6, cursorY() + 1, WHITE);
            gfx->drawPixel(cursorX() + 6, cursorY() - 0, WHITE);
            gfx->print("u");
        }
        
        void draw_uDoubleLong()
        {
            gfx->drawLine(cursorX() + 2, cursorY() - 0, cursorX() + 2 + 2, cursorY() - 0 - 2, WHITE);
            gfx->drawLine(cursorX() + 3, cursorY() - 0, cursorX() + 3 + 2, cursorY() - 0 - 2, WHITE);

            gfx->drawLine(cursorX() + 5, cursorY() - 0, cursorX() + 5 + 2, cursorY() - 0 - 2, WHITE);
            gfx->drawLine(cursorX() + 6, cursorY() - 0, cursorX() + 6 + 2, cursorY() - 0 - 2, WHITE);

            gfx->print("u");
        }

        void draw_ALong()
        {
            gfx->drawLine(cursorX() + 4, cursorY() - 0 - 3, cursorX() + 4 + 2, cursorY() - 0 - 2 - 3, WHITE);
            gfx->drawLine(cursorX() + 5, cursorY() - 0 - 3, cursorX() + 5 + 2, cursorY() - 0 - 2 - 3, WHITE);
            gfx->print("A");
        }

        void draw_ELong()
        {
            gfx->drawLine(cursorX() + 3, cursorY() - 0 - 3, cursorX() + 3 + 2, cursorY() - 0 - 2 - 3, WHITE);
            gfx->drawLine(cursorX() + 4, cursorY() - 0 - 3, cursorX() + 4 + 2, cursorY() - 0 - 2 - 3, WHITE);
            gfx->print("E");
        }

        void draw_ILong()
        {
            gfx->drawLine(cursorX() + 4, cursorY() - 0 - 2, cursorX() + 4 + 2, cursorY() - 0 - 2 - 2, WHITE);
            gfx->drawLine(cursorX() + 5, cursorY() - 0 - 2, cursorX() + 5 + 2, cursorY() - 0 - 2 - 2, WHITE);
            gfx->print("I");
        }

        void draw_OLong()
        {
            gfx->drawLine(cursorX() + 4, cursorY() - 0 - 2, cursorX() + 4 + 2, cursorY() - 0 - 2 - 2, WHITE);
            gfx->drawLine(cursorX() + 5, cursorY() - 0 - 2, cursorX() + 5 + 2, cursorY() - 0 - 2 - 2, WHITE);
            gfx->print("O");
        }

        void draw_ODoubleShort()
        {
            gfx->drawPixel(cursorX() + 3, cursorY() - 2, WHITE);
            gfx->drawPixel(cursorX() + 3, cursorY() - 3, WHITE);
            gfx->drawPixel(cursorX() + 2, cursorY() - 3, WHITE);
            gfx->drawPixel(cursorX() + 2, cursorY() - 2, WHITE);

            gfx->drawPixel(cursorX() + 7, cursorY() - 2, WHITE);
            gfx->drawPixel(cursorX() + 7, cursorY() - 3, WHITE);
            gfx->drawPixel(cursorX() + 6, cursorY() - 3, WHITE);
            gfx->drawPixel(cursorX() + 6, cursorY() - 2, WHITE);
            gfx->print("O");
        }

        void draw_ODoubleLong()
        {
            gfx->drawLine(cursorX() + 3, cursorY() - 0 - 2, cursorX() + 3 + 2, cursorY() - 0 - 2 - 2, WHITE);
            gfx->drawLine(cursorX() + 4, cursorY() - 0 - 2, cursorX() + 4 + 2, cursorY() - 0 - 2 - 2, WHITE);

            gfx->drawLine(cursorX() + 6, cursorY() - 0 - 2, cursorX() + 6 + 2, cursorY() - 0 - 2 - 2, WHITE);
            gfx->drawLine(cursorX() + 7, cursorY() - 0 - 2, cursorX() + 7 + 2, cursorY() - 0 - 2 - 2, WHITE);

            gfx->print("O");
        }

        void draw_ULong()
        {
            gfx->drawLine(cursorX() + 4, cursorY() - 0 - 2, cursorX() + 4 + 2, cursorY() - 0 - 2 - 2, WHITE);
            gfx->drawLine(cursorX() + 5, cursorY() - 0 - 2, cursorX() + 5 + 2, cursorY() - 0 - 2 - 2, WHITE);
            gfx->print("U");
        }

        void draw_UDoubleShort()
        {
            gfx->drawPixel(cursorX() + 3, cursorY() - 2, WHITE);
            gfx->drawPixel(cursorX() + 3, cursorY() - 3, WHITE);
            gfx->drawPixel(cursorX() + 2, cursorY() - 2, WHITE);
            gfx->drawPixel(cursorX() + 2, cursorY() - 3, WHITE);

            gfx->drawPixel(cursorX() + 7, cursorY() - 2, WHITE);
            gfx->drawPixel(cursorX() + 7, cursorY() - 3, WHITE);
            gfx->drawPixel(cursorX() + 6, cursorY() - 2, WHITE);
            gfx->drawPixel(cursorX() + 6, cursorY() - 3, WHITE);
            gfx->print("U");
        }

        void draw_UDoubleLong()
        {
            gfx->drawLine(cursorX() + 2, cursorY() - 0 - 2, cursorX() + 2 + 2, cursorY() - 0 - 2 - 2, WHITE);
            gfx->drawLine(cursorX() + 3, cursorY() - 0 - 2, cursorX() + 3 + 2, cursorY() - 0 - 2 - 2, WHITE);

            gfx->drawLine(cursorX() + 5, cursorY() - 0 - 2, cursorX() + 5 + 2, cursorY() - 0 - 2 - 2, WHITE);
            gfx->drawLine(cursorX() + 6, cursorY() - 0 - 2, cursorX() + 6 + 2, cursorY() - 0 - 2 - 2, WHITE);

            gfx->print("U");
        }
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

        String segmentText(String text, int lineStart)
        {
            int textLength = text.length();
            int numLineBreaks = 0;

            // Count the number of line breaks in the text
            for (int i = 0; i < textLength; i++)
            {
                if (text[i] == L'\n')
                {
                    numLineBreaks++;
                }
            }

            // Calculate the new text length with additional line breaks and whitespaces
            int newTextLength = textLength + (numLineBreaks * 2 + 1) * lineStart;

            // Create a new wstring to store the segmented text
            String segmentedText;
            segmentedText.reserve(newTextLength);

            for (int i = 0; i < textLength; i++)
            {
                segmentedText += text[i];
                if (text[i] == L'\n')
                {
                    // Add the specified number of whitespaces after a line break
                    for (int k = 0; k < lineStart; k++)
                    {
                        segmentedText += L' ';
                    }
                    segmentedText += L'\n'; // Add an additional line break
                    for (int k = 0; k < lineStart; k++)
                    {
                        segmentedText += L' ';
                    }
                }
            }

            return segmentedText;
        }

        void displayDecodedFormattedText(String text)
        {
            int len = text.length();
            for (int i = 0; i < len; i++)
            {
                if (text.charAt(i) == '%' && i + 1 < len && isdigit(text.charAt(i + 1)))
                {
                    int num = 0;
                    int j = i + 1;
                    i += 2;
                    while (j < len && isdigit(text.charAt(j)))
                    {
                        num = num * 10 + (text.charAt(j) - '0');
                        j++;
                    }
                    switch (num)
                    {
                    case 10:
                        drawSpecChar.draw_aLong();
                        break;

                    case 11:
                        drawSpecChar.draw_eLong();
                        break;

                    case 12:
                        drawSpecChar.draw_iLong();
                        break;

                    case 13:
                        drawSpecChar.draw_oLong();
                        break;

                    case 14:
                        drawSpecChar.draw_oDoubleShort();
                        break;

                    case 15:
                        drawSpecChar.draw_oDoubleLong();
                        break;

                    case 16:
                        drawSpecChar.draw_uLong();
                        break;

                    case 17:
                        drawSpecChar.draw_uDoubleShort();
                        break;

                    case 18:
                        drawSpecChar.draw_uDoubleLong();
                        break;

                    // UPPERCASED LETTERS:---------------------------
                    case 20:
                        drawSpecChar.draw_ALong();
                        break;

                    case 21:
                        drawSpecChar.draw_ELong();
                        break;

                    case 22:
                        drawSpecChar.draw_ILong();
                        break;

                    case 23:
                        drawSpecChar.draw_OLong();
                        break;

                    case 24:
                        drawSpecChar.draw_ODoubleShort();
                        break;

                    case 25:
                        drawSpecChar.draw_ODoubleLong();
                        break;

                    case 26:
                        drawSpecChar.draw_ULong();
                        break;

                    case 27:
                        drawSpecChar.draw_UDoubleShort();
                        break;

                    case 28:
                        drawSpecChar.draw_UDoubleLong();
                        break;

                    default:
                        throw std::runtime_error("Unidentified char at L394");
                        break;
                    }
                    continue;
                }
                else
                {
                    gfx->print(text.charAt(i));
                    continue;
                }
            }
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
                        drawSpecChar.draw_aLong();
                    }

                    else if (currentChar == *L"é")
                    {
                        drawSpecChar.draw_eLong();
                    }
                    else if (currentChar == *L"í")
                    {
                        drawSpecChar.draw_iLong();
                    }

                    else if (currentChar == *L"ó")
                    {
                        drawSpecChar.draw_oLong();
                    }
                    else if (currentChar == *L"ö")
                    {
                        drawSpecChar.draw_oDoubleShort();
                    }
                    else if (currentChar == *L"ő")
                    {
                        drawSpecChar.draw_oDoubleLong();
                    }
                    else if (currentChar == *L"ú")
                    {
                        drawSpecChar.draw_uLong();
                    }

                    else if (currentChar == *L"ü")
                    {
                        drawSpecChar.draw_uDoubleShort();
                    }
                    else if (currentChar == *L"ű")
                    {
                        drawSpecChar.draw_uDoubleLong();
                    }
                    else if (currentChar == *L"Á")
                    {
                        drawSpecChar.draw_ALong();
                    }

                    else if (currentChar == *L"É")
                    {
                        drawSpecChar.draw_ELong();
                    }
                    else if (currentChar == *L"Í")
                    {
                        drawSpecChar.draw_ILong();
                    }

                    else if (currentChar == *L"Ó")
                    {
                        drawSpecChar.draw_OLong();
                    }
                    else if (currentChar == *L"Ö")
                    {
                        drawSpecChar.draw_ODoubleShort();
                    }
                    else if (currentChar == *L"Ő")
                    {
                        drawSpecChar.draw_ODoubleLong();
                    }
                    else if (currentChar == *L"Ú")
                    {
                        drawSpecChar.draw_ULong();
                    }

                    else if (currentChar == *L"Ü")
                    {
                        drawSpecChar.draw_uDoubleShort();
                    }
                    else if (currentChar == *L"Ű")
                    {
                        drawSpecChar.draw_UDoubleLong();
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
        DrawSpecialCharacters drawSpecChar = DrawSpecialCharacters(gfx);

        // START OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // START OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // START OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // START OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // START OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // START OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // START OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // START OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // START OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // START OF OPERATIONHANDLING -------------------------------------------------------------------------------
        enum ChestState
        {
            closed,
            open
        };
        ChestState isChestClosed()
        {
            int doorPin = 13;
            delay(500);
            if (digitalRead(doorPin))
            {
                return closed;
            }
            else
            {
                return open;
            }
        }

        ChestState lastKnownChestState = ChestState::open;
        bool wiFiGotConnected = true;

        void checkWifi()
        {
            if (WiFi.status() != WL_CONNECTED)
            {
                wiFiGotConnected = false;
                WiFi.begin("Macko", "Maczkonokia01");
                this->onTemporaryError(L"Elment a WiFi jel.\n\nVárj egy pillanatot\namíg újra csatlakozom...");
                delay(2000);
                while (WiFi.status() != WL_CONNECTED)
                {
                }
                makeTransition(Home);
                return;
            }
        }

        void lookForNewMessages()
        {
            // Get the queue every 5 second
            const unsigned long getQueueInterval = 5000;
            // Store when was the last queue got.
            unsigned long lastQueueGot = 0;
            int queueCount = 0;
            int sectionNum = 1;
            LedDriverClass ld = LedDriverClass();
            while (true)
            {
                unsigned long currentTime = millis();
                if (currentTime - lastQueueGot >= getQueueInterval)
                {
                    checkWifi();
                    queueCount = network.getQueueStatus();
                    lastQueueGot = millis();
                }

                // If the chest got opened
                if (isChestClosed() == open)
                {
                    return;
                }
                // If there is an unread message
                if (queueCount > 0)
                {
                    while (true)
                    {
                        checkWifi();

                        // Led villogtatás
                        ld.ledStart(sectionNum++);
                        if (sectionNum == 31)
                        {
                            sectionNum = 1;
                        }

                        if (isChestClosed() == open)
                        {
                            return;
                        }
                    }
                }
            }
        }

        void onChestClosed()
        {
            this->setBackgroundLed(0);
            // The program execution continues when found new messages!
            lookForNewMessages();
            this->makeTransition(Home);
            this->setBackgroundLed(100);
        }

    public:
        void watchAlways(bool withCheckWifi = true)
        {
            if (this->isChestClosed() == closed)
            {
                onChestClosed();
            }

            if (withCheckWifi)
                checkWifi();
        }

        // END OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // END OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // END OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // END OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // END OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // END OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // END OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // END OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // END OF OPERATIONHANDLING -------------------------------------------------------------------------------
        // END OF OPERATIONHANDLING -------------------------------------------------------------------------------

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
            // vTaskStartScheduler();
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
            messageCount = -1;
            try
            {
                messageCount = network.getQueueStatus();
            }
            catch (...)
            {
                onErrorThrown(L"Problem on getting\nthe queue Status.");
            }
            if (messageCount == 0)
            {
                drawJpeg("/buttonIcons/mailOff.jpg", messageButton.x1, messageButton.y1);
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
                watchAlways();

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
                    // makeTransition(Screens(History));
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

            displayDecodedFormattedText(queueItem.message);

            try
            {
                network.lastPostDisplayed();
            }
            catch (...)
            {
                onErrorThrown(L"Problem on contacting\nthe server. (L717)");
            }
            while (true)
            {
                watchAlways();

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
        // ONLY FOR TYPE 2 loveTextToDisplay!!
        wchar_t *stringToWchar(const String &str)
        {
            // Convert String to std::string
            std::string stdStr = str.c_str();

            // Allocate memory for wchar_t* and convert std::string to wide string
            size_t bufferSize = stdStr.length() + 1; // +1 for null-terminator
            wchar_t *wcharStr = new wchar_t[bufferSize];
            mbstowcs(wcharStr, stdStr.c_str(), bufferSize);

            return wcharStr;
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
            try
            {
                LoveTextData loveData = network.getLoveText();
                displayDecodedFormattedText(segmentText(loveData.serverContent, 2));

            
            }
            catch (...)
            {
                onErrorThrown(L"Error on getting\nthe love data.");
            }
            while (true)
            {
                watchAlways(false);
                if (senseObject(homeButton))
                {
                    makeTransition(Screens(Home));
                    break;
                }
            }
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
                // xTaskCreate(DisplayHandler::taskDrawHomeScreen, "Draw Home screen and sense touches on it", 1200000, NULL, 1, TaskHandlers::drawHomeScreen);
                // th.terminateAllTasks(th.drawHomeScreen);
                break;
            case History:
                drawHistoryScreen();
                break;
            case Love:
                drawLoveScreen();
                // xTaskCreate(DisplayHandler::taskDrawLoveScreen, "Draw Love Screen and sense touches on it", 1200000, NULL, 1, TaskHandlers::drawLoveScreen);
                // th.terminateAllTasks(th.drawLoveScreen);
                break;
            case Message:
                drawMessageScreen();
                // xTaskCreate(DisplayHandler::taskDrawMessageScreen, "Draw Message screen and sense touches on it", 1200000, NULL, 1, TaskHandlers::drawMessageScreen);
                // th.terminateAllTasks(th.drawMessageScreen);
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
                watchAlways(false);
                if (senseObject(homeButton))
                {
                    drawHomeScreen();
                    return;
                }
            }
        }
        void onTemporaryError(wchar_t *errorMessage)
        {
            Box background = Box(90, 50, 300, 160, BLACK, gfx);
            Box homeButton = Box((background.x2 - background.x1) / 2 + 90 - 25, background.y2 - 50 - 20, 50, 50, YELLOW, gfx);
            background.drawBox();
            gfx->fillRect(90, 50, 300, 160, BLACK);
            gfx->drawRect(90, 50, 300, 160, RED);

            gfx->setCursor(100, 55);
            displayComplexText(segmentText(errorMessage, 8));
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