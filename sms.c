#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a student
struct Student {
    int id;
    char name[100];
    float gpa;
};

// Function to add a student record to the file
void addStudent() {
    FILE *file = fopen("students.dat", "ab"); // Open the file in append binary mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Student student;

    printf("Enter student ID: ");
    scanf("%d", &student.id);

    printf("Enter student name: ");
    scanf("%s", student.name);

    printf("Enter student GPA: ");
    scanf("%f", &student.gpa);

    // Write the student record to the file
    fwrite(&student, sizeof(struct Student), 1, file);

    fclose(file);
    printf("Student record added successfully!\n");
}

// Function to display all student records
void displayStudents() {
    FILE *file = fopen("students.dat", "rb"); // Open the file in read binary mode
    if (file == NULL) {
        printf("No student records found!\n");
        return;
    }

    struct Student student;

    printf("\n--- List of Students ---\n");
    printf("ID\tName\t\tGPA\n");
    printf("----------------------------\n");

    // Read and display each student record from the file
    while (fread(&student, sizeof(struct Student), 1, file)) {
        printf("%d\t%s\t\t%.2f\n", student.id, student.name, student.gpa);
    }

    fclose(file);
}

// Function to search for a student by ID
void searchStudent() {
    int id;
    printf("Enter student ID to search: ");
    scanf("%d", &id);

    FILE *file = fopen("students.dat", "rb"); // Open the file in read binary mode
    if (file == NULL) {
        printf("No student records found!\n");
        return;
    }

    struct Student student;
    int found = 0;

    // Read each student record and search for the given ID
    while (fread(&student, sizeof(struct Student), 1, file)) {
        if (student.id == id) {
            printf("Student found:\n");
            printf("ID: %d\n", student.id);
            printf("Name: %s\n", student.name);
            printf("GPA: %.2f\n", student.gpa);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }

    fclose(file);
}

// Function to delete a student by ID
void deleteStudent() {
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    FILE *file = fopen("students.dat", "rb"); // Open the file in read binary mode
    FILE *tempFile = fopen("temp.dat", "wb"); // Temporary file to store updated records
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Student student;
    int found = 0;

    // Read each student record and copy to the temporary file, except the one to delete
    while (fread(&student, sizeof(struct Student), 1, file)) {
        if (student.id == id) {
            found = 1; // Mark that we found the student to delete
        } else {
            fwrite(&student, sizeof(struct Student), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Delete the original file and rename the temporary file
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        printf("Student with ID %d deleted successfully!\n", id);
    } else {
        printf("Student with ID %d not found.\n", id);
    }
}

// Main function with menu-driven interface
int main() {
    int choice;

    do {
        printf("\n=== Student Management System ===\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Delete Student by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
