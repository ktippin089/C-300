/*
 * Project Two: Advising Assistance Program
 * Author: Kevin Tippin
 * Course: CS 300
 * Due Date: April 20, 2025
 * Description: This program allows academic advisors to
 * load course data from a file, view a list of courses,
 * and retrieve information about specific courses including
 * prerequisites.
 *
 * File Structure Example:
 * CourseID, Title, Prerequisite1, Prerequisite2,...
 * Example:
 * CS101,Introduction to Computer Science,
 * CS102,Data Structures,CS101
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

// Define a structure to hold course information
struct Course {
    string courseID;
    string title;
    vector<string> prerequisites;

    // Function to print course information
    void printInfo() const {  // make it const since it doesn't modify member variables
        cout << "Course ID: " << courseID << "\n";
        cout << "Title: " << title << "\n";
        cout << "Prerequisites: ";
        if (prerequisites.empty()) {
            cout << "None" << endl;
        }
        else {
            for (const auto& prereq : prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        }
    }
};

// Function prototypes
void loadCourses(const string& filename, vector<Course>& courses);
void printCourses(const vector<Course>& courses);
void printCourseInfo(const vector<Course>& courses, const string& courseID);

int main() {
    vector<Course> courses;
    string filename;

    while (true) {
        cout << "Please select an option:\n";
        cout << "1. Load Course Data\n";
        cout << "2. Print Course List\n";
        cout << "3. Print Course Information\n";
        cout << "9. Exit\n";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the course data file name (e.g., courses.txt): ";
            cin >> filename;
            loadCourses(filename, courses);
            break;
        case 2:
            printCourses(courses);
            break;
        case 3: {
            cout << "Enter the course ID (e.g., CSCI101): ";
            string courseID;
            cin >> courseID;
            printCourseInfo(courses, courseID);
            break;
        }
        case 9:
            cout << "Exiting the program.\n";
            return 0;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    }
}

void loadCourses(const string& filename, vector<Course>& courses) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << "\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Course course;
        getline(ss, course.courseID, ','); // Read course ID
        getline(ss, course.title, ','); // Read course title

        string prereqs;
        while (getline(ss, prereqs, ',')) { // Read prerequisites
            if (!prereqs.empty()) {
                course.prerequisites.push_back(prereqs);
            }
        }

        courses.push_back(course); // Add course to the list
    }
    file.close();
    cout << "Courses loaded successfully from " << filename << ".\n"; // Confirmation message
}

void printCourses(const vector<Course>& courses) {
    if (courses.empty()) {
        cout << "No courses available. Please load data first.\n";
        return;
    }

    vector<Course> sortedCourses = courses; // Copy to sort
    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.courseID < b.courseID; // Sort by course ID
        });

    cout << "Course List:\n";
    for (const auto& course : sortedCourses) {
        cout << course.courseID << ": " << course.title << "\n";
    }
}

void printCourseInfo(const vector<Course>& courses, const string& courseID) {
    auto it = find_if(courses.begin(), courses.end(), [&courseID](const Course& course) {
        return course.courseID == courseID; // Search for course by ID
        });

    if (it != courses.end()) {
        it->printInfo(); // Print the course details
    }
    else {
        cout << "Course ID " << courseID << " not found.\n";
    }
}