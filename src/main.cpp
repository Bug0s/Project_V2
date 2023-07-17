#pragma once
#include <Arduino.h>
#include "SPI.h"
#include "Networking.cpp"
#include "DisplayHandling.cpp"
#include "DataHandling.cpp"
#include "SPIFFS.h"
#include "FS.h"
#include "TaskHandler.h"
#define FS_NO_GLOBALS

// using namespace Networking;
using namespace DisplayHandling;
using namespace DataHandling;
using namespace Networking;
using namespace TaskHandler;

// Network network = Network();
Network network = Network();
DisplayHandler displayHandler = DisplayHandler();
JpegHandler jpegHandler = JpegHandler();


// Background thread init

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  network.connectToWiFi("Macko", "Maczkonokia01");
  if (!SPIFFS.begin())
  {
    Serial.println("SPIFFS initialisation failed!");
    while (1)
      yield(); // Stay here twiddling thumbs waiting
  }
  LedDriverClass().ledSetup();
  pinMode(35, INPUT);
  digitalWrite(34, HIGH);
  delay(1000);
  Serial.println("RESULT: ");
  Serial.println(digitalRead(35));
  
  
  displayHandler.initTFT();

  // network.donwloadImage("https://onlinejpgtools.com/images/examples-onlinejpgtools/coffee-resized.jpg");
}

void loop()
{
  // testComment
}
