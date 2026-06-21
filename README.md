# UDRMSys — University Dormitory & Restaurant Management System

A simple desktop app made with **C++** and **Qt Widgets** for a university OOP course project.
It manages students, dormitories, rooms, and restaurant meals — all from one window.

---

## What it does

- Add / remove students
- Add / remove dormitories
- Add rooms inside a dormitory, assign or remove students from a room
- Manage breakfast/lunch/dinner menus for each dormitory's restaurant
- Scan a student ID to record that they had a meal (no double-scanning the same meal twice a day)
- Move to a new day, which resets meal records
- A live log at the bottom of the window shows every action taken

---

## How the interface is organized

The app opens in **one main window** with a tab bar at the top:

| Tab | What you can do there |
|---|---|
| 👤 Students | Add a student (opens a small popup form), remove a student, search the list |
| 🏠 Dormitories | Add a dormitory, remove a dormitory |
| 🚪 Rooms | Pick a dormitory from a dropdown, add rooms to it, assign/remove students |
| 🍽 Restaurant | Pick a dormitory, then opens a separate window to manage its meals, menus, and ID scanning |

Each tab has a table that updates automatically whenever something changes. Small popup windows (`QInputDialog`, `QMessageBox`) are used for quick inputs, warnings, and confirmations.

---

## Project structure

```
UDRMS/
├── Person.h / Person.cpp             
├── Student.h / Student.cpp           
├── Room.h / Room.cpp
├── Menu.h / Menu.cpp
├── Meal.h / Meal.cpp
├── Restaurant.h / Restaurant.cpp
├── Dormitory.h / Dormitory.cpp
├── University.h / University.cpp
├── DormitoryException.h / .cpp        
│
├── mainwindow.h / .cpp / .ui          
├── studentdialog.h / .cpp / .ui       
├── restaurantdialog.h / .cpp / .ui    
└── main.cpp
```

## How the classes connect

- A `University` holds a list of `Dormitory` objects and a list of `Student` objects.
- Each `Dormitory` owns a list of `Room` objects and one `Restaurant`.
- Each `Restaurant` owns three `Meal` objects (breakfast, lunch, dinner), and each `Meal` has a `Menu` (list of dishes) and a list of student IDs who already ate that meal today.
- A `Room` keeps pointers to the `Student`s currently assigned to it.
- `Student` inherits from `Person`.