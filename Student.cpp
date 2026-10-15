/**
* Tossan Azhar
* 041161657
* Lab 2
* CST8219 - C++ Programming
*/

#include "Student.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <set>
#include <sstream>  

bool fileWriteSuccess = false; // Volatile variable to indicate file write success condition can be changed

void inputStudent(Student& s) {
    /* Static set to track existing IDs to ensure uniqueness */
    static std::set<int> existingIDs; // Set to track existing IDs

    std::cout << "Enter ID: ";
    std::string temp;
    while (true) {

        std::getline(std::cin, temp);
        /* trim whitespace input for ID */
        auto trim = [](std::string& str) {
            /* Anonymous function for trim */
            str.erase(0, str.find_first_not_of(" \t\n\r\f\v")); // Left trim
            str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1); // Right trim
            };
        trim(temp);

        if (temp.empty()) {
            std::cout << "ID cannot be empty. Please enter a valid ID.\n" << std::endl;
            std::cout << "Enter ID: ";
            continue; // Skip to the next iteration to re-prompt for input
        }
        /* Convert trimmed string to integer*/
        try {
            s.id = std::stoi(temp);
        }
        catch (const std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a valid integer for ID.\n" << std::endl;
            std::cout << "Enter ID: ";
            continue;  // Skip to the next iteration to re-prompt for input
        }
        if (s.id <= 0) {
            std::cout << "Invalid input. Please enter a positive integer for ID.\n" << std::endl;
            std::cout << "Enter ID: ";
            continue; // Skip to the next iteration to re-prompt for input
        }

        if (existingIDs.count(s.id)) {
            std::cout << "ID already exists. Please enter a unique ID.\n" << std::endl;
			std::cout << "Enter ID: ";
            continue; // Skip to the next iteration to re-prompt for input
        }
        existingIDs.insert(s.id); // Add the new ID to the set
        break; // Valid input, exit the loop
    }
       
    std::cout << "Enter Name: ";
    while(true){
    std::getline(std::cin, s.name); // Read the full name including spaces
    auto trim = [](std::string& str) {
		/* Lambda function to trim whitespace from both ends of the string */
        str.erase(0, str.find_first_not_of(" \t\n\r\f\v")); // Left trim
        str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1); // Right trim
        };
    trim(s.name);
    if (s.name.empty()) {
        std::cout << "Name cannot be empty. Please enter a valid name: .\n" << std::endl;
        std::cout << "Enter Name: ";
        continue;
    }
    break; // Valid input, exit the loop
}
    /* Allocate memory for marks */
    s.marks = std::make_unique<float[]>(NUM_SUBJECTS);

    for (int i = 0; i < NUM_SUBJECTS; i++) {
        while (true) {
            std::cout << "Enter marks for subject " << i + 1 << ": ";
            std::string temp;
			std::getline(std::cin, temp);
			auto trim = [](std::string& str) {
				str.erase(0, str.find_first_not_of(" \t\n\r\f\v")); // Left trim
				str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1); // Right trim
				};
            trim(temp);
			/* Validate if input is empty */
			if (temp.empty()) {
				std::cout << "Marks cannot be empty. Please enter a valid number.\n" << std::endl;
				continue; // Skip to the next iteration to re-prompt for input
			}
            /* validate input */
            float mark{};
            try {
                mark = std::stof(temp);
            } catch (const std::invalid_argument&) {
                std::cout << "Invalid input. Please enter a valid number.\n" << std::endl;
                continue;  // Skip to the next iteration to re-prompt for input
            }
            if (mark < 0 || mark > 100) {
                std::cout << "Invalid input. Please enter a value between 0 and 100.\n" << std::endl;
                continue;  // Skip to the next iteration to re-prompt for input
            }
            s.marks[i] = mark; // store the valid mark in the array
            break;  // Valid input, exit the loop
        }
    }
}

void calculateResults(Student& s) {
    s.total = 0;

    for (int i = 0; i < 3; i++) {
        s.total += s.marks[i];
    }

    s.average = s.total / 3;
}

void displayStudent(const Student& s) {
    std::cout << "ID: " << s.id << '\n';
    std::cout <<"Name: " << s.name << '\n';

    std::cout << "Marks: ";
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        std::cout << s.marks[i] << ", ";
    }

    std::cout << "\nTotal: " << s.total
        << std::fixed << std::setprecision(2)
        << ", \nAverage: " << s.average << std::endl;

    std::cout << "Status: " << (s.average >= 50 ? "PASS" : "FAIL") << std::endl;
}

void smartestStudent(Student* students, int n) {
	int index = 0; /* Smartest student index */


    for (int i = 1; i < n; i++) {
		/* Compare averages to find the highest scorer */
        if (students[i].average > students[index].average) {
            index = i;
        }
    }

    std::cout << "\nHighest Scorer:\n\n";
    displayStudent(students[index]);
}

void writeStudentsToFile(Student* students, int n, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::out);

    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    // Tidy fixed-width header
    outFile << std::left
        /* setw for fixed-width columns */
        << std::setw(5) << "ID" << " | "
        << std::setw(12) << "Name" << " | "
        << std::setw(24) << "Marks" << " | "
        << std::setw(7) << "Average" << " | "
        << std::setw(6) << "Grade" << " | "
        << "Status" << "\n";

    // Separator line
    outFile << "-----+--------------+-------------------------------+-------+-------+--------\n";

    for (int i = 0; i < n; ++i) {

        // Build marks string: "m1, m2, m3"
        std::string marksStr =
            std::to_string(students[i].marks[0]) + ", " +
            std::to_string(students[i].marks[1]) + ", " +
            std::to_string(students[i].marks[2]);

        // Determine grade
        char grade;
        if (students[i].average >= 80) grade = 'A';
        else if (students[i].average >= 70) grade = 'B';
        else if (students[i].average >= 60) grade = 'C';
        else if (students[i].average >= 50) grade = 'D';
        else grade = 'F';

        // Determine pass/fail status
        std::string status = (students[i].average >= PASSING_AVERAGE) ? "PASS" : "FAIL";

        // Write formatted row
        outFile << std::left
            << std::setw(5) << students[i].id << " | "
            << std::setw(12) << students[i].name << " | "
            << std::setw(19) << marksStr << " | "
            << std::setw(7) << std::fixed << std::setprecision(2) << students[i].average << " | "
            << std::setw(6) << grade << " | "
            << status << "\n";
    }

    outFile.close();
    std::cout << "\nData saved to " << filename << "\n\n";
}



void readStudentsFromFile(Student* students, int& count, const std::string& filename) {
    std::ifstream inFile(filename);

    if (!inFile) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    std::string line;

    // Skip header line
    std::getline(inFile, line);

    int idx = 0;

    while (idx < count && std::getline(inFile, line)) {

        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string part;

        // Helper trim lambda
        auto trim = [](std::string& s) {
            s.erase(0, s.find_first_not_of(" \t\n\r\f\v"));
            s.erase(s.find_last_not_of(" \t\n\r\f\v") + 1);
            };

        // Split by '|'
        std::string fields[6];
        int f = 0;

        while (std::getline(ss, part, '|') && f < 6) {
            trim(part);
            fields[f++] = part;
        }

        if (f < 6) continue; // malformed line

        // Parse ID
        students[idx].id = std::stoi(fields[0]);

        // Parse Name
        students[idx].name = fields[1];

        // Parse marks: "85, 90, 95"
        std::stringstream marksStream(fields[2]);
        std::string markStr;
        int m = 0;

        students[idx].marks = std::make_unique<float[]>(NUM_SUBJECTS);

        while (std::getline(marksStream, markStr, ',') && m < NUM_SUBJECTS) {
            trim(markStr);
            students[idx].marks[m++] = std::stof(markStr);
        }

        // Parse average
        students[idx].average = std::stof(fields[3]);

        // Recalculate total
        students[idx].total = 0;
        for (int i = 0; i < NUM_SUBJECTS; i++) {
            students[idx].total += students[idx].marks[i];
        }

        idx++;
    }

    count = idx;

    std::cout << "\nLoaded data from file:\n\n";

    for (int i = 0; i < count; i++) {
        displayStudent(students[i]);
        std::cout << std::endl;
    }
}



void summary(const Student* students, int n) {
    int passCount = 0;
	int failCount = 0;
	for (int i = 0; i < n; i++) {
		if (students[i].average >= PASSING_AVERAGE) {
			passCount++;
		}
		else {
			failCount++;
		}
	}
	std::cout << "\nSummary:\n";
	std::cout << "Total Students: " << n << "\n";
	std::cout << "Passed: " << passCount << " out of " << n << "\n";
	std::cout << "Failed: " << failCount << " out of " << n << "\n";

}
