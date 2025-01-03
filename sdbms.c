#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LEN 100
#define MAX_COURSE_LEN 50
#define MAX_SUBJECTS 5
#define MAX_ADDRESS_LEN 200

// Struct for storing student information
struct student_info
{
    int roll_number;
    char first_name[MAX_NAME_LEN];
    char last_name[MAX_NAME_LEN];
    char course[MAX_COURSE_LEN];
    float marks[MAX_SUBJECTS];
    float total_marks;
    char grade;
    char co_curricular[MAX_NAME_LEN];
    char parent_name[MAX_NAME_LEN];
    char parent_contact[MAX_NAME_LEN];
    char address[MAX_ADDRESS_LEN];
};

// Function declarations
void add_student(struct student_info *students, int *count);
void input_marks(int student_index, struct student_info *students);
void assign_grade(int student_index, struct student_info *students);
void input_co_curricular(int student_index, struct student_info *students);
void find_using_roll(int count, struct student_info *students);
void find_using_fname(int count, struct student_info *students);
void find_using_course(int count, struct student_info *students);
void delete_student(int *count, struct student_info *students);
void update(int count, struct student_info *students);
void count(int count);
void displayCoCurricularActivities(struct student_info *students, int count);
void displayParentDetails(struct student_info *students, int count);
void displayStudentDetails(struct student_info *students, int count);
void generateReportCard(struct student_info *students, int count);
void saveToFile(struct student_info *students, int count);
void loadFromFile(struct student_info *students, int *count);
int validateRollNumber(int rollNumber, struct student_info *students, int count);
float validateMarks();
void displayMenu();
void validateParentContact(char *contact);
void validateName(char *name);
void clearInputBuffer();


// Main function
int main()
{
    struct student_info students[MAX_STUDENTS];
    int student_count = 0;
    loadFromFile(students, &student_count);

    int choice;
    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer(); // to clear newline from input buffer

        switch (choice) {
            case 1:
                add_student(students, &student_count);
                saveToFile(students, student_count);
                break;
            case 2:
                input_marks(student_count, students);
                saveToFile(students, student_count);
                break;
            case 3:
                assign_grade(student_count, students);
                saveToFile(students, student_count);
                break;
            case 4:
                input_co_curricular(student_count, students);
                saveToFile(students, student_count);
                break;
            case 5:
                find_using_roll(student_count, students);
                break;
            case 6:
                find_using_fname(student_count, students);
                break;
            case 7:
                find_using_course(student_count, students);
                break;
            case 8:
                delete_student(&student_count, students);
                saveToFile(students, student_count);
                break;
            case 9:
                update(student_count, students);
                saveToFile(students, student_count);
                break;
            case 10:
                count(student_count);
                break;
            case 11:
                displayStudentDetails(students, student_count);
                saveToFile(students, student_count);
                break;
            case 12:
                displayCoCurricularActivities(students, student_count);
                break;
            case 13:
                displayParentDetails(students, student_count);
                break;
            case 14:
                generateReportCard(students, student_count);
                break;
            case 15:
                printf("Exiting the program.\n");
                exit(0);
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
// Function definitions
// 0. Function to display menu options
void displayMenu()
{
    printf("                                                             *****************************************\n");
    printf("                                                             *    Student Record Management System   *\n");
    printf("                                                             *****************************************\n");
    printf("                                                             \n\n");
    printf("                                                             ******************************************\n");
    printf("                                                             * 1.  Add Student                        *\n");
    printf("                                                             * 2.  Input Marks                        *\n");
    printf("                                                             * 3.  Assign Grade                       *\n");
    printf("                                                             * 4.  Input Co-curricular Activities     *\n");
    printf("                                                             * 5.  Find using Roll Number             *\n");
    printf("                                                             * 6.  Find using First Name              *\n");
    printf("                                                             * 7.  Find using Course                  *\n");
    printf("                                                             * 8.  Delete Student                     *\n");
    printf("                                                             * 9.  Update Student                     *\n");
    printf("                                                             * 10. Count Students                     *\n");
    printf("                                                             * 11. Display Student Details            *\n");
    printf("                                                             * 12. Display Co-curricular Activities   *\n");
    printf("                                                             * 13. Display Parent Details             *\n");
    printf("                                                             * 14. Show Report Card                   *\n");
    printf("                                                             * 15. Exit                               *\n");
    printf("                                                             ******************************************\n\n");
}
// 1. Function to add a new student
void add_student(struct student_info *students, int *count)
{
    struct student_info student;

    // Predefined list of courses
    char courses[][MAX_COURSE_LEN] = {"CS", "ECE", "EE VLSI", "EE ACT", "MNC", "Biotech", "BBA", "BCA"};
    int num_courses = sizeof(courses) / sizeof(courses[0]); // Calculate number of courses available

    printf("Enter roll number: ");
    scanf("%d", &student.roll_number);
    clearInputBuffer(); // Clear buffer

    // Check if roll number already exists
    if (validateRollNumber(student.roll_number, students, *count))
        {
            printf("Roll number already exists!\n");
            return;
        }

    // Input validation for student names
    printf("Enter first name: ");
    fgets(student.first_name, MAX_NAME_LEN, stdin);
    student.first_name[strcspn(student.first_name, "\n")] = 0; // Remove newline
    validateName(student.first_name);

    printf("Enter last name : ");
    fgets(student.last_name, MAX_NAME_LEN, stdin);
    student.last_name[strcspn(student.last_name, "\n")] = 0;
    validateName(student.last_name);

    // Display predefined course options
    printf("Select course from the following options:\n");
    for (int i = 0; i < num_courses; i++)
        {
            printf("%d. %s\n", i + 1, courses[i]);
        }

    int course_choice;
    printf("Enter the number corresponding to the course: ");
    scanf("%d", &course_choice);
    clearInputBuffer(); // Clear buffer

    // Check if the entered choice is valid
    if (course_choice < 1 || course_choice > num_courses)
        {
            printf("Invalid choice! Please select a valid course.\n");
            return;
        }

    // Assign the selected course
    strcpy(student.course, courses[course_choice - 1]);

    // Validate parent contact
    printf("Enter parent's contact number: ");
    fgets(student.parent_contact, MAX_NAME_LEN, stdin);
    student.parent_contact[strcspn(student.parent_contact, "\n")] = 0;
    validateParentContact(student.parent_contact);


    printf("Enter parent's name: ");
    fgets(student.parent_name, MAX_NAME_LEN, stdin);
    student.parent_name[strcspn(student.parent_name, "\n")] = 0;

    printf("Enter address: ");
    fgets(student.address, MAX_ADDRESS_LEN, stdin);
    student.address[strcspn(student.address, "\n")] = 0;


    // Add the student record to the array
    students[*count] = student;
    (*count)++;
}

// 2. Function to input marks for a student

void input_marks(int count, struct student_info *students)
{
    if (count == 0)
    {
        printf("No students available to input marks.\n");
        return;
    }

    int roll;
    printf("Enter roll number of the student to input marks: ");
    scanf("%d", &roll);
    clearInputBuffer();

    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (students[i].roll_number == roll)
        {
            found = 1;
            printf("Enter marks for student %s %s:\n", students[i].first_name, students[i].last_name);
            for (int j = 0; j < MAX_SUBJECTS; j++)
            {
                printf("Enter marks for subject %d: ", j + 1);
                students[i].marks[j] = validateMarks();
            }

            // Calculate total marks and assign grade after updating marks
            float total = 0;
            for (int j = 0; j < MAX_SUBJECTS; j++)
            {
                total += students[i].marks[j];
            }
            students[i].total_marks = total;

            printf("Marks updated successfully for %s %s.\n", students[i].first_name, students[i].last_name);
            break;
        }
    }

    if (!found)
    {
        printf("No student found with roll number %d.\n", roll);
    }
}
// 3. Function to assign grade based on total marks
void assign_grade(int count, struct student_info *students)
    {
        if (count == 0)
            {
                printf("No students available to assign grades.\n");
                return;
            }

        for (int i = 0; i < count; i++)
            {
                float total = 0;
                for (int j = 0; j < MAX_SUBJECTS; j++)
                    {
                        total += students[i].marks[j];
                    }
                students[i].total_marks = total;

                float percentage = (total / (MAX_SUBJECTS * 100)) * 100;
                if (percentage >= 90)
                    {
                        students[i].grade = 'A';
                    }
                else if (percentage >= 75)
                    {
                        students[i].grade = 'B';
                    }
                else if (percentage >= 60)
                    {
                        students[i].grade = 'C';
                    }
                else
                    {
                        students[i].grade = 'D';
                    }
            }

        printf("Grades assigned to all students.\n");
    }


// 4. Function to input co-curricular activities
void input_co_curricular(int count, struct student_info *students)
    {
        int roll;
        printf("Enter roll number: ");
        scanf("%d", &roll);
        clearInputBuffer();

        for (int i = 0; i < count; i++)
            {
                if (students[i].roll_number == roll)
                    {
                        printf("Enter co-curricular activities for %s %s: ", students[i].first_name, students[i].last_name);
                        fgets(students[i].co_curricular, MAX_NAME_LEN, stdin);
                        students[i].co_curricular[strcspn(students[i].co_curricular, "\n")] = 0;
                        printf("Activities updated successfully.\n");
                        return;
                    }
            }
        printf("Student with roll number %d not found.\n", roll);
    }


// 5. Function to search for a student by roll number
void find_using_roll(int count, struct student_info *students)
    {
        int roll;
        printf("Enter roll number to search: ");
        scanf("%d", &roll);
        clearInputBuffer();  // To clear newline character after input
        int found = 0;
        for (int i = 0; i < count; i++)
            {
                if (students[i].roll_number == roll)
                    {
                        printf("Student found: %s %s\n", students[i].first_name, students[i].last_name);
                        found = 1;
                        break;
                    }
            }
    if (!found)
        {
            printf("Student with roll number %d not found.\n", roll);
        }
    }

// 6. Function to search for students by first name
void find_using_fname(int count, struct student_info *students)
    {
        char fname[MAX_NAME_LEN];
        printf("Enter first name to search: ");
        fgets(fname, MAX_NAME_LEN, stdin);
        fname[strcspn(fname, "\n")] = 0; // Remove newline character
        int found = 0;
        for (int i = 0; i < count; i++)
            {
                if (strcmp(students[i].first_name, fname) == 0)
                    {
                        printf("Student found: %s %s\n", students[i].first_name, students[i].last_name);
                        found = 1;
                    }
            }
        if (!found)
            {
                printf("No student found with the first name %s.\n", fname);
            }
    }

// 7. Function to search for students by course
void find_using_course(int count, struct student_info *students)
    {
        char course[MAX_COURSE_LEN];
        printf("Select course from the following options:\n1. CS\n2. ECE\n3. EE VLSI\n4. EE ACT\n5. MNC\n6. Biotech\n7. BBA\n8. BCA\n");
        printf("Enter course to search: ");
        fgets(course, MAX_COURSE_LEN, stdin);
        course[strcspn(course, "\n")] = 0; // Remove newline character
        int found = 0;
        for (int i = 0; i < count; i++)
            {
                if (strcmp(students[i].course, course) == 0)
                    {
                        printf("Student found: %s %s\n", students[i].first_name, students[i].last_name);
                        found = 1;
                    }
            }
        if (!found)
            {
                printf("No students found in the course %s.\n", course);
            }
    }

// 8. Function to delete a student by roll number
void delete_student(int *count, struct student_info *students)
    {
        int roll;
        printf("Enter roll number to delete: ");
        scanf("%d", &roll);
        clearInputBuffer(); // To clear newline character
        int found = 0;
        for (int i = 0; i < *count; i++)
            {
                if (students[i].roll_number == roll)
                    {
                        for (int j = i; j < *count - 1; j++)
                            {
                                students[j] = students[j + 1];
                            }
                            (*count)--;
                            printf("Student deleted successfully.\n");
                            found = 1;
                            break;
                    }
            }
        if (!found)
            {
                printf("Student with roll number %d not found.\n", roll);
            }
    }

// 9. Function to update a student's details

// Function to update a student's details
void update(int count, struct student_info *students) {
    int roll;
    printf("Enter roll number to update: ");
    scanf("%d", &roll);
    clearInputBuffer(); // To clear newline character
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (students[i].roll_number == roll) {
            found = 1;
            printf("Updating details for student: %s %s\n", students[i].first_name, students[i].last_name);

            // Update first name
            printf("Enter new first name (current: %s): ", students[i].first_name);
            fgets(students[i].first_name, MAX_NAME_LEN, stdin);
            students[i].first_name[strcspn(students[i].first_name, "\n")] = 0;

            // Update last name
            printf("Enter new last name (current: %s): ", students[i].last_name);
            fgets(students[i].last_name, MAX_NAME_LEN, stdin);
            students[i].last_name[strcspn(students[i].last_name, "\n")] = 0;

            // Update parent's name
            printf("Enter new parent's name (current: %s): ", students[i].parent_name);
            fgets(students[i].parent_name, MAX_NAME_LEN, stdin);
            students[i].parent_name[strcspn(students[i].parent_name, "\n")] = 0;

            // Update parent's contact number
            printf("Enter new parent's contact number (current: %s): ", students[i].parent_contact);
            fgets(students[i].parent_contact, MAX_NAME_LEN, stdin);
            students[i].parent_contact[strcspn(students[i].parent_contact, "\n")] = 0;

            // Update course
            printf("Enter new course (current: %s): ", students[i].course);
            fgets(students[i].course, MAX_COURSE_LEN, stdin);
            students[i].course[strcspn(students[i].course, "\n")] = 0;

            // Update address
            printf("Enter new address (current: %s): ", students[i].address);
            fgets(students[i].address, MAX_ADDRESS_LEN, stdin);
            students[i].address[strcspn(students[i].address, "\n")] = 0;

            // Update roll number
            printf("Enter new roll number (current: %d): ", students[i].roll_number);
            int new_roll;
            scanf("%d", &new_roll);
            clearInputBuffer();
            if (!validateRollNumber(new_roll, students, count)) {
                students[i].roll_number = new_roll;
            } else {
                printf("Error: Roll number %d already exists! Keeping the old roll number.\n", new_roll);
            }

            printf("Student details updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Student with roll number %d not found.\n", roll);
    }
}
// 10. Function to count the number of students
void count(int count)
    {
        printf("Total number of students: %d\n", count);
    }

// 11. Function to display all student details
void displayStudentDetails(struct student_info *students, int count)
    {
        printf("Student Details:\n");
        for (int i = 0; i < count; i++)
            {
                printf("----------------------------------------------\n");
                printf("Roll Number: %d\nName: %s %s\nCourse: %s\nTotal Marks: %.2f\nGrade: %c\n",
                students[i].roll_number, students[i].first_name, students[i].last_name,
                students[i].course, students[i].total_marks, students[i].grade);
                printf("----------------------------------------------\n");
            }
    }

// 12. Function to display co-curricular activities
void displayCoCurricularActivities(struct student_info *students, int count)
    {
        printf("Co-curricular activities of students:\n");
        for (int i = 0; i < count; i++)
            {
                printf("%s %s: %s\n", students[i].first_name, students[i].last_name, students[i].co_curricular);
            }
    }

// 13. Function to display parent details
void displayParentDetails(struct student_info *students, int count)
    {
        printf("Parent details of students:\n");
        for (int i = 0; i < count; i++)
            {
                printf("%s %s's Parent: %s, Contact: %s\n", students[i].first_name, students[i].last_name, students[i].parent_name, students[i].parent_contact);
            }
    }

// 14. Function to generate a report
void generateReportCard(struct student_info *students, int count)
    {
        printf("\nStudent Report:\n");
        for (int i = 0; i < count; i++)
            {
                printf("\nStudent: %s %s\n", students[i].first_name, students[i].last_name);
                printf("Roll Number: %d\n", students[i].roll_number);
                printf("Course: %s\n", students[i].course);
                printf("Total Marks: %.2f\n", students[i].total_marks);
                printf("Grade: %c\n", students[i].grade);

                if (students[i].grade == 'A')
                    {
                        printf("Comments: Excellent performance!\n");
                    }
                else if (students[i].grade == 'B')
                    {
                        printf("Comments: Good work, keep it up!\n");
                    }
                else if (students[i].grade == 'C')
                    {
                        printf("Comments: Can do better, put in more effort.\n");
                    }
                else
                    {
                        printf("Comments: Needs improvements, please seek help.\n");
                    }
            }
    }

// 15. Function to save student data to a file
void saveToFile(struct student_info *students, int count) {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error saving data to file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%s,%.2f,%c,%s,%s,%s\n",
                students[i].roll_number,
                students[i].first_name,
                students[i].last_name,
                students[i].course,
                students[i].total_marks,
                students[i].grade,
                students[i].co_curricular,
                students[i].parent_name,
                students[i].parent_contact);
    }
    fclose(file);
    printf("Data saved successfully in text format.\n");
}


// 16. Function to load student data from a file
void loadFromFile(struct student_info *students, int *count) {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("No data file found. Starting fresh.\n");
        *count = 0;
        return;
    }

    *count = 0; // Reset count before loading
    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%f,%c,%[^,],%[^,],%[^\n]\n",
                  &students[*count].roll_number,
                  students[*count].first_name,
                  students[*count].last_name,
                  students[*count].course,
                  &students[*count].total_marks,
                  &students[*count].grade,
                  students[*count].co_curricular,
                  students[*count].parent_name,
                  students[*count].parent_contact) == 9) {
        (*count)++;
    }

    fclose(file);
    printf("Data loaded successfully from text format.\n");
}


// 17. Function to validate roll number (ensure uniqueness)
int validateRollNumber(int rollNumber, struct student_info *students, int count)
    {
        for (int i = 0; i < count; i++)
            {
                if (students[i].roll_number == rollNumber)
                    {
                        return 1;
                    }
            }
        return 0;
    }

// 18. Function to validate marks (ensure they are within a valid range)
float validateMarks()
    {
        float marks;
        while (1)
            {
                scanf("%f", &marks);
                if (marks >= 0 && marks <= 100)
                    {
                        return marks;
                    }
                else
                    {
                        printf("Invalid marks! Please enter marks between 0 and 100: ");
                        main();
                    }
            }
    }


// 19. Helper function to validate name
void validateName(char *name)
    {
        for (int i = 0; name[i] != '\0'; i++)
            {
                if ((name[i] < 'A' || (name[i] > 'Z' && name[i] < 'a') || name[i] > 'z') && name[i] != ' ')
                    {
                        printf("Invalid character in name! Please enter a valid name.\n");
                        main();
                    }
            }
    }

// 20. Helper function to validate parent contact number
void validateParentContact(char *contact)
    {
        if (strlen(contact) != 10 || !isdigit(contact[0]))
            {
                printf("Invalid contact number! Please enter a valid 10-digit contact.\n");
                main();
            }
    }


// 21. Function to clear input buffer after reading integer inputs
void clearInputBuffer()
    {
        while (getchar() != '\n');
    }
