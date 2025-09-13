# Employee Record Management System (C Project)

This is a simple **Employee Record Management System** built in C.  
It allows users to manage employee data, perform operations like adding, deleting, modifying records, and generate salary breakdown reports.

---

## 📂 Project Structure
- `main.c` → Entry point with menu-driven interface.
- `employee.c / employee.h` → Functions and structures to handle employee records.
- `salaries.c / salaries.h` → Functions to calculate salary components.
- `records.txt` → Sample dataset containing employee records.

---

## ✨ Features
- Add new employee records (with validation for unique IDs).
- Delete or modify existing records.
- Search employees by ID or filter by:
  - ID range
  - Designation
  - Date of joining
  - Salary range
  - Probation period
- Sort records by ID, Name, Joining Date, Salary, or Probation.
- Display all records in a formatted table.
- Generate detailed salary breakdown reports.
- Check which employees complete probation **today**.

---
