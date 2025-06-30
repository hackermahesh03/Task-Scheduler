# 🗓️ Task Scheduler (C++ Console App)

A feature-rich console-based Task Scheduler application developed in C++ using Object-Oriented Programming and file-based JSON persistence. The project supports multiple users, task prioritization, tagging, deadlines, and user-friendly interactions through a clean terminal interface.

---

## 🚀 Features

- 🔐 **Multi-User Login** (via username)
- ➕ **Add Task** with:
  - Auto-incrementing Task ID
  - Priority (1 to 5)
  - Tag (e.g., Work, Study)
  - Deadline (YYYY-MM-DD)
  - Timestamp (auto-generated)
- 📄 **View Tasks** (with Pagination if >10 tasks)
- ✅ **Complete Task** (removes highest-priority task)
- ❌ **Delete Task by ID**
- 🔁 **Update Task by ID** (skip fields with `.`)
- 🔍 **Search Task** by name, tag, or ID
- 💾 **JSON-Based Persistent Storage** (per user)
- 🔎 **Input Validation & Edge Case Handling**
- 🧪 **Unit Tests** with `assert()` covering all core features

---

## 🛠️ Technologies Used

- C++ (STL, OOP)
- JSON (using [nlohmann/json](https://github.com/nlohmann/json))
- File I/O (for persistent storage)
- Header file modularity (`.h` and `.cpp` separation)

---

## 📁 Folder Structure

```
Task Scheduler/
├── main.cpp
├── task_manager.cpp
├── task_manager.h
├── user_manager.cpp
├── user_manager.h
├── task.h
├── json.hpp                # External JSON library
├── test.cpp                # Unit tests
├── tasks_<username>.json  # Auto-generated for each user
```

---

## ▶️ How to Run the App

### 🧮 Compile the Main Program:
```bash
g++ main.cpp task_manager.cpp user_manager.cpp -I. -o scheduler
```

### ▶️ Run:
```bash
./scheduler
```

---

## 🧪 Unit Testing

### ✅ Run Unit Tests:
```bash
g++ test.cpp -I. -o test
./test
```

### 🔍 Covered Scenarios:
- Task-to-JSON and back
- Priority queue ordering
- Task update logic
- Task deletion by ID
- Search functionality

Unit tests are written using standard C++ `assert()` statements for clarity and simplicity.

---

## 🧠 Author

- **Mahesh Babu Nettem** – B.Tech Final Year Student  
- Focused on mastering DSA and Web Development for placements

---

