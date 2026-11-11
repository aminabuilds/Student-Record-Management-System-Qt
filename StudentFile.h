#ifndef STUDENTFILE_H
#define STUDENTFILE_H

#include "Student.h"
#include <QList>
#include <QString>

// Handles all reading/writing of the comma-separated text file.
// File format (one record per line):
//   Name,RollNumber,FatherName,Caste,District,GPA
class StudentFile
{
public:
    explicit StudentFile(const QString &path);

    QList<Student> loadAll() const;                    // read every record
    bool saveAll(const QList<Student> &students) const; // overwrite the file

    bool append(const Student &s) const;                // add one record
    bool exists(const QString &rollNumber) const;       // roll number already used?
    bool update(const Student &s) const;                // replace record with same roll no.
    bool remove(const QString &rollNumber) const;       // delete record by roll no.

    QString path() const { return m_path; }

private:
    static QString toLine(const Student &s);
    static bool fromLine(const QString &line, Student &out);

    QString m_path;
};

#endif // STUDENTFILE_H
