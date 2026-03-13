#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};

void addStudent();
void viewStudents();
void updateStudent();
void deleteStudent();
void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;
    while (1) {
        printf("\n=== Student Record System ===\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: printf("Goodbye!\n"); exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

void addStudent() {
    struct Student s;
    FILE *f = fopen("students.dat", "ab");
    
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    getchar();
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, f);
    fclose(f);
    printf("Student added successfully!\n");
}

void viewStudents() {
    struct Student s;
    FILE *f = fopen("students.dat", "rb");
    if (!f) { printf("No records found!\n"); return; }

    printf("\nID\tName\t\tAge\tMarks\n");
    printf("------------------------------------\n");
    while (fread(&s, sizeof(s), 1, f)) {
        printf("%d\t%-15s\t%d\t%.2f\n", s.id, s.name, s.age, s.marks);
    }
    fclose(f);
}

void updateStudent() {
    struct Student s;
    int id, found = 0;
    FILE *f = fopen("students.dat", "rb+");
    if (!f) return;

    printf("Enter ID to update: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, f)) {
        if (s.id == id) {
            found = 1;
            printf("Enter new Name: ");
            getchar();
            fgets(s.name, 50, stdin);
            s.name[strcspn(s.name, "\n")] = 0;
            printf("Enter new Age: ");
            scanf("%d", &s.age);
            printf("Enter new Marks: ");
            scanf("%f", &s.marks);

            fseek(f, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, f);
            printf("Record updated!\n");
            break;
        }
    }
    fclose(f);
    if (!found) printf("Student not found!\n");
}

void deleteStudent() {
    struct Student s;
    int id, found = 0;
    FILE *f = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, f)) {
        if (s.id != id) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(f);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) printf("Student deleted!\n");
    else printf("Student not found!\n");
}