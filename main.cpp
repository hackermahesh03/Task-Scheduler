// main.cpp
#include <iostream>
#include <string>
#include "task_manager.h"
#include "user_manager.h"
using namespace std;

int main() {
    // 1) Get username with getline
    string username = getUsername();

    // 2) Load tasks
    loadTasks(username);

    while (true) {
        cout << "\n===== Task Scheduler =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Complete Top-Priority Task\n";
        cout << "4. Delete Task by ID\n";
        cout << "5. Update Task by ID\n";
        cout << "6. Search Task\n";
        cout << "7. Save & Exit\n";
        cout << "Enter your choice (1-7): ";

        // Read the whole line
        string line;
        if (!getline(cin, line)) 
            break;  // EOF

        int choice;
        try {
            choice = stoi(line);
        } catch (...) {
            cout << "Invalid input. Please enter 1-7.\n";
            continue;
        }

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasksPaginated(); break;
            case 3: completeTask(); break;
            case 4: deleteTaskById(); break;
            case 5: updateTaskById(); break;
            case 6: searchTask(); break;
            case 7:
                saveTasks(username);
                cout << "Tasks saved. Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please select 1-7.\n";
        }
    }

    return 0;
}
