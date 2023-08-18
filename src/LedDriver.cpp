#pragma once
#include <Arduino.h>

namespace LedDriver
{
  class LedDriverClass
  {
    public:
    LedDriverClass() {}
    const int Q1 = 0; // PNP transistor base pin (ROW1)
    const int Q2 = 2; // PNP transistor base pin (ROW2)
    const int Q3 = 15; // PNP transistor base pin (ROW3)
    const int Q4 = 26; // PNP transistor base pin (ROW4)
    const int Q5 = 4; // NPN transistor base pin (COL1)
    const int Q6 = 16; // NPN transistor base pin (COL2)
    const int Q7 = 17; // NPN transistor base pin (COL3)
    const int Q8 = 5; // NPN transistor base pin (COL4)

    int onTime = 50; // cycle time

    void LED1(int dly)
    {
      digitalWrite(Q1, LOW);
      digitalWrite(Q5, HIGH);
      delay(dly);
      digitalWrite(Q1, HIGH);
      digitalWrite(Q5, LOW);
    }

    void LED2(int dly)
    {
      digitalWrite(Q1, LOW);
      digitalWrite(Q6, HIGH);
      delay(dly);
      digitalWrite(Q1, HIGH);
      digitalWrite(Q6, LOW);
    }

    void LED3(int dly)
    {
      digitalWrite(Q1, LOW);
      digitalWrite(Q7, HIGH);
      delay(dly);
      digitalWrite(Q1, HIGH);
      digitalWrite(Q7, LOW);
    }

    void LED4(int dly)
    {
      digitalWrite(Q1, LOW);
      digitalWrite(Q8, HIGH);
      delay(dly);
      digitalWrite(Q1, HIGH);
      digitalWrite(Q8, LOW);
    }

    void LED5(int dly)
    {
      digitalWrite(Q2, LOW);
      digitalWrite(Q5, HIGH);
      delay(dly);
      digitalWrite(Q2, HIGH);
      digitalWrite(Q5, LOW);
    }

    void LED6(int dly)
    {
      digitalWrite(Q2, LOW);
      digitalWrite(Q6, HIGH);
      delay(dly);
      digitalWrite(Q2, HIGH);
      digitalWrite(Q6, LOW);
    }

    void LED7(int dly)
    {
      digitalWrite(Q2, LOW);
      digitalWrite(Q7, HIGH);
      delay(dly);
      digitalWrite(Q2, HIGH);
      digitalWrite(Q7, LOW);
    }

    void LED8(int dly)
    {
      digitalWrite(Q2, LOW);
      digitalWrite(Q8, HIGH);
      delay(dly);
      digitalWrite(Q2, HIGH);
      digitalWrite(Q8, LOW);
    }

    void LED9(int dly)
    {
      digitalWrite(Q3, LOW);
      digitalWrite(Q5, HIGH);
      delay(dly);
      digitalWrite(Q3, HIGH);
      digitalWrite(Q5, LOW);
    }

    void LED10(int dly)
    {
      digitalWrite(Q3, LOW);
      digitalWrite(Q6, HIGH);
      delay(dly);
      digitalWrite(Q3, HIGH);
      digitalWrite(Q6, LOW);
    }

    void LED11(int dly)
    {
      digitalWrite(Q3, LOW);
      digitalWrite(Q7, HIGH);
      delay(dly);
      digitalWrite(Q3, HIGH);
      digitalWrite(Q7, LOW);
    }

    void LED12(int dly)
    {
      digitalWrite(Q3, LOW);
      digitalWrite(Q8, HIGH);
      delay(dly);
      digitalWrite(Q3, HIGH);
      digitalWrite(Q8, LOW);
    }

    void LED13(int dly)
    {
      digitalWrite(Q4, LOW);
      digitalWrite(Q5, HIGH);
      delay(dly);
      digitalWrite(Q4, HIGH);
      digitalWrite(Q5, LOW);
    }

    void LED14(int dly)
    {
      digitalWrite(Q4, LOW);
      digitalWrite(Q6, HIGH);
      delay(dly);
      digitalWrite(Q4, HIGH);
      digitalWrite(Q6, LOW);
    }

    void LED15(int dly)
    {
      digitalWrite(Q4, LOW);
      digitalWrite(Q7, HIGH);
      delay(dly);
      digitalWrite(Q4, HIGH);
      digitalWrite(Q7, LOW);
    }

    void LED16(int dly)
    {
      digitalWrite(Q4, LOW);
      digitalWrite(Q8, HIGH);
      delay(dly);
      digitalWrite(Q4, HIGH);
      digitalWrite(Q8, LOW);
    }

    void flashLED(
        unsigned long dlyTime = 100,
        bool LEDnr1 = 0, bool LEDnr2 = 0, bool LEDnr3 = 0, bool LEDnr4 = 0, bool LEDnr5 = 0, bool LEDnr6 = 0, bool LEDnr7 = 0, bool LEDnr8 = 0,
        bool LEDnr9 = 0, bool LEDnr10 = 0, bool LEDnr11 = 0, bool LEDnr12 = 0, bool LEDnr13 = 0, bool LEDnr14 = 0, bool LEDnr15 = 0, bool LEDnr16 = 0)
    {

      unsigned long stTime = millis();

      while (true)
      {

        if (millis() - stTime >= dlyTime)
        {
          break;
        }

        if (LEDnr1 == true)
        {
          LED1(0);
        }
        else
        {
          digitalWrite(Q1, HIGH);
          digitalWrite(Q5, LOW);
        }

        if (LEDnr2 == true)
        {
          LED2(0);
        }
        else
        {
          digitalWrite(Q1, HIGH);
          digitalWrite(Q6, LOW);
        }

        if (LEDnr3 == true)
        {
          LED3(0);
        }
        else
        {
          digitalWrite(Q1, HIGH);
          digitalWrite(Q7, LOW);
        }

        if (LEDnr4 == true)
        {
          LED4(0);
        }
        else
        {
          digitalWrite(Q1, HIGH);
          digitalWrite(Q8, LOW);
        }

        if (LEDnr5 == true)
        {
          LED5(0);
        }
        else
        {
          digitalWrite(Q2, HIGH);
          digitalWrite(Q5, LOW);
        }

        if (LEDnr6 == true)
        {
          LED6(0);
        }
        else
        {
          digitalWrite(Q2, HIGH);
          digitalWrite(Q6, LOW);
        }

        if (LEDnr7 == true)
        {
          LED7(0);
        }
        else
        {
          digitalWrite(Q2, HIGH);
          digitalWrite(Q7, LOW);
        }

        if (LEDnr8 == true)
        {
          LED8(0);
        }
        else
        {
          digitalWrite(Q2, HIGH);
          digitalWrite(Q8, LOW);
        }

        if (LEDnr9 == true)
        {
          LED9(0);
        }
        else
        {
          digitalWrite(Q3, HIGH);
          digitalWrite(Q5, LOW);
        }

        if (LEDnr10 == true)
        {
          LED10(0);
        }
        else
        {
          digitalWrite(Q3, HIGH);
          digitalWrite(Q6, LOW);
        }

        if (LEDnr11 == true)
        {
          LED11(0);
        }
        else
        {
          digitalWrite(Q3, HIGH);
          digitalWrite(Q7, LOW);
        }

        if (LEDnr12 == true)
        {
          LED12(0);
        }
        else
        {
          digitalWrite(Q3, HIGH);
          digitalWrite(Q8, LOW);
        }

        if (LEDnr13 == true)
        {
          LED13(0);
        }
        else
        {
          digitalWrite(Q4, HIGH);
          digitalWrite(Q5, LOW);
        }

        if (LEDnr14 == true)
        {
          LED14(0);
        }
        else
        {
          digitalWrite(Q4, HIGH);
          digitalWrite(Q6, LOW);
        }

        if (LEDnr15 == true)
        {
          LED15(0);
        }
        else
        {
          digitalWrite(Q4, HIGH);
          digitalWrite(Q7, LOW);
        }

        if (LEDnr16 == true)
        {
          LED16(0);
        }
        else
        {
          digitalWrite(Q4, HIGH);
          digitalWrite(Q8, LOW);
        }
      }

      digitalWrite(Q1, HIGH);
      digitalWrite(Q2, HIGH);
      digitalWrite(Q3, HIGH);
      digitalWrite(Q4, HIGH);
      digitalWrite(Q5, LOW);
      digitalWrite(Q6, LOW);
      digitalWrite(Q7, LOW);
      digitalWrite(Q8, LOW);
    }

    void ledSetup()
    {
      pinMode(Q1, OUTPUT);
      pinMode(Q2, OUTPUT);
      pinMode(Q3, OUTPUT);
      pinMode(Q4, OUTPUT);
      pinMode(Q5, OUTPUT);
      pinMode(Q6, OUTPUT);
      pinMode(Q7, OUTPUT);
      pinMode(Q8, OUTPUT);

      digitalWrite(Q1, HIGH);
      digitalWrite(Q2, HIGH);
      digitalWrite(Q3, HIGH);
      digitalWrite(Q4, HIGH);
      digitalWrite(Q5, LOW);
      digitalWrite(Q6, LOW);
      digitalWrite(Q7, LOW);
      digitalWrite(Q8, LOW);

      delay(1000);
    }

    void ledStart(int section)
    {
        Serial.print("inside ledStart with sectionNum: ");
        Serial.println(section);
        if (section <= 4)
        {
          delay(250);
          flashLED(onTime, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
          flashLED(onTime, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
          flashLED(onTime, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
          flashLED(onTime, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
          flashLED(onTime, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
          flashLED(onTime, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
          flashLED(onTime, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
          flashLED(onTime, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
          flashLED(onTime, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0);
          flashLED(onTime, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
          flashLED(onTime, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0);
          flashLED(onTime, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0);
          flashLED(onTime, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0);
          flashLED(onTime, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0);
          flashLED(onTime, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0);
          flashLED(onTime, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0);
          flashLED(250, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
          return;
        }
        

        if (section == 5)
        {
          for (int i = 0; i <= 4; i++) {
            delay(250);
            flashLED(onTime, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            flashLED(onTime, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            flashLED(onTime, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            flashLED(onTime, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            flashLED(onTime, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            flashLED(onTime, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0);
            flashLED(onTime, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0);
            flashLED(onTime, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0);
            flashLED(onTime, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0);
            flashLED(onTime, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0);
            flashLED(onTime, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0);
            flashLED(onTime, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0);
            flashLED(onTime, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0);
            flashLED(onTime, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1);
            flashLED(onTime, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1);
            flashLED(onTime, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
          }
          return;
        }


        if (section == 6)
        {
          for (int i = 0; i <= 8; i++) {
            flashLED(onTime, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0);
            flashLED(onTime, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0);
            flashLED(onTime, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0);
            flashLED(onTime, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0);
            flashLED(onTime, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1);
            flashLED(onTime, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1);
            flashLED(onTime, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1);
            flashLED(onTime, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1);
          }
          return;
        }

        if (section == 7)
        {
          for (int i = 0; i <= 8; i++) {
            flashLED(250, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0);
            flashLED(250, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1);
          }
          return;
        }


        if (section == 8)
        {
          for (int i = 0; i <= 8; i++) {
            flashLED(100, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
            flashLED(100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            flashLED(100, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
            flashLED(750, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
          }
          return;
        }
    }
  };
}