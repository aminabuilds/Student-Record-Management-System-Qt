# Student Record Management System (C++ / Qt)

GUI application (Qt Widgets) to add, update, delete and browse student records.
Records are stored in `students.txt` (next to the .exe), comma separated:

    Name,RollNumber,FatherName,Caste,District,GPA

## Files
| File | Purpose |
|---|---|
| `main.cpp` | Program entry point |
| `MainWindow.h/.cpp` | GUI, button events, validation |
| `StudentFile.h/.cpp` | All file handling (load, append, update, remove) |
| `Student.h` | Student record structure |

## Build & run
**Qt Creator (easiest):** install Qt 6 (or 5) -> File > Open Project -> `CMakeLists.txt` (or `StudentRecordSystem.pro`) -> Run.

**Command line:**
    cmake -B build && cmake --build build

## Behaviour
- Start: Add enabled, Update/Delete disabled.
- Add: validates, saves to file, shows confirmation, clears the form.
- Next: shows next record; Add disabled, Update/Delete enabled. After the last record it returns to the blank Add mode.
- Update: changes the displayed record, matched by Roll Number (Roll Number is locked while browsing).
- Delete: asks for confirmation, removes the record.

## Extra features (creativity)
Input validation (empty fields, commas, letters-only names, GPA 0-4), duplicate roll number check, delete confirmation, themed UI.
