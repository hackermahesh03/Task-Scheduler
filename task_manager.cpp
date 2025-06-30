// task_manager.cpp
#include "task_manager.h"
#include "task.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <ctime>
#include <limits>
#include <algorithm>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

// Global priority queue and ID counter
priority_queue<Task> taskQueue;
int taskId = 1;

// Get timestamp for new tasks
string getCurrentTimestamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[30];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buf);
}

// Build filename per user
string getFilename(const string& username) {
    return "tasks_" + username + ".json";
}

// Load tasks from JSON file
void loadTasks(const string& username) {
    taskQueue = priority_queue<Task>();  // clear
    string filename = getFilename(username);
    ifstream inFile(filename);
    if (!inFile) return;

    json j;
    inFile >> j;
    for (auto& item : j) {
        Task t = item.get<Task>();
        taskQueue.push(t);
        taskId = max(taskId, t.id + 1);
    }
    inFile.close();
}

// Save tasks back to JSON file
void saveTasks(const string& username) {
    string filename = getFilename(username);
    ofstream outFile(filename);
    json j = json::array();

    priority_queue<Task> temp = taskQueue;
    while (!temp.empty()) {
        j.push_back(temp.top());
        temp.pop();
    }
    outFile << setw(4) << j;
    outFile.close();
}


//check valid DATE:
bool isValidDate(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;

    int year, month, day;
    try {
        year  = stoi(date.substr(0, 4));
        month = stoi(date.substr(5, 2));
        day   = stoi(date.substr(8, 2));
    } catch (...) {
        return false;
    }

    if (month < 1 || month > 12) return false;
    if (day < 1) return false;

    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    // Leap year check
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        daysInMonth[1] = 29;

    if (day > daysInMonth[month - 1]) return false;

    return true;
}


// Add new task
void addTask() {
    Task t;
    t.id = taskId++;

    // Task name
    cout << "Enter task name: ";
    getline(cin, t.name);

    // Priority
    while (true) {
        cout << "Enter priority [1 - 5]: ";
        string p;
        getline(cin, p);
        try {
            t.priority = stoi(p);
            if (t.priority >= 1 && t.priority <= 5) break;
        } catch (...) {}
        cout << "Invalid priority. Try again.\n";
    }

    // Tag
    cout << "Enter tag (e.g., Work, Study): ";
    getline(cin, t.tag);

    // Deadline with validation
    do {
        cout << "Enter deadline (YYYY-MM-DD): ";
        getline(cin, t.deadline);
        if (!isValidDate(t.deadline))
            cout << "Invalid date. Try again.\n";
    } while (!isValidDate(t.deadline));

    // Timestamp & push
    t.timestamp = getCurrentTimestamp();
    taskQueue.push(t);
    cout << "Task added.\n";
}



// View tasks in pages of 10 with proper bounds checking
void viewTasksPaginated() {
    if (taskQueue.empty()) {
        cout << "No tasks to show.\n";
        return;
    }

    vector<Task> tasks;
    priority_queue<Task> temp = taskQueue;
    while (!temp.empty()) {
        tasks.push_back(temp.top());
        temp.pop();
    }

    const int pageSize = 10;
    int page = 0;
    char input;

    while (true) {
        int start = page * pageSize;
        if (start >= (int)tasks.size()) {
            cout << "No more pages.\n";
            break;
        }

        cout << "\nPage " << (page + 1) << ":\n";
        cout << left
             << setw(5)  << "ID"
             << setw(10) << "Priority"
             << setw(20) << "Tag"
             << setw(15) << "Deadline"
             << setw(25) << "Timestamp"
             << "Task Name\n";
        cout << string(90, '-') << "\n";

        for (int i = start; i < min(start + pageSize, (int)tasks.size()); ++i) {
            Task& t = tasks[i];
            cout << left
                 << setw(5)  << t.id
                 << setw(10) << t.priority
                 << setw(20) << t.tag
                 << setw(15) << t.deadline
                 << setw(25) << t.timestamp
                 << t.name << "\n";
        }

        cout << "[n]ext, [p]revious, [q]uit: ";
        cin >> input;

        if (input == 'n') {
            if ((page + 1) * pageSize >= (int)tasks.size()) {
                cout << "You're already on the last page.\n";
            } else {
                ++page;
            }
        }
        else if (input == 'p') {
            if (page > 0) {
                --page;
            } else {
                cout << "You're already on the first page.\n";
            }
        }
        else if (input == 'q') {
            break;
        }
        else {
            cout << "Invalid option. Try again.\n";
        }
    }
}

// Complete (pop) the top-priority task
void completeTask() {
    if (taskQueue.empty()) {
        cout << "No tasks available.\n";
        return;
    }
    Task t = taskQueue.top();
    taskQueue.pop();
    cout << "Completed task: " << t.name << " (ID: " << t.id << ")\n";
}

// Delete a specific task by ID
void deleteTaskById() {
    if (taskQueue.empty()) {
        cout << "No tasks to delete.\n";
        return;
    }
    int id;
    cout << "Enter task ID to delete: ";
    cin >> id;

    bool found = false;
    priority_queue<Task> temp;
    while (!taskQueue.empty()) {
        Task t = taskQueue.top();
        taskQueue.pop();
        if (t.id == id) found = true;
        else temp.push(t);
    }
    taskQueue = temp;
    cout << (found ? "Deleted successfully.\n" : "Task ID not found.\n");
}

// Update a task’s fields by ID
void updateTaskById() {
    if (taskQueue.empty()) {
        cout << "No tasks to update.\n";
        return;
    }
    int id;
    cout << "Enter task ID to update: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;
    priority_queue<Task> temp;
    while (!taskQueue.empty()) {
        Task t = taskQueue.top();
        taskQueue.pop();
        if (t.id == id) {
            found = true;
            string input;
            cout << "Enter new task name (or . to skip): ";
            getline(cin, input);
            if (input != ".") t.name = input;

            cout << "Enter new priority (1-5 or -1 to skip): ";
            int p; cin >> p;
            if (p >= 1 && p <= 5) t.priority = p;
            cin.ignore();

            cout << "Enter new tag (or . to skip): ";
            getline(cin, input);
            if (input != ".") t.tag = input;

            cout << "Enter new deadline (YYYY-MM-DD or . to skip): ";
            getline(cin, input);
            if (input != ".") t.deadline = input;
        }
        temp.push(t);
    }
    taskQueue = temp;
    cout << (found ? "Task updated.\n" : "Task ID not found.\n");
}

// Search tasks by ID, name, or tag
void searchTask() {
    if (taskQueue.empty()) {
        cout << "No tasks to search.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string keyword;
    cout << "Enter keyword (name, tag, or ID): ";
    getline(cin, keyword);

    bool found = false;
    priority_queue<Task> temp = taskQueue;
    while (!temp.empty()) {
        Task t = temp.top();
        temp.pop();
        if (to_string(t.id) == keyword
            || t.name.find(keyword) != string::npos
            || t.tag.find(keyword)  != string::npos) {
            cout << "ID: " << t.id
                 << " | Name: "    << t.name
                 << " | Priority: "<< t.priority
                 << " | Tag: "     << t.tag
                 << " | Deadline: "<< t.deadline << "\n";
            found = true;
        }
    }
    if (!found) cout << "No matching task found.\n";
}
