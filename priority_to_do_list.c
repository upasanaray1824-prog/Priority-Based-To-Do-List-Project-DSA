#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX 100

struct Task {
    int id;
    char description[100];
    int priority;
    int completed;
};

struct Task tasks[MAX];
int count = 0;
int nextId = 1;

void clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* discard extra input */
    }
}

void addTask(void) {
    if (count >= MAX) {
        printf("\nTask list is full!\n");
        return;
    }

    tasks[count].id = nextId++;

    printf("\nEnter task description: ");
    if (fgets(tasks[count].description,
              sizeof(tasks[count].description), stdin) == NULL) {
        printf("Unable to read task description.\n");
        return;
    }
    tasks[count].description[
        strcspn(tasks[count].description, "\n")] = '\0';

    printf("Enter priority (1-High, 2-Medium, 3-Low): ");
    if (scanf("%d", &tasks[count].priority) != 1 ||
        tasks[count].priority < 1 || tasks[count].priority > 3) {
        printf("Invalid priority! Please enter 1, 2 or 3.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    tasks[count].completed = 0;
    count++;
    printf("\nTask added successfully!\n");
}

void displayTasks(void) {
    int i;

    if (count == 0) {
        printf("\nNo tasks available.\n");
        return;
    }

    printf("\n--- TO-DO LIST ---\n");
    for (i = 0; i < count; i++) {
        printf("\nID: %d\n", tasks[i].id);
        printf("Task: %s\n", tasks[i].description);

        if (tasks[i].priority == 1)
            printf("Priority: High\n");
        else if (tasks[i].priority == 2)
            printf("Priority: Medium\n");
        else
            printf("Priority: Low\n");

        printf("Status: %s\n",
               tasks[i].completed ? "Completed" : "Pending");
    }
}

void completeTask(void) {
    int id, i;

    if (count == 0) {
        printf("\nNo tasks available to complete.\n");
        return;
    }

    displayTasks();
    printf("\nEnter task ID to mark completed: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid task ID.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    for (i = 0; i < count; i++) {
        if (tasks[i].id == id) {
            if (tasks[i].completed) {
                printf("\nTask is already completed.\n");
            } else {
                tasks[i].completed = 1;
                printf("\nTask marked as completed!\n");
            }
            return;
        }
    }

    printf("\nTask ID not found.\n");
}

void deleteTask(void) {
    int id, i, j;

    if (count == 0) {
        printf("\nNo tasks available to delete.\n");
        return;
    }

    displayTasks();
    printf("\nEnter task ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid task ID.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    for (i = 0; i < count; i++) {
        if (tasks[i].id == id) {
            for (j = i; j < count - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            count--;
            printf("\nTask deleted successfully!\n");
            return;
        }
    }

    printf("\nTask ID not found.\n");
}

int main(void) {
    int choice;

    do {
        printf("\n===== PRIORITY TO-DO LIST =====\n");
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Complete Task\n");
        printf("4. Delete Task\n");
        printf("5. Exit\n");
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid choice! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: addTask(); break;
            case 2: displayTasks(); break;
            case 3: completeTask(); break;
            case 4: deleteTask(); break;
            case 5: printf("\nThank you!\n"); break;
            default: printf("\nInvalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}