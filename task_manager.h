// task_manager.h
#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "task.h"
#include <string>

void loadTasks(const std::string& username);
void saveTasks(const std::string& username);
void addTask();
void viewTasksPaginated();
void completeTask();
void deleteTaskById();
void updateTaskById();
void searchTask();

#endif
