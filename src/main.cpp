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
JpegHandler jpegHandler = JpegHandler();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //network.connectToWiFi("Macko", "Maczkonokia01");
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }
  displayHandler.initTFT();
  
  //network.donwloadImage("https://onlinejpgtools.com/images/examples-onlinejpgtools/coffee-resized.jpg");

  
  
}

void loop() {
    TouchPoint tp = displayHandler.senseTouch();
    if (tp.isValid && false) {
      Serial.print("X: ");
      Serial.print (tp.x);
      Serial.print(" Y: ");
      Serial.print(tp.y);
      Serial.println(" ");
    }
    if (displayHandler.senseObject(35,135,40,140)) {
      displayHandler.makeTransition(Screens(Downloading));
    }

}
