#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

// Plain data holder for one student record.
struct Student
{
    QString name;
    QString rollNumber;   // unique identifier
    QString fatherName;
    QString caste;
    QString district;
    QString gpa;
};

#endif // STUDENT_H
