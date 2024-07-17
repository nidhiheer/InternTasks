#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct Student {
    string name;
    int id;
    double assignmentGrade;
    double examGrade;
    double overallGrade;
};

vector<Student> students;

void addStudent() {
    Student student;
    cout << "Enter student name: ";
    cin >> student.name;
    cout << "Enter student ID: ";
    cin >> student.id;
    cout << "Enter assignment grade: ";
    cin >> student.assignmentGrade;
    cout << "Enter exam grade: ";
    cin >> student.examGrade;
    student.overallGrade = (student.assignmentGrade + student.examGrade) / 2.0;
    students.push_back(student);
}

void calculateClassAverage() {
    double sum = 0.0;
    for (const auto& student : students) {
        sum += student.overallGrade;
    }
    double classAverage = sum / students.size();
    cout << "Class average: " << classAverage << endl;
}

void displayClassToppers() {
    vector<Student> sortedStudents = students;
    sort(sortedStudents.begin(), sortedStudents.end(), [](const Student& a, const Student& b) {
        return a.overallGrade > b.overallGrade;
    });
    cout << "Class toppers (Top 3):" << endl;
    for (int i = 0; i < 3 && i < sortedStudents.size(); i++) {
        cout << (i + 1) << ". " << sortedStudents[i].name << " (ID: " << sortedStudents[i].id << ") - Overall grade: " << sortedStudents[i].overallGrade << endl;
    }
}

void displayStudentGrades() {
    for (const auto& student : students) {
        cout << "Name: " << student.name << ", ID: " << student.id << endl;
        cout << "Assignment grade: " << student.assignmentGrade << endl;
        cout << "Exam grade: " << student.examGrade << endl;
        cout << "Overall grade: " << student.overallGrade << endl;
        cout << endl;
    }
}

int main() {
    int choice;
    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Add student" << endl;
        cout << "2. Calculate class average" << endl;
        cout << "3. Display class toppers" << endl;
        cout << "4. Display student grades" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                calculateClassAverage();
                break;
            case 3:
                displayClassToppers();
                break;
            case 4:
                displayStudentGrades();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}