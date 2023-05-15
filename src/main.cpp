#include <Arduino.h>
#include "SPI.h"
#include "Networking.cpp"
#include "DisplayHandling.cpp"
#include "DataHandling.cpp"
#include "SPIFFS.h"
#include "FS.h"
#include "TaskHandler.cpp"
#define FS_NO_GLOBALS

//using namespace Networking;
using namespace DisplayHandling;
using namespace DataHandling;
using namespace Networking;
using namespace TaskHandler;

//Network network = Network();
Network network = Network();
DisplayHandler displayHandler = DisplayHandler();
JpegHandler jpegHandler = JpegHandler();

//Background thread init
void backGroundInit(void* param) {
  network.connectToWiFi("Macko", "Maczkonokia01");
  vTaskDelete(NULL);
}

void test() {
   Serial.println("test TASK");
   delay(500);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //network.connectToWiFi("Macko", "Maczkonokia01");
  xTaskCreatePinnedToCore(&backGroundInit, "WiFiConnect", 3500, NULL, 1, NULL, 1);
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }
  displayHandler.initTFT();

  //TaskHandler::TaskHandler* taskHandler = TaskHandler::TaskHandler::shared();
  String testName = TaskHandler::TaskHandler::shared()->tasks[0].name;
  //Task testTask = Task("test", test, true);


  
  //network.donwloadImage("https://onlinejpgtools.com/images/examples-onlinejpgtools/coffee-resized.jpg");


  
  
}

void loop() {
    //testComment

}
