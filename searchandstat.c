#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "scheduler.h"       
#include "task_management.h"
#include "searchandstat.h"


/*
searchTasks() - Search tasks by multiple criteria
 - Time: O(n), Space: O(1)
 - Sample Case:
    Input:
      Choice: 7 (Keyword search)
      Keyword: "project"
    Output:
      --- Pending Tasks ---
      Name: Final Project
      Description: Complete capstone project
      Tags: academic, important
      -------------------------
      --- Completed Tasks ---
      Name: Project Proposal
      -------------------------
 */
void searchTasks(task* head, completedstack* stack, const char* keyword) {
    int found = 0;
    int search_option;
    int min_priority = 0, max_priority = 0;
    date start_date = {0}, end_date = {0};
    char new_keyword[100] = {0};
    char buffer[100];
    
    printf("\n=== Task Search ===\n");
    printf("Search by:\n");
    printf("1. Name\n");
    printf("2. Description\n");
    printf("3. Priority Range\n");
    printf("4. Status (Pending/Completed/Overdue)\n");
    printf("5. Due Date Range\n");
    printf("6. Tasks with No Due Date\n");
    printf("7. Keyword (search all fields)\n");
    printf("Enter your choice (1-7): ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &search_option) != 1) {
        printf("Invalid input. Search aborted.\n");
        return;
    }
    
    // search criteria based on option
    switch(search_option) {
        case 1: // Name
        case 2: // Description
            
            printf("Enter search keyword: ");
            if (fgets(new_keyword, sizeof(new_keyword), stdin) == NULL) {
                printf("Error reading keyword. Search aborted.\n");
                return;
            }
            new_keyword[strcspn(new_keyword, "\n")] = 0;
            
            // Check if keyword is empty
            if (strlen(new_keyword) == 0) {
                printf("Keyword cannot be empty. Search aborted.\n");
                return;
            }
            
            printf("\n=== Search Results for '%s' ===\n", new_keyword);
            
            // Search pending tasks
            printf("--- Pending Tasks ---\n");
            task* current = head;
            while (current) {
                if ((search_option == 1 && strstr(current->name, new_keyword)) ||
                    (search_option == 2 && strstr(current->description, new_keyword))) {
                    printTaskInfo(current);
                    found = 1;
                }
                current = current->next;
            }
            
            // Search completed tasks
            printf("--- Completed Tasks ---\n");
            stacknode* node = stack->top;
            while (node) {
                task* t = node->task_data;
                if ((search_option == 1 && strstr(t->name, new_keyword)) ||
                    (search_option == 2 && strstr(t->description, new_keyword))) {
                    printTaskInfo(t);
                    found = 1;
                }
                node = node->next;
            }
            break;
            
        case 3: // Priority Range
            printf("Enter priority from : ");
            if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &min_priority) != 1) {
                printf("Invalid input. Search aborted.\n");
                return;
            }
            
            printf("Enter priority to : ");
            if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &max_priority) != 1) {
                printf("Invalid input. Search aborted.\n");
                return;
            }
            
            if (min_priority > max_priority) {
                // Swap if min > max
                int temp = min_priority;
                min_priority = max_priority;
                max_priority = temp;
            }
            
            printf("\n=== Search Results for Priority %d to %d ===\n", min_priority, max_priority);
            
            // Search pending tasks
            printf("--- Pending Tasks ---\n");
            current = head;
            while (current) {
                if (current->priority >= min_priority && current->priority <= max_priority) {
                    printTaskInfo(current);
                    found = 1;
                }
                current = current->next;
            }
            
            // Search completed tasks
            printf("--- Completed Tasks ---\n");
            node = stack->top;
            while (node) {
                task* t = node->task_data;
                if (t->priority >= min_priority && t->priority <= max_priority) {
                    printTaskInfo(t);
                    found = 1;
                }
                node = node->next;
            }
            break;
            
        case 4: // Status
            printf("Search by status:\n");
            printf("1. Pending\n");
            printf("2. Completed\n");
            printf("3. Overdue\n");
            printf("Enter choice: ");
            int status_choice;
            
            if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &status_choice) != 1) {
                printf("Invalid input. Search aborted.\n");
                return;
            }
            
            TaskStatus search_status;
            switch(status_choice) {
                case 1: search_status = PENDING; break;
                case 2: search_status = COMPLETED; break;
                case 3: search_status = OVERDUE; break;
                default: 
                    printf("Invalid status choice.\n");
                    return;
            }
            
            printf("\n=== Search Results for Status: %s ===\n", 
                  (search_status == PENDING) ? "Pending" : 
                  (search_status == COMPLETED) ? "Completed" : "Overdue");
            
            // For completed tasks : search the stack
            if (search_status == COMPLETED) {
                printf("--- Completed Tasks ---\n");
                stacknode* status_node = stack->top;
                while (status_node) {
                    task* t = status_node->task_data;
                    if (t->status == search_status) {
                        printTaskInfo(t);
                        found = 1;
                    }
                    status_node = status_node->next;
                }
            } else {
                // For PENDING/OVERDUE : search the main list
                printf("--- Tasks ---\n");
                task* status_current = head;
                while (status_current) {
                    if (status_current->status == search_status) {
                        printTaskInfo(status_current);
                        found = 1;
                    }
                    status_current = status_current->next;
                }
            }
            break;
            
        case 5: // Due Date Range
            printf("Enter start date (DD MM YYYY): ");
            if (fgets(buffer, sizeof(buffer), stdin) == NULL || 
                sscanf(buffer, "%d %d %d", &start_date.day, &start_date.month, &start_date.year) != 3) {
                printf("Invalid date format. Search aborted.\n");
                return;
            }
            
            printf("Enter end date (DD MM YYYY): ");
            if (fgets(buffer, sizeof(buffer), stdin) == NULL || 
                sscanf(buffer, "%d %d %d", &end_date.day, &end_date.month, &end_date.year) != 3) {
                printf("Invalid date format. Search aborted.\n");
                return;
            }
            
            // Validate dates
            if (!isValidDate(start_date.day, start_date.month, start_date.year) || 
                !isValidDate(end_date.day, end_date.month, end_date.year)) {
                printf("Invalid date range. Search aborted.\n");
                return;
            }
            
            // Check if start date is after end date
            if (compareDates(start_date, end_date) > 0) {
                printf("Error: Start date must be before end date. Search aborted.\n");
                return;
            }
            
            printf("\n=== Search Results for Due Date from %02d/%02d/%04d to %02d/%02d/%04d ===\n",
                   start_date.day, start_date.month, start_date.year,
                   end_date.day, end_date.month, end_date.year);
            
            // Search pending tasks
            printf("--- Pending Tasks ---\n");
            task* date_current = head;
            while (date_current) {
                if (date_current->due_date_set) {
                    // Check if task due date is within range
                    if (compareDates(date_current->duedate, start_date) >= 0 && 
                        compareDates(date_current->duedate, end_date) <= 0) {
                        printTaskInfo(date_current);
                        found = 1;
                    }
                }
                date_current = date_current->next;
            }
            
            // Search completed tasks
            printf("--- Completed Tasks ---\n");
            stacknode* date_node = stack->top;
            while (date_node) {
                task* t = date_node->task_data;
                if (t->due_date_set) {
                    // Check if task due date is within range
                    if (compareDates(t->duedate, start_date) >= 0 && 
                        compareDates(t->duedate, end_date) <= 0) {
                        printTaskInfo(t);
                        found = 1;
                    }
                }
                date_node = date_node->next;
            }
            break;
            
        case 6: // Tasks with No Due Date
            printf("\n=== Tasks with No Due Date ===\n");
            
            // Search pending tasks
            printf("--- Pending Tasks ---\n");
            task* nodate_current = head;
            while (nodate_current) {
                if (!nodate_current->due_date_set) {
                    printTaskInfo(nodate_current);
                    found = 1;
                }
                nodate_current = nodate_current->next;
            }
            
            // Search completed tasks
            printf("--- Completed Tasks ---\n");
            stacknode* nodate_node = stack->top;
            while (nodate_node) {
                task* t = nodate_node->task_data;
                if (!t->due_date_set) {
                    printTaskInfo(t);
                    found = 1;
                }
                nodate_node = nodate_node->next;
            }
            break;
            
        case 7: // Keyword search
            printf("Enter keyword to search in all fields: ");
            if (fgets(new_keyword, sizeof(new_keyword), stdin) == NULL) {
                printf("Error reading keyword. Search aborted.\n");
                return;
            }
            new_keyword[strcspn(new_keyword, "\n")] = 0;
            
            printf("\n=== Keyword Search Results for '%s' ===\n", new_keyword);
            
            // Search pending tasks
            printf("--- Pending Tasks ---\n");
            task* keyword_current = head;
            while (keyword_current) {
                // Check name, description, and tags
                int found_in_task = 0;
                
                // Check name
                if (strstr(keyword_current->name, new_keyword)) {
                    found_in_task = 1;
                }
                
                // Check description
                if (!found_in_task && strstr(keyword_current->description, new_keyword)) {
                    found_in_task = 1;
                }
                
                // Check tags
                if (!found_in_task) {
                    for (int i = 0; i < keyword_current->tag_count; i++) {
                        if (strstr(keyword_current->tags[i], new_keyword)) {
                            found_in_task = 1;
                            break;
                        }
                    }
                }
                
                if (found_in_task) {
                    printTaskInfo(keyword_current);
                    // Add tag information to output
                    if (keyword_current->tag_count > 0) {
                        printf("Tags: ");
                        for (int i = 0; i < keyword_current->tag_count; i++) {
                            printf("%s%s", keyword_current->tags[i], 
                                  (i < keyword_current->tag_count - 1) ? ", " : "\n");
                        }
                        printf("-------------------------\n");
                    }
                    found = 1;
                }
                
                keyword_current = keyword_current->next;
            }
            
            // Search completed tasks
            printf("--- Completed Tasks ---\n");
            stacknode* keyword_node = stack->top;
            while (keyword_node) {
                task* t = keyword_node->task_data;
                
                // Check name, description, and tags
                int found_in_task = 0;
                
                // Check name
                if (strstr(t->name, new_keyword)) {
                    found_in_task = 1;
                }
                
                // Check description
                if (!found_in_task && strstr(t->description, new_keyword)) {
                    found_in_task = 1;
                }
                
                // Check tags
                if (!found_in_task) {
                    for (int i = 0; i < t->tag_count; i++) {
                        if (strstr(t->tags[i], new_keyword)) {
                            found_in_task = 1;
                            break;
                        }
                    }
                }
                
                if (found_in_task) {
                    printTaskInfo(t);
                    // Add tag information to output
                    if (t->tag_count > 0) {
                        printf("Tags: ");
                        for (int i = 0; i < t->tag_count; i++) {
                            printf("%s%s", t->tags[i], 
                                  (i < t->tag_count - 1) ? ", " : "\n");
                        }
                        printf("-------------------------\n");
                    }
                    found = 1;
                }
                
                keyword_node = keyword_node->next;
            }
            break;
            
        default:
            printf("Invalid search option.\n");
            return;
    }
    
    if (!found) {
        printf("No matching tasks found.\n");
    }
}


/*
printTaskInfo() - Displays detailed task information
 - Time: O(1), Space: O(1)
 - Sample Case:
    Input: Task with name="Study", priority=1, due=05/05/2025
    Output:
      Name: Study
      Description: Prepare for final exam
      Priority: 1 (High)
      Status: Pending
      Due Date: 05/05/2025
      -------------------------
 */
void printTaskInfo(task* t) {
    printf("Name: %s\n", t->name);
    printf("Description: %s\n", t->description);
    printf("Priority: %d (%s)\n", t->priority, 
           (t->priority == 1) ? "High" : (t->priority == 2) ? "Medium" : "Low");
    printf("Status: %s\n", 
           (t->status == PENDING) ? "Pending" : 
           (t->status == COMPLETED) ? "Completed" : "Overdue");
    if (t->due_date_set) {
        printf("Due Date: %02d/%02d/%04d\n", 
               t->duedate.day, t->duedate.month, t->duedate.year);
    } else {
        printf("Due Date: Not Set\n");
    }
    printf("-------------------------\n");
}


/*
showStats() - Shows overall task statistics
 - Time: O(n), Space: O(1)
 - Example: showStats(tasks, stack, today) -> "Total: 10, Completed: 50%"
 */
void showStats(task* head, completedstack* stack, date today) {
    int total = 0, completed = 0, pending = 0, overdue = 0;
    
    // Count pending and overdue tasks
    task* p = head;
    while (p) {
        if (p->completed) {
            
            completed++;
        } else if (p->status == OVERDUE || 
                   (p->due_date_set && compareDates(today, p->duedate) > 0)) {
            overdue++;
        } else {
            pending++;
        }
        p = p->next;
    }
    
    // Count completed tasks in stack
    stacknode* s = stack->top;
    while (s) {
        if (s->task_data) {
            completed++;
        }
        s = s->next;
    }
    
    // Total tasks
    total = pending + completed + overdue;
    
    printf("\n=== Task Statistics ===\n");
    printf("Total Tasks: %d\n", total);
    
    // Calculate percentages
    float completed_percent = total > 0 ? (completed * 100.0f) / total : 0;
    float pending_percent = total > 0 ? (pending * 100.0f) / total : 0;
    float overdue_percent = total > 0 ? (overdue * 100.0f) / total : 0;
    
    printf("Completed: %d (%.1f%%)\n", completed, completed_percent);
    printf("Pending: %d (%.1f%%)\n", pending, pending_percent);
    printf("Overdue/Late: %d (%.1f%%)\n", overdue, overdue_percent);
    
    printf("\n=== Progress ===\n");
    
    printf("[");
    int bar_length = 20;
    int completed_bars = total > 0 ? (int)((completed * bar_length) / total) : 0;
    int overdue_bars = total > 0 ? (int)((overdue * bar_length) / total) : 0;
    
    for (int i = 0; i < bar_length; i++) {
        if (i < completed_bars) {
            printf("="); // Completed sections
        } else if (i < completed_bars + overdue_bars) {
            printf("!"); // Overdue sections
        } else {
            printf(" "); // Pending sections
        }
    }
    printf("] %.1f%% completed\n", completed_percent);
}


/*
doneToday() - Shows tasks completed today
 - Time: O(n), Space: O(1)
 - Example: doneToday(&tasks, &stack) -> lists today's completed tasks
 */
void doneToday(tasklist* list, completedstack* stack) {
    date today = getToday();
    int count = 0;
    
    printf("\n=== Tasks Completed Today (%02d/%02d/%04d) ===\n", 
           today.day, today.month, today.year);
    
    // Update task statuses before checking
    
    // check pending tasks
    task* current = list->head;
    while (current) {
        if (current->completed && current->status == COMPLETED) {
            
            printf("Task: %s\n", current->name);
            printf("Description: %s\n", current->description);
            printf("Priority: %d\n", current->priority);
            printf("-------------------------\n");
            count++;
        }
        current = current->next;
    }
    
    // check completed tasks in the stack
    stacknode* node = stack->top;
    while (node) {
        if (node->task_data) {
            // Assuming the task in the stack is completed today
            printf("Task: %s\n", node->task_data->name);
            printf("Description: %s\n", node->task_data->description);
            printf("Priority: %d\n", node->task_data->priority);
            printf("-------------------------\n");
            count++;
            
            // Limit to top 5 most recently completed tasks
            if (count >= 5) {
                break; 
            }
        }
        node = node->next;
    }
    
    if (count == 0) {
        printf("No tasks completed today.\n");
    } else {
        printf("Total tasks completed today: %d\n", count);
    }
}


/*
show_combined_stats() - Menu for all/weekly/monthly stats
 - Time: O(n), Space: O(1)
 - Sample Case:
    Input: Choice: 2 (Weekly Statistics)
    Output:
      === Task Statistics for This Week ===
      Total Tasks for this week: 5
      Completed: 2 (40.0%)
      Pending: 2 (40.0%)
      Overdue: 1 (20.0%)
      
      [====!    ] 40.0% completed
 */
void show_combined_stats(task* head, completedstack* stack, date today) {
    int choice;
    char buffer[10];
    
    printf("\n=== Task Statistics View ===\n");
    printf("1. All-time Statistics\n");
    printf("2. Weekly Statistics\n");
    printf("3. Monthly Statistics\n");
    printf("Enter your choice (1-3): ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &choice) != 1) {
        printf("Invalid input. Showing all-time statistics by default.\n");
        choice = 1;
    }
    
    switch(choice) {
        case 1:
            showStats(head, stack, today);  // Original all times stats function
            break;
        case 2:
            show_time_stats(head, stack, today, 0);  // Weekly stats 
            break;
        case 3:
            show_time_stats(head, stack, today, 1);  // Monthly stats 
            break;
        default:
            printf("Invalid option. Showing all-time statistics.\n");
            showStats(head, stack, today);
    }
}


/*
show_time_stats() - Shows stats for specific period
 - Time: O(n), Space: O(1)
 - Example: show_time_stats(tasks, stack, today, 0) -> weekly stats
 */
void show_time_stats(task* head, completedstack* stack, date today, int period) {
    int total = 0, completed = 0, pending = 0, overdue = 0;
    int high_priority = 0, medium_priority = 0, low_priority = 0;
    
    // Define period in days
    int days_period = (period == 0) ? 7 : 30; // 0 for week, 1 for month
    
    printf("\n=== Task Statistics for %s ===\n", (period == 0) ? "This Week" : "This Month");
    
    // Count pending and overdue tasks for the specified period
    task* p = head;
    while (p) {
        if (p->due_date_set && isDateWithinDays(today, p->duedate, days_period)) {
            if (p->completed) {
                completed++;
            } else if (p->status == OVERDUE) {
                overdue++;
            } else {
                pending++;
            }
            
            // Count by priority
            switch (p->priority) {
                case 1: high_priority++; break;
                case 2: medium_priority++; break;
                case 3: low_priority++; break;
            }
        }
        p = p->next;
    }
    
    // Count completed tasks in stack for the specified period
    int stack_items = 0;
    stacknode* s = stack->top;
    while (s && stack_items < days_period) { 
        if (s->task_data) {
            completed++;
        }
        stack_items++;
        s = s->next;
    }
    
    // Total tasks
    total = pending + completed + overdue;
    
    printf("Total Tasks for this %s: %d\n", (period == 0) ? "week" : "month", total);
    
    // Calculate percentages
    float completed_percent = total > 0 ? (completed * 100.0f) / total : 0;
    float pending_percent = total > 0 ? (pending * 100.0f) / total : 0;
    float overdue_percent = total > 0 ? (overdue * 100.0f) / total : 0;
    
    printf("Completed: %d (%.1f%%)\n", completed, completed_percent);
    printf("Pending: %d (%.1f%%)\n", pending, pending_percent);
    printf("Overdue/Late: %d (%.1f%%)\n", overdue, overdue_percent);
    
    // Priority breakdown
    printf("\nPriority Breakdown:\n");
    printf("High Priority: %d (%.1f%%)\n", high_priority, total > 0 ? (high_priority * 100.0f) / total : 0);
    printf("Medium Priority: %d (%.1f%%)\n", medium_priority, total > 0 ? (medium_priority * 100.0f) / total : 0);
    printf("Low Priority: %d (%.1f%%)\n", low_priority, total > 0 ? (low_priority * 100.0f) / total : 0);
    
    printf("\n=== Progress ===\n");
    // Print a visual progress bar
    printf("[");
    int bar_length = 20;
    int completed_bars = total > 0 ? (int)((completed * bar_length) / total) : 0;
    int overdue_bars = total > 0 ? (int)((overdue * bar_length) / total) : 0;
    
    for (int i = 0; i < bar_length; i++) {
        if (i < completed_bars) {
            printf("="); // Completed sections
        } else if (i < completed_bars + overdue_bars) {
            printf("!"); // Overdue sections
        } else {
            printf(" "); // Pending sections
        }
    }
    printf("] %.1f%% completed\n", completed_percent);
}

