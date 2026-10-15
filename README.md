Tossan Azhar 
041161657

# 📘 Student Management System  
A simple C++ console application for managing student records, calculating grades, validating input, and saving/loading data in a tidy fixed‑width table format.

---

## ✨ Features

### 🔹 Add Students  
- Enter **ID**, **Name**, and **Marks** for 3 subjects  
- Full input validation  
- Whitespace trimming  
- Duplicate ID detection  
- Marks must be between **0–100**

### 🔹 Automatic Calculations  
For each student:
- Total marks  
- Average  
- Letter grade (A–F)  
- PASS/FAIL status  

### 🔹 Display Students  
- Clean, readable console output  
- Shows all student details  
- Uses consistent formatting

### 🔹 Save to File  
Writes data in a tidy fixed‑width table:

```
ID   | Name        | Marks              | Average | Grade | Status
-----+--------------+-------------------+--------+-------+--------
101  | Alice       | 85, 90, 95         | 90.00   | A     | PASS
```

### 🔹 Load from File  
Reads saved student data back into the program.

---

## 📂 File Format

The saved file uses fixed‑width columns:

```
ID   | Name        | Marks              | Average | Grade | Status
-----+--------------+-------------------+--------+-------+--------
101  | Alice       | 85, 90, 95         | 90.00   | A     | PASS
```

This makes the file:
- human‑readable  
- easy to parse  
- consistent across runs  

---

## 🧠 Input Validation

The program ensures:
- IDs are positive integers  
- Names are non‑empty  
- Marks are valid floats  
- Marks are within 0–100  
- Duplicate IDs are rejected  
- Whitespace is trimmed from all inputs  

All input is read using `std::getline()` to avoid buffer issues.

---

## 🛠️ Technologies Used

- **C++17**  
- `std::unique_ptr` for safe dynamic memory  
- `std::setw`, `std::left`, `std::fixed` for tidy formatting  
- `std::set` for tracking unique IDs  
- `std::ofstream` / `std::ifstream` for file I/O  

---

## 🚀 How to Compile

If your project has multiple `.cpp` files:

```
g++ main.cpp Student.cpp -o student_app
```

Or if everything is in one file:

```
g++ main.cpp -o student_app
```

Run the program:

```
./student_app
```

---

## 📌 Project Structure (example)

```
/StudentManagement
│
├── main.cpp
├── Student.h
├── Student.cpp
├── README.md
└── students.txt
```
