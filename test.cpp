// test.cpp
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include "task.h"
using namespace std;

void testTaskToJsonAndBack() {
    Task original = {1, "Test Task", 2, "2025-06-30 12:00:00", "Work", "2025-07-01"};
    json j = original;
    Task recovered = j.get<Task>();
    assert(recovered.id == 1);
    assert(recovered.name == "Test Task");
    assert(recovered.priority == 2);
    assert(recovered.timestamp == "2025-06-30 12:00:00");
    assert(recovered.tag == "Work");
    assert(recovered.deadline == "2025-07-01");
    cout << "✅ testTaskToJsonAndBack passed.\n";
}

void testTaskPriorityOrdering() {
    Task t1 = {1, "Low Priority", 5, "ts", "tag", "dl"};
    Task t2 = {2, "Medium Priority", 3, "ts", "tag", "dl"};
    Task t3 = {3, "High Priority", 1, "ts", "tag", "dl"};

    priority_queue<Task> q;
    q.push(t1);
    q.push(t2);
    q.push(t3);

    assert(q.top().priority == 1);
    q.pop();
    assert(q.top().priority == 3);
    q.pop();
    assert(q.top().priority == 5);

    cout << "✅ testTaskPriorityOrdering passed.\n";
}

void testTaskUpdateLogic() {
    Task t = {10, "Old Task", 4, "ts", "OldTag", "2025-07-01"};
    t.name = "Updated Task";
    t.priority = 2;
    t.tag = "NewTag";
    t.deadline = "2025-07-15";

    assert(t.name == "Updated Task");
    assert(t.priority == 2);
    assert(t.tag == "NewTag");
    assert(t.deadline == "2025-07-15");

    cout << "✅ testTaskUpdateLogic passed.\n";
}

void testTaskDeletionById() {
    vector<Task> tasks = {
        {1, "T1", 2, "ts", "tag", "dl"},
        {2, "T2", 3, "ts", "tag", "dl"},
        {3, "T3", 1, "ts", "tag", "dl"}
    };

    int deleteId = 2;
    vector<Task> remaining;
    for (Task& t : tasks) {
        if (t.id != deleteId) remaining.push_back(t);
    }

    assert(remaining.size() == 2);
    for (Task& t : remaining) assert(t.id != deleteId);

    cout << "✅ testTaskDeletionById passed.\n";
}

void testSearchTaskByKeyword() {
    vector<Task> tasks = {
        {1, "Math Homework", 1, "ts", "Study", "2025-07-01"},
        {2, "Office Meeting", 2, "ts", "Work", "2025-07-02"},
        {3, "Read Book", 3, "ts", "Leisure", "2025-07-03"}
    };

    string keyword = "Book";
    bool found = false;

    for (Task& t : tasks) {
        if (t.name.find(keyword) != string::npos || t.tag.find(keyword) != string::npos ||
            to_string(t.id) == keyword) {
            found = true;
        }
    }

    assert(found == true);
    cout << "✅ testSearchTaskByKeyword passed.\n";
}

void runAllTests() {
    testTaskToJsonAndBack();
    testTaskPriorityOrdering();
    testTaskUpdateLogic();
    testTaskDeletionById();
    testSearchTaskByKeyword();
    cout << "\n🎉 All tests passed successfully.\n";
}

int main() {
    runAllTests();
    return 0;
}
