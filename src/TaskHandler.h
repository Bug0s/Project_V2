#pragma once
#include "Arduino.h"

namespace TaskHandler
{
    struct TaskHandlers {
        static TaskHandle_t* drawHomeScreen;
        static TaskHandle_t* drawMessageScreen;
        static TaskHandle_t* drawLoveScreen;
        static TaskHandle_t* drawHistoryScreen;
    };
} // namespace TaskHandler