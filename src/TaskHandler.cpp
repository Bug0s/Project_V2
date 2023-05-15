#pragma once
#include "Arduino.h"

namespace TaskHandler
{
    struct Task {
        /// @brief Thze task's name
        String name;

        /// @brief The TASK
        void(* function)();

        /// @brief if not runable it should be deleted from the DispatchQueue
        bool runable;

        int taskLocation = -1;

        void stopTask() {
            this->runable = false;
            this->function = NULL;
        }

        
        
    };
    class TaskHandler {
    private:
        static TaskHandler* instance;
        
        int taskCount = 0;
        TaskHandler() {}
    public:
        Task tasks[10];
        
        static TaskHandler* shared() {
            if (instance == nullptr) {
                instance = new TaskHandler();
            }
            return instance;
        }

        void addTask(Task task) {
            tasks[taskCount] = task;
            tasks[taskCount].taskLocation = taskCount++;
        }
        bool removeTask(String name) {
            int deletableTaskCount;
            for(int i = 0; i<= taskCount; i++) {
                if (tasks[i].name == name) {
                    deletableTaskCount = tasks[i].taskLocation;
                    for (int i = deletableTaskCount; i < taskCount; i++) {
                        tasks[i] = tasks[i + 1];
                    }
                    break;
                }
            }
            if (deletableTaskCount == NULL) return false; else return true;
        }


        

    };
} // namespace TaskHandler
