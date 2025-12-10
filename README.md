# Hostel Meal Management System (C)

A simple **command-line Hostel Meal Management System** written in C.

The system is designed for a university hostel to manage:

- Student accounts
- Daily meal booking / cancellation
- Hostel menu
- Meal billing and credit log
- Admin vs student roles

All data is stored in plain text files inside the `resources/` folder, so the project is easy to run and understand.

---

## Features

### 👤 Student

- Register as a new student
- Log in using roll number and password
- View:
  - Current balance
  - Monthly meal calendar (ON/OFF per day)
- Book meal for the current day (before a cut-off time, e.g. 16:00)
- Cancel meal for the current day
- See total meals and approximate bill

### 🛠️ Admin

Admin login is detected when the roll number is `admin`.

Admin can:

- View list of all students with:
  - Roll number
  - Name
  - Room number
  - Current balance
- Edit hostel menu:
  - Show menu
  - Add item
  - Delete item
- Manage credits:
  - Add credit to a student
  - View credit log (who paid how much and when)
- View meal log for a given day (who has meal ON)
- Generate monthly bill for a student
- Reset student passwords

---
## Command for Compiling and Running the code

```bash
gcc main.c meal.c auth.c student.c file_handeler.c helper.c billing.c -o MealManagement;./MealManagement
```
---
## Project Structure

```text
MealManagementSystem/
├── Readme.md                 # (currently empty in the project)
├── resources/
│   ├── admin_pass.txt        # admin credentials
│   ├── credit_log.txt        # log of all credit changes
│   ├── menu.txt              # daily hostel menu
│   ├── students_basic_info.txt  # student details + balance + meal history
│   └── students_pass.txt     # student login info (roll, password)
└── scr/
    ├── auth.c
    ├── billing.c
    ├── def.h
    ├── file_handeler.c
    ├── helper.c
    ├── main.c
    ├── meal.c
    ├── student.c
    ├── Makefile
    └── RunCommandText
