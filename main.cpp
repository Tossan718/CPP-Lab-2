/**
 * Tossan Azhar
 * 041161657
 * Lab 3
 * CST8219 - C++ Programming
 */

#include "Student.h"
#include <iomanip>
#include <iostream>
#include <memory>

#define IGNORED_CHARS 1000

using namespace std;

/**
 * @brief Clears the input buffer to handle invalid input.
 */
void clearInputBuffer() {
  cin.clear();                     // Clear the error state
  cin.ignore(IGNORED_CHARS, '\n'); // Ignore the rest of the line
}

/**
 * @brief Trims whitespace from both ends of a string.
 *
 * @param str The string to be trimmed.
 */
void trimString(string &str) {
  /* Lambda function to trim whitespace from both ends of the string */
  if (str.empty())
    return;
  str.erase(0, str.find_first_not_of(" \t\n\r\f\v")); // Left trim
  str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1); // Right trim
}

/**
 * @brief Checks if a student ID already exists in the array of students.
 *
 * @param students The unique pointer to the array of Student objects.
 * @param numStudents The number of students in the array.
 * @param id The student ID to check for uniqueness.
 * @return true if the ID exists, false otherwise.
 */
bool uid(const unique_ptr<Student[]> &students, int count, int id) {
  for (int i = 0; i < count; i++) {
    if (students[i].getId() == id) {
      return false; // ID already exists
    }
  }
  return true;
}

/**
 * @brief Prompts the user to input student details and returns a Student
 * object.
 * @param students The unique pointer to the array of Student objects.
 * @param count The number of students in the array.
 * @return A Student object with the provided details.
 */
Student inputStudent(const unique_ptr<Student[]> &students, int count) {
  int id = 0;
  string temp;
  string name;
  float marksArray[3] = {0, 0, 0};

  while (true) {
    cout << "Enter student ID: ";
    getline(cin, temp);
    trimString(temp);
    if (temp.empty()) {
      cout << "Student ID cannot be empty. Please enter a valid ID.\n";
      continue;
    }
    try {
      id = stoi(temp);
    } catch (...) {
      cout << "Invalid input. Please enter a valid integer for student ID.\n";
      continue;
    }
    if (id <= 0) {
      cout << "Enter a positive ID number.\n";
      continue;
    }
    if (!uid(students, count, id)) {
      cout << "Error: ID " << id << " already exists!\n";
      continue;
    }
    break;
  }
  while (true) {
    cout << "Enter student name: ";
    getline(cin, name);
    trimString(name);
    if (name.empty()) {
      cout << "Student name cannot be empty. Please enter a valid name.\n";
      continue;
    }
    break;
  }
  for (int i = 0; i < 3; i++) {
    while (true) {
      cout << "Enter marks for subject " << i + 1 << ": ";
      getline(cin, temp);
      trimString(temp);
      if (temp.empty()) {
        cout << "Marks cannot be empty. Please enter a valid mark.\n";
        continue;
      }
      try {
        marksArray[i] = stof(temp);
        if (marksArray[i] < 0 || marksArray[i] > 100) {
          cout << "Marks must be between 0 and 100. Please enter a valid "
                  "mark.\n";
          continue;
        }
      } catch (...) {
        cout << "Invalid input. Please enter a valid number for marks.\n";
        continue;
      }
      break;
    }
  }
  // Return a valid Student object after successful input
  return Student(id, name, marksArray);
}

void appendStudent(unique_ptr<Student[]> &students, int &count,
                   Student newStudent) {
  // Create a new array with one additional slot
  unique_ptr<Student[]> newArray = make_unique<Student[]>(count + 1);

  // Copy existing students to the new array
  for (int i = 0; i < count; i++) {
    newArray[i] = move(students[i]);
  }

  // Add the new student to the end of the new array
  newArray[count] = move(newStudent);

  // Update the unique_ptr to point to the new array
  students = move(newArray);

  // Increment the count of students
  count++;
  cout << "Student added successfully!\n";
  cout << " Total students: " << count << endl;
}

/**
 * @brief Displays all student records in the array.
 *
 * @param students The unique pointer to the array of Student objects.
 * @param count The number of students in the array.
 */
void displayAll(const unique_ptr<Student[]> &students, int count) {
  if (count == 0) {
    cout << "No students added yet.\n";
    return;
  }
  for (int i = 0; i < count; ++i) {
    students[i].display(); // Calls the virtual display() function
  }
}

/**
 * @brief Finds and displays the student with the highest average score.
 *
 * @param students The unique pointer to the array of Student objects.
 * @param count The number of students in the array.
 */
void findSmartest(const unique_ptr<Student[]> &students, int count) {
  if (count == 0) {
    cout << "No students to compare.\n";
    return;
  }
  int smartestIndex = 0;
  for (int i = 1; i < count; ++i) {
    if (students[i].getAverage() > students[smartestIndex].getAverage()) {
      smartestIndex = i;
    }
  }
  cout << "\n--- Highest Scoring Student ---\n";
  students[smartestIndex].display();
}

/**
 * @brief Displays a summary of the class, including total students, class
 * average, and number of students who passed.
 *
 * @param students The unique pointer to the array of Student objects.
 * @param count The number of students in the array.
 */
void displaySummary(const unique_ptr<Student[]> &students, int count) {
  if (count == 0) {
    cout << "No students to summarize.\n";
    return;
  }

  float classTotal = 0.0f;
  int passed = 0;
  for (int i = 0; i < count; ++i) {
    classTotal += students[i].getAverage();
    if (students[i].getStatus() == PASS) {
      passed++;
    }
  }
  cout << "\n--- Class Summary ---\n";
  cout << "Total Students: " << count << "\n";
  cout << fixed << setprecision(2);
  cout << "Class Average: " << (classTotal / count) << "\n";
  cout << "Students Passed: " << passed << "\n";
}

int main() {
  unique_ptr<Student[]> students;
  int numStudents = 0;
  int choice = 0;

  while (true) {

    cout << "\n===== Student Management System ===== \n";
    cout << "1. Add student records\n";
    cout << "2. Display all students\n";
    cout << "3. Find highest scoring student\n";
    cout << "4. Display class summary\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";

    if (!(cin >> choice)) {
      cout << "Invalid input. Please enter a number.\n";
      clearInputBuffer();
      continue;
    }
    clearInputBuffer(); // Clear the newline character left in the buffer

    switch (choice) {
    case 1: {
      int n;
      string temp;

      cout << "Enter number of students: ";
      while (true) {
        getline(cin, temp);
        trimString(temp);
        if (temp.empty()) {
          cout << "Number of students cannot be empty.\nEnter number: ";
          continue;
        }
        try {
          n = stoi(temp);
        } catch (...) {
          cout << "Invalid input. Enter a valid integer.\nEnter number: ";
          continue;
        }
        if (n <= 0) {
          cout << "Please enter a positive integer.\nEnter number: ";
          continue;
        }
        if (n > 50) {
          cout << "Limit is 50.\nEnter number: ";
          continue;
        }
        break;
      }

      for (int i = 0; i < n; i++) {
        cout << "\n --- Student " << i + 1 << " --- \n";

        Student s = inputStudent(students, numStudents);
        appendStudent(students, numStudents, move(s));
      }
      break;
    }
    case 2:
      displayAll(students, numStudents);
      break;
    case 3:
      findSmartest(students, numStudents);
      break;
    case 4:
      displaySummary(students, numStudents);
      break;
    case 5:
      cout << "\n..... Exiting program .....\n";
      return 0;
    default:
      cout << "\nInvalid choice. Please enter a number between 1 and 5.\n";
      break;
    }
  }
  return 0;
}
