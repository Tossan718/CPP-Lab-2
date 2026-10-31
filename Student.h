/**
 * Tossan Azhar
 * 041161657
 * Lab 3
 * CST8219 - C++ Programming
 *
 */
#ifndef STUDENT_H
#define STUDENT_H

#include <fstream>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>


#define IGNORED_CHARS 1000

/* unscoped enum */
enum Status { PASS, FAIL };

/* scoped enum */
enum class Grade { A, B, C, D, F };

// Constants value must be computable at compile time, so we use constexpr
constexpr int NUM_SUBJECTS = 3;
constexpr float PASSING_AVERAGE = 50.0f;

// Global variable to keep track of total students
static int totalStudents = 0;
/* extern variable*/
// extern bool fileWriteSuccess;
//  Class to hold student data
class Student {
  /* private access specifier */
private:
  /* Use default member initializer for id */
  int id;
  std::string name;
  /* Use unique_ptr for dynamic array of marks, exclusive ownership to Student*/
  std::unique_ptr<float[]> marks;
  float total;
  float average;
  Status status;
  Grade grade;

  static constexpr int SUBJECTS = 3; // Number of subjects
  // public access specifier
public:
  /** Default constructor */
  Student();
};

// Function prototypes
void inputStudent(Student &s);
void calculateResults(Student &s);
void displayStudent(const Student &s);

// File-related function prototypes (to be implemented by you)
/* unique_ptr for dynamic array of students*/
void loadStudents(std::unique_ptr<Student[]> &students, int &count);
void writeStudentsToFile(Student *students, int n, const std::string &filename);
void readStudentsFromFile(Student *students, int &count,
                          const std::string &filename);
void smartestStudent(Student *students, int n);
void summary(const Student *students, int n);

#endif
