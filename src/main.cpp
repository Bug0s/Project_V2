#include <Arduino.h>
#include "SPI.h"
#include "Networking.cpp"
#include "DisplayHandling.cpp"
#include "DataHandling.cpp"
#include "SPIFFS.h"
#include "FS.h"
#define FS_NO_GLOBALS

using namespace Networking;
using namespace DisplayHandling;
using namespace DataHandling;

//Network network = Network();
Networking::Network network = Networking::Network();
DisplayHandler displayHandler = DisplayHandler();
JpegHandler jpegHandler = JpegHandler(displayHandler.gfx);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  network.connectToWiFi("Macko", "Maczkonokia01");
  displayHandler.initTFT();
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }
  network.donwloadImage("https://onlinejpgtools.com/images/examples-onlinejpgtools/coffee-resized.jpg");

  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  displayHandler.gfx->fillScreen(random(0xFFFF));
  jpegHandler.drawJpeg("/downloads/testt.jpg", 0,0);
  delay(2000);
}
