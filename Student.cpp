/**
 * Tossan Azhar
 * 041161657
 * CST8219 - C++ Programming Lab 3
 */

#include "Student.h"
#include <initializer_list>
#include <iomanip>
#include <iostream>

using namespace std;



// ========== Constructors ==========

// Default Constructor
Student::Student()
    : id(0), name("N/A"), marks(make_unique<float[]>(NUM_SUBJECTS)),
      total(0.0f), average(0.0f), status(FAIL), grade(Grade::F) {
  for (int i = 0; i < NUM_SUBJECTS; ++i) {
    marks[i] = 0.0f;
  }
}

// Parameterized Constructor
Student::Student(int id, const string &name, const float *marksArray)
    : id(id), name(name), marks(make_unique<float[]>(NUM_SUBJECTS)),
      total(0.0f), average(0.0f), status(FAIL), grade(Grade::F) {
  for (int i = 0; i < NUM_SUBJECTS; ++i) {
    marks[i] = marksArray[i];
  }
  calculateResults();
}

// Initializer List Constructor
Student::Student(int id, const string &name, initializer_list<float> marksList)
    : id(id), name(name), marks(make_unique<float[]>(NUM_SUBJECTS)),
      total(0.0f), average(0.0f), status(FAIL), grade(Grade::F) {
  int i = 0;
  for (float mark : marksList) {
    if (i < NUM_SUBJECTS)
      marks[i++] = mark;
  }
  calculateResults();
}

// Delegating Constructor
Student::Student(int id) : Student() { this->id = id; }

// Copy Constructor (Deep Copy)
Student::Student(const Student &other)
    : id(other.id), name(other.name), marks(make_unique<float[]>(NUM_SUBJECTS)),
      total(other.total), average(other.average), status(other.status),
      grade(other.grade) {
  for (int i = 0; i < NUM_SUBJECTS; ++i) {
    marks[i] = other.marks[i];
  }
}

// Move Constructor (Transfer resources ownership)
Student::Student(Student &&other) noexcept
    : id(other.id), name(std::move(other.name)), marks(std::move(other.marks)),
      total(other.total), average(other.average), status(other.status),
      grade(other.grade) {
  other.id = 0;
  other.total = 0.0f;
  other.average = 0.0f;
}

// Destructor
Student::~Student() {
  // unique_ptr automatically handles memory deallocation
}

// ========= Assignment Operators ==========

// Copy Assignment Operator (Deep Copy A = B)
Student &Student::operator=(const Student &other) {
  if (this != &other) { // Self-assignment check
    id = other.id;
    name = other.name;
    total = other.total;
    average = other.average;
    status = other.status;
    grade = other.grade;

    // Deep copy of marks
    marks = make_unique<float[]>(NUM_SUBJECTS);
    for (int i = 0; i < NUM_SUBJECTS; ++i) {
      marks[i] = other.marks[i];
    }
  }
  return *this;
}

// Move Assignment (Transfer resources ownership)
Student &Student::operator=(Student &&other) noexcept {
  if (this != &other) { // Self-assignment check
    id = other.id;
    name = std::move(other.name);
    marks = std::move(other.marks);
    total = other.total;
    average = other.average;
    status = other.status;
    grade = other.grade;

    // Reset the moved-from object
    other.id = 0;
    other.total = 0.0f;
    other.average = 0.0f;
  }
  return *this;
}

/**
 * @brief Calculates the total marks of the student using recursion.
 *
 * @param index The current index in the marks array.
 * @return The total marks calculated recursively.
 */
void Student::calculateResults() {
  if (!marks)
    return;

  total = recursiveTotal(0);

  average = total / NUM_SUBJECTS;
  status = (average >= PASSING_AVERAGE) ? PASS : FAIL;

  if (average >= 90) {
    grade = Grade::A;
  } else if (average >= 80) {
    grade = Grade::B;
  } else if (average >= 70) {
    grade = Grade::C;
  } else if (average >= 60) {
    grade = Grade::D;
  } else {
    grade = Grade::F;
  }
}

/**
 * @brief Recursively calculates the total marks of the student.
 *
 * @param index The current index in the marks array.
 * @return The total marks calculated recursively.
 */
float Student::recursiveTotal(int index) const {
  // Base case: no more subjects to add
  if (index == NUM_SUBJECTS)
    return 0.0f;

  // Recursive case: add current mark and move to next
  return marks[index] + recursiveTotal(index + 1);
}

// ======== Overloaded Functions ========

/**
 * @brief Updates the marks of the student and recalculates the results.
 * @param newMarks Pointer to an array of new marks.
 */
void Student::updateMarks(const float *newMarks) {
  for (int i = 0; i < NUM_SUBJECTS; i++)
    marks[i] = newMarks[i];
  calculateResults();
}
/**
 * @brief Updates the marks of the student and recalculates the results.
 *
 * @param m1 The new mark for subject 1.
 * @param m2 The new mark for subject 2.
 * @param m3 The new mark for subject 3.
 */
void Student::updateMarks(float m1, float m2, float m3) {
  marks[0] = m1;
  marks[1] = m2;
  marks[2] = m3;
  calculateResults();
}

// ======== Display Function ========

void Student::display() const {
  cout << "ID: " << id << " | Name: " << name << "\n";
  if (marks) {
    cout << "Marks: " << marks[0] << ", " << marks[1] << ", " << marks[2]
         << "\n";
  } else {
    cout << "Marks: N/A\n";
  }

  cout << fixed << setprecision(2);
  cout << "Total: " << total << " | Average: " << average
       << " | Status: " << (status == PASS ? "PASS" : "FAIL") << " | Grade: ";

  switch (grade) {
  case Grade::A:
    cout << "A\n";
    break;
  case Grade::B:
    cout << "B\n";
    break;
  case Grade::C:
    cout << "C\n";
    break;
  case Grade::D:
    cout << "D\n";
    break;
  case Grade::F:
    cout << "F\n";
    break;
  }
  cout << "-----------------------------\n";
}

// ======== Getters ========

int Student::getId() const { return id; }
string Student::getName() const { return name; }
float Student::getAverage() const { return average; }
Status Student::getStatus() const { return status; }
Grade Student::getGrade() const { return grade; }