#pragma once
#include "Arduino.h"

namespace TaskHandler
{
    struct TaskHandlers {
        static TaskHandle_t* drawHomeScreen;
        static TaskHandle_t* drawMessageScreen;
        static TaskHandle_t* drawLoveScreen;
        static TaskHandle_t* drawHistoryScreen;
        static TaskHandle_t* ledDriver;

        static TaskHandle_t* allTasks[5];

        static void terminateAllTasks(TaskHandle_t* except);
    };
} // namespace TaskHandler