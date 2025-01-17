#ifndef DATAHANDLING_CPP
#define DATAHANDLING_CPP
#include <Arduino.h>
#include <JPEGDecoder.h>
#include <SPIFFS.h>
#include <FS.h>
#include <Arduino_GFX_Library.h>
#include "Networking.cpp"
#include "TaskHandler.h"
#include "WiFi.h"



#define minimum(a, b) (((a) < (b)) ? (a) : (b))
namespace DataHandling
{
    typedef struct {
        int32_t width;
        int32_t height;
    } ImageSize;

    class JpegHandler
    {
    public:
        static bool decodeArray(const uint8_t *jpgArr, size_t size)
        {
            Serial.println("starting to decode");
            Serial.println(sizeof(*jpgArr));
            bool decoded = JpegDec.decodeArray(jpgArr, size);
            return (decoded) ? true : false;
        }

        static ImageSize jpegRender(int xpos, int ypos, Arduino_GFX *tft)
        {

            // retrieve infomration about the image
            uint16_t *pImg;
            int16_t mcu_w = JpegDec.MCUWidth;
            int16_t mcu_h = JpegDec.MCUHeight;
            int32_t max_x = JpegDec.width;
            int32_t max_y = JpegDec.height;

            // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
            // Typically these MCUs are 16x16 pixel blocks
            // Determine the width and height of the right and bottom edge image blocks
            int32_t min_w = minimum(mcu_w, max_x % mcu_w);
            int32_t min_h = minimum(mcu_h, max_y % mcu_h);

            // save the current image block size
            int32_t win_w = mcu_w;
            int32_t win_h = mcu_h;

            // record the current time so we can measure how long it takes to draw an image
            uint32_t drawTime = millis();

            // save the coordinate of the right and bottom edges to assist image cropping
            // to the screen size
            max_x += xpos;
            max_y += ypos;

            // read each MCU block until there are no more
            while (JpegDec.readSwappedBytes())
            { // Swapped byte order read

                // save a pointer to the image block
                pImg = JpegDec.pImage;

                // calculate where the image block should be drawn on the screen
                int mcu_x = JpegDec.MCUx * mcu_w + xpos; // Calculate coordinates of top left corner of current MCU
                int mcu_y = JpegDec.MCUy * mcu_h + ypos;

                // check if the image block size needs to be changed for the right edge
                if (mcu_x + mcu_w <= max_x)
                    win_w = mcu_w;
                else
                    win_w = min_w;

                // check if the image block size needs to be changed for the bottom edge
                if (mcu_y + mcu_h <= max_y)
                    win_h = mcu_h;
                else
                    win_h = min_h;

                // copy pixels into a contiguous block
                if (win_w != mcu_w)
                {
                    for (int h = 1; h < win_h - 1; h++)
                    {
                        memcpy(pImg + h * win_w, pImg + (h + 1) * mcu_w, win_w << 1);
                    }
                }

                // draw image MCU block only if it will fit on the screen
                if (mcu_x < tft->width() && mcu_y < tft->height())
                {
                    // Now push the image block to the screen
                    tft->draw16bitBeRGBBitmap(mcu_x, mcu_y, pImg, win_w, win_h);
                }

                else if ((mcu_y + win_h) >= tft->height())
                    JpegDec.abort();
            }
            ImageSize imageSize;
            imageSize.width = JpegDec.width;
            imageSize.height = JpegDec.height;

            return imageSize;

        }
        
    };

    class ProcessHandler {
        private:
        static bool checkNetworkStatus() {
            return WiFi.status() == WL_CONNECTED;
        }
        static bool checkServerStatus() {
            HTTPClient http;


            http.begin("http://80.99.154.229:5000/success");
            int httpCode = http.GET();
            http.end();
            if (httpCode == 200) return true;  else  return false;
        }

        public:
        typedef struct 
        {
            bool networkCorrect;
            bool serverCorrect;
        } ConnectionStatusCheck;
        
        static ConnectionStatusCheck checkConnectionStatuses() {
            bool networkStatus = ProcessHandler::checkNetworkStatus();
            bool serverStatus = ProcessHandler::checkServerStatus();
            ConnectionStatusCheck statusCheck;
            statusCheck.networkCorrect = networkStatus;
            statusCheck.serverCorrect = serverStatus;

            return statusCheck;
        }

        
    };
}
#endif