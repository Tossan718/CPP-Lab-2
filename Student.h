/**
 * Tossan Azhar
 * 041161657
 * Lab 3
 * CST8219 - C++ Programming
 */

#ifndef STUDENT_H
#define STUDENT_H

#include <initializer_list>
#include <memory>
#include <string>

using namespace std;
// Unscoped enum for student status
enum Status { PASS, FAIL };

// Scoped preventing conversion enum for student grade
enum class Grade { A, B, C, D, F };

// Constants value must be computable at compile time, so we use constexpr
constexpr float PASSING_AVERAGE = 50.0f;

//  Class to hold student data
class Student {
  // Student data members
private:
  int id;
  string name;
  // Use unique_ptr for dynamic array of marks, exclusive ownership to Student
  unique_ptr<float[]> marks;
  float total;
  float average;
  Status status;
  Grade grade;

  static constexpr int NUM_SUBJECTS = 3; // Number of subjects

public:
  // ===== Constructors =====

  // Default constructor
  Student();
  // Parameterized constructor
  Student(int id, const string &name, const float *marks);
  // Copy constructor
  Student(const Student &other);
  // Move constructor
  Student(Student &&other) noexcept;
  // Initializer list constructor
  Student(int id, const string &name, initializer_list<float> marksList);
  // Delegating constructor
  Student(int id);
  // Destructor
  virtual ~Student();

  // ===== Assignment Operators =====

  // Copy assignment (deep copy)
  Student &operator=(const Student &other);
  // Move assignment
  Student &operator=(Student &&other) noexcept;

  // ===== Member Functions =====

  // Function to calculate total, average, status, and grade
  void calculateResults();
  // Virtual function to display student information
  virtual void display() const;

  // overloaded functions
  void updateMarks(const float *newMarks);
  void updateMarks(float m1, float m2, float m3);

  // Recursive function
  float recursiveTotal(int index) const;

  // ===== Getters =====
  int getId() const;
  string getName() const;
  float getAverage() const;
  Status getStatus() const;
  Grade getGrade() const;
};

#endif
