#  To-Do List Application (Data Structures Project)

This project is a terminal-based To-Do List application written in **C**, created for the **CPE112 Data Structures** course.  
It helps users manage tasks with scheduling, reminders, priority adjustment, and statistics using key data structures.

---

##  Introduction

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

##  Overview

Managing tasks with different levels of urgency is a common challenge.  
This To-Do List application enables:
- Task creation with due dates, priorities, and tags
- Automatic status updates (Pending/Overdue)
- Undo functionality for task completion
- Advanced search and filtering capabilities
- Import/Export functionality for data persistence

It's designed to improve productivity, reduce stress, and provide an organized workflow in a **command-line interface**.

---

##  Features

-  **Task Management**
  - Add, Edit, and Delete Tasks
  - Assign Due Dates and Priority Levels
  - Tag Tasks for Better Organization
  - Mark Tasks as Completed (with Undo)
  
-  **Smart Features**
  - Automatic Status Updates (Overdue Detection)
  - Priority-based Task Sorting
  - Due Date Validation
  - Duplicate Task Name Prevention
  
-  **Search & Filter**
  - Search by Name, Description, Priority, Status
  - Filter by Date Range
  - Search by Tags
  - Find Tasks without Due Dates
  
-  **Views & Statistics**
  - Standard/Simplified/Enhanced Views
  - Weekly and Monthly Summaries
  - Completion Statistics with Visual Progress Bars
  
-  **Data Management**
  - Import Tasks from TXT
  - Export Tasks to Text File
  - Clear Completed Tasks
  - Daily Task Tracking

---

##  Data Structures Used

| Structure | Purpose | Time Complexity |
|-----------|---------|----------------|
| **Linked List** | Store tasks dynamically | O(1) insertion, O(n) search |
| **Stack** | Track completed tasks (Undo/Clear) | O(1) push/pop |
| **Arrays** | Temporary storage for sorting | O(n) space |
| **Bubble Sort** | Organize tasks by date/priority | O(n²) time |

---

##  File Structure

```bash
 ToDoList-DSA/
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


##  How to Run the Code

###  Requirements
- A C compiler (`gcc`)
- All header files (`scheduler.h`, `task_management.h`, `searchstats.h`) and `main.c` in the same folder

###  Compilation

first
```bash
gcc -o todolist main.c task_management.c searchandstat.c scheduler.c fileio.c
```
then 

if you use MacOS :
```bash
./todolist 
```

if you use Window :
```bash
./todolist.exe 
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
---

##  Test Cases

### Test Case 1: Add Task with Valid Input

**Input:**
```bash
Option: 1
Task name: Complete Assignment
Description: Finish DSA homework
Priority: 1
Due date: 10 05 2025
```
**Expected Output:**
```bash
Task added successfully!
```

### Test Case 2: Invalid Date Input
**Input:**
```bash
Option: 1
Task name: Test Task
Due date: 32 13 2025
```
**Expected Output:**
```bash
Invalid date. Due date not set.
```

### Test Case 3: Duplicate Task Name
**Input:**
```bash
Option: 1
Task name: Complete Assignment (existing task)
```
**Expected Output:**
```bash
Error: A task with this name already exists. Please choose a different name.
```

### Test Case 4: Search Non-existent Task
**Input:**
```bash
Option: 7
Search option: 1
Keyword: NonExistentTask
```
**Expected Output:**
```bash
No matching tasks found.
```

### Test Case 5: Complete and Undo Task
**Input:**
```bash
Option: 4
Task name: Complete Assignment
Option: 5
```
**Expected Output:**
```bash
Task 'Complete Assignment' marked as completed!
Last completed task restored to the list.
```
---

##  Testing

### Running Test Cases
1. Import test data:
((tasks_import.txt , sample_tasks.txt))
```bash
Option: 10
Filename: tasks_import.txt
```
2. Verify error handling:
- Try adding duplicate task names
- Enter invalid dates (32/13/2025)
- Input out-of-range priorities (0, 4)

3. Test core functionality:
- Add, edit, delete tasks
- Complete and undo operations
- Search with various criteria
- View statistics

### Performance Testing
Run performance analysis (Option 16 [hidden function] ) to see:
- Operation timing for different data sizes


### Edge Cases Tested
- Empty task list operations
- Maximum capacity handling (1000+ tasks)
- Invalid input formats
- Boundary date values
- Special characters in task names



---



##  Group Members

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

##  Acknowledgments

Special thanks to our professor and TAs for guiding us through the concepts of data structures, which helped us turn theory into a working, real-world project.


