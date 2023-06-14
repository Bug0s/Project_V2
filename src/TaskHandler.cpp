#pragma once
#include "TaskHandler.h"


TaskHandler::TaskHandlers th;
TaskHandle_t* TaskHandler::TaskHandlers::drawHomeScreen = nullptr;
TaskHandle_t* TaskHandler::TaskHandlers::drawMessageScreen = nullptr;
TaskHandle_t* TaskHandler::TaskHandlers::drawLoveScreen = nullptr;
TaskHandle_t* TaskHandler::TaskHandlers::drawHistoryScreen = nullptr;

TaskHandle_t* TaskHandler::TaskHandlers::allTasks[] = {
    drawHomeScreen,
    drawMessageScreen,
    drawLoveScreen,
    drawHistoryScreen,
};

void TaskHandler::TaskHandlers::terminateAllTasks()
{
    for (int i = 0; i < sizeof(allTasks) / sizeof(allTasks[0]); i++) {
        if (allTasks[i] != nullptr) {
            vTaskDelete(allTasks[i]);
            allTasks[i] = nullptr;
        }
    }
}
