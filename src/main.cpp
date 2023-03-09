#include <Arduino.h>
#include "SPI.h"
#include "Networking.cpp"
#include "DisplayHandling.cpp"
#include "DataHandling.cpp"
#include "SPIFFS.h"
#include "FS.h"
#define FS_NO_GLOBALS

//using namespace Networking;
using namespace DisplayHandling;
using namespace DataHandling;
using namespace Networking;

//Network network = Network();
Network network = Network();
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
  //network.donwloadImage("https://onlinejpgtools.com/images/examples-onlinejpgtools/coffee-resized.jpg");

  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //displayHandler.gfx->fillScreen(random(0xFFFF));
  //jpegHandler.drawJpeg("/downloads/testt.jpg", 0,0);
  //displayHandler.downloadAndDisplayImage("https://onlinejpgtools.com/images/examples-onlinejpgtools/coffee-resized.jpg", 20,20);
  network.downloadImage("https://static.wikia.nocookie.net/gloomverse/images/3/3f/Random.jpg/revision/latest?cb=20190516041403");
  jpegHandler.drawJpeg("/image.jpg", 20, 20);
  delay(2000);
}
