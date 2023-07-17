#pragma once
#include "TaskHandler.h"


TaskHandler::TaskHandlers th;
TaskHandle_t* TaskHandler::TaskHandlers::drawHomeScreen = nullptr;
TaskHandle_t* TaskHandler::TaskHandlers::drawMessageScreen = nullptr;
TaskHandle_t* TaskHandler::TaskHandlers::drawLoveScreen = nullptr;
TaskHandle_t* TaskHandler::TaskHandlers::drawHistoryScreen = nullptr;
TaskHandle_t* TaskHandler::TaskHandlers::ledDriver = nullptr;


TaskHandle_t* TaskHandler::TaskHandlers::allTasks[] = {
    drawHomeScreen,
    drawMessageScreen,
    drawLoveScreen,
    drawHistoryScreen,
    ledDriver
};

void TaskHandler::TaskHandlers::terminateAllTasks(TaskHandle_t* except)
{
    for (int i = 0; i < sizeof(allTasks) / sizeof(allTasks[0]); i++) {
        if (allTasks[i] == except) continue;
        if (allTasks[i] != nullptr) {
            vTaskDelete(allTasks[i]);
            allTasks[i] = nullptr;
        }
    }
}
