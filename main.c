#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Student structure
typedef struct {
    char name[50];
    float marks;
    char grade;
} Student;

// Function to assign grades based on marks
char assign_grade(float marks) {
    if (marks >= 90)
        return 'A';
    else if (marks >= 80)
        return 'B';
    else if (marks >= 70)
        return 'C';
    else if (marks >= 60)
        return 'D';
    else
        return 'F';
}

// Function to calculate the mean marks and mean grade
void calculate_means(Student *students, int count, float *mean_marks, char *mean_grade) {
    float total_marks = 0;
    int total_grade_points = 0;
    for (int i = 0; i < count; i++) {
        total_marks += students[i].marks;
        switch (students[i].grade) {
            case 'A': total_grade_points += 4; break;
            case 'B': total_grade_points += 3; break;
            case 'C': total_grade_points += 2; break;
            case 'D': total_grade_points += 1; break;
            case 'F': total_grade_points += 0; break;
        }
    }
    *mean_marks = total_marks / count;
    float mean_grade_point = (float)total_grade_points / count;

    if (mean_grade_point >= 3.5)
        *mean_grade = 'A';
    else if (mean_grade_point >= 2.5)
        *mean_grade = 'B';
    else if (mean_grade_point >= 1.5)
        *mean_grade = 'C';
    else if (mean_grade_point >= 0.5)
        *mean_grade = 'D';
    else
        *mean_grade = 'F';
}

// Function to read students data from a file
int read_students_data(const char *file_path, Student **students) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", file_path);
        return -1;
    }

    int count;
    fscanf(file, "%d", &count);
    *students = (Student *)malloc(count * sizeof(Student));

    for (int i = 0; i < count; i++) {
        fscanf(file, "%s %f", (*students)[i].name, &(*students)[i].marks);
        (*students)[i].grade = assign_grade((*students)[i].marks);
    }

    fclose(file);
    return count;
}

// Function to write transcript data to a file
void write_transcript(const char *output_file, Student *students, int count, float mean_marks, char mean_grade) {
    FILE *file = fopen(output_file, "w");
    if (file == NULL) {
        printf("Error creating file: %s\n", output_file);
        return;
    }

    fprintf(file, "Name,Marks,Grade\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%.2f,%c\n", students[i].name, students[i].marks, students[i].grade);
    }

    fprintf(file, "\nMean Marks: %.2f\n", mean_marks);
    fprintf(file, "Mean Grade: %c\n", mean_grade);

    fclose(file);
}

// Main processing function
int main() {
    const char *input_file = "C:\\users\\hp1030\\Documents\\student_marks.txt";
    const char *output_file = "student_transcript.txt";
    Student *students;
    int student_count = read_students_data(input_file, &students);

    if (student_count == -1) {
        return 1;
    }

    float mean_marks;
    char mean_grade;
    calculate_means(students, student_count, &mean_marks, &mean_grade);
    write_transcript(output_file, students, student_count, mean_marks, mean_grade);

    printf("Transcript saved to %s\n", output_file);

    free(students);
    return 0;
}
