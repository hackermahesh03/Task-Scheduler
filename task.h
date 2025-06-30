// task.h
#ifndef TASK_H
#define TASK_H

#include <string>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

struct Task {
    int id;
    string name;
    int priority;
    string timestamp;
    string tag;
    string deadline;

    bool operator<(const Task& other) const {
        return priority > other.priority; // min-heap
    }
};

// Convert Task to/from JSON
inline void to_json(json& j, const Task& t) {
    j = json{{"id", t.id}, {"name", t.name}, {"priority", t.priority},
             {"timestamp", t.timestamp}, {"tag", t.tag}, {"deadline", t.deadline}};
}

inline void from_json(const json& j, Task& t) {
    j.at("id").get_to(t.id);
    j.at("name").get_to(t.name);
    j.at("priority").get_to(t.priority);
    j.at("timestamp").get_to(t.timestamp);
    j.at("tag").get_to(t.tag);
    j.at("deadline").get_to(t.deadline);
}

#endif
