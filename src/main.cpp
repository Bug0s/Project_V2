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

using namespace DisplayHandling;
using namespace DataHandling;
using namespace Networking;
using namespace TaskHandler;

Network network = Network();
DisplayHandler displayHandler = DisplayHandler();
JpegHandler jpegHandler = JpegHandler();

/*
  TODO in future versions:
    -try to connect to multiple wifis.
    -dont check for wifi all the time, its enough to check it every 5-10 seconds
    -status bar server check unreliable
    -history function
    -react to messages
*/
void setup()
{
  Serial.begin(9600);

  if (!SPIFFS.begin())
  {
    Serial.println("SPIFFS initialisation failed!");
    while (1)
      yield();
  }
  LedDriverClass().ledSetup();
  displayHandler.initTFT();
}

void loop()
{
}
