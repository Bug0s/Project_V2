#pragma once
#include "Arduino.h"

namespace TaskHandler
{
    struct TaskHandlers {
        static TaskHandle_t* drawHomeScreen;
        static TaskHandle_t* drawMessageScreen;
        static TaskHandle_t* drawLoveScreen;
        static TaskHandle_t* drawHistoryScreen;

        static TaskHandle_t* allTasks[4];

        static void terminateAllTasks();
    };
} // namespace TaskHandler