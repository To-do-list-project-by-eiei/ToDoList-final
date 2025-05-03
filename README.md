# 📝 To-Do List Application (Data Structures Project)

This project is a terminal-based To-Do List application written in **C**, created for the **CPE112 Data Structures** course.  
It helps users manage tasks with scheduling, reminders, priority adjustment, and statistics using key data structures.

---

## 📚 Introduction

In daily life, tasks often vary in priority and urgency. Traditional to-do lists fail to address:
- Deadlines approaching
- Reordering priorities dynamically
- Tracking completed tasks
- Efficient searching and filtering
- Data backup and recovery

This project solves those problems by:
- Using a **linked list** for dynamic task management
- Applying a **stack** to track completed items with undo support
- Implementing **sorting algorithms** for task organization
- Including **date handling** and automatic status updates
- Supporting **tag-based organization** and advanced search features

---

## 📌 Overview

Managing tasks with different levels of urgency is a common challenge.  
This To-Do List application enables:
- Task creation with due dates, priorities, and tags
- Automatic status updates (Pending/Overdue)
- Undo functionality for task completion
- Advanced search and filtering capabilities
- Dashboard view with statistics and progress tracking
- Import/Export functionality for data persistence

It's designed to improve productivity, reduce stress, and provide an organized workflow in a **command-line interface**.

---

## 🚀 Features

- ✅ **Task Management**
  - Add, Edit, and Delete Tasks
  - Assign Due Dates and Priority Levels
  - Tag Tasks for Better Organization
  - Mark Tasks as Completed (with Undo)
  
- ✅ **Smart Features**
  - Automatic Status Updates (Overdue Detection)
  - Priority-based Task Sorting
  - Due Date Validation
  - Duplicate Task Name Prevention
  
- ✅ **Search & Filter**
  - Search by Name, Description, Priority, Status
  - Filter by Date Range
  - Search by Tags
  - Find Tasks without Due Dates
  
- ✅ **Views & Statistics**
  - Standard/Simplified/Enhanced Views
  - Weekly and Monthly Summaries
  - Completion Statistics with Visual Progress Bars
  
- ✅ **Data Management**
  - Import Tasks from TXT
  - Export Tasks to Text File
  - Clear Completed Tasks
  - Daily Task Tracking

---

## 🧠 Data Structures Used

| Structure | Purpose | Time Complexity |
|-----------|---------|----------------|
| **Linked List** | Store tasks dynamically | O(1) insertion, O(n) search |
| **Stack** | Track completed tasks (Undo/Clear) | O(1) push/pop |
| **Arrays** | Temporary storage for sorting | O(n) space |
| **Bubble Sort** | Organize tasks by date/priority | O(n²) time |

---

## 📁 File Structure

```bash
📁 ToDoList-DSA/
├── main.c                 # Entry point with menu system
├── task_management.c      # Core task operations
├── task_management.h      # Task structures and declarations
├── scheduler.c            # Date handling and scheduling logic
├── scheduler.h            # Date operations and status updates
├── searchandstat.c        # Search and statistics functions
├── searchandstat.h        # Search declarations
├── fileio.c              # Import/Export functionality
├── fileio.h              # File operations declarations
├── sample_tasks.txt      # Sample data for import
└── README.md             # Project documentation
```

---


## 💻 How to Run the Code

### 🧾 Requirements
- A C compiler (`gcc`)
- All header files (`scheduler.h`, `task_management.h`, `searchstats.h`) and `main.c` in the same folder

### ⚙️ Compilation

first
```bash
gcc -o todolist main.c task_management.c searchandstat.c scheduler.c fileio.c
```
then 
```bash
./todolist
```
the file should run properly

---
###  Sample menu

```bash
=== TO-DO LIST MENU ===
1. Add Task
2. View Tasks (Standard/Simplified/By Tag)
3. Edit Task
4. Mark Task as Completed
5. Undo Last Completed Task
6. Delete Task
7. Search Tasks
8. View Statistics (All/Week/Month)
9. Clear All Completed Tasks
10. Import Tasks
11. Export Tasks
12. Daily Completed Tasks
13. Simulate Day Change
14. Time Period Summary (Week/Month)
15. Add Tag to Task
0. Exit
Select an option:
```

###  Sample input

- ADD function (1)
1.
```bash
CompProg, Linked List practice - Practice linked list operations for homework, 1, 30/04/2025
```
2.
```bash
CalII, Integration review - Study integration techniques for upcoming exam, 1, 02/05/2025
```
more sample input on the file sample_import.txt

## expected output
```bash
Name: CompProg [!]URGENT
Description:  Debugging session - Fix errors in C program homework
Status: Pending
Due Date: 30/04/2025
```
```bash
Name: CalII
Description:  Integration review - Study integration techniques for upcoming exam
Status: Pending
Due Date: 02/05/2025
```

---



## 👨‍👩‍👧‍👦 Group Members

| Name                        | Student ID    | Role / Responsibilities                    |
|-----------------------------|---------------|---------------------------------------------|
| **Kulchaya Paipinij**       | 67070503406   | • Search, Statistics & File I/O (`searchandstat.h`, `fileio.h`)<br>• **Project Report Writing**<br>• **Presentation Preparation** |
| **Chayanit Kuntanarumitkul** | 67070503408   | • Scheduling, Date Handling (`scheduler.h`)<br>• **Lead Code Reviewer & Bug Fixing**<br>•  **GitHub Repository Management** |
| **Siripitch Chaiyabutra**   | 67070503440   | • Task Management & UI (`task_management.h`)<br>• **Flowchart Design**<br>• **System Architecture Documentation** |

### Project Documentation

- **Report & Presentation**: Jointly prepared by Chayanit Kuntanarumitkul and Kulchaya Paipinij
- **Flowcharts & Diagrams**: Created by Siripitch Chaiyabutra
- **Code Review & Integration**: Led by Chayanit Kuntanarumitkul
-  **GitHub Repository**: Managed and maintained by Chayanit Kuntanarumitkul


> Each member contributed to their specialized areas while collaborating on the overall project success.


---

## 🌟 Acknowledgments

Special thanks to our professor and TAs for guiding us through the concepts of data structures, which helped us turn theory into a working, real-world project.


