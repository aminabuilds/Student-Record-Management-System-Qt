#include "StudentFile.h"

#include <QFile>
#include <QTextStream>

StudentFile::StudentFile(const QString &path) : m_path(path) {}

// Convert a Student into one CSV line.
QString StudentFile::toLine(const Student &s)
{
    return QStringList{ s.name, s.rollNumber, s.fatherName,
                        s.caste, s.district, s.gpa }.join(',');
}

// Convert one CSV line into a Student. Returns false for malformed lines.
bool StudentFile::fromLine(const QString &line, Student &out)
{
    const QStringList f = line.split(',');
    if (f.size() != 6)
        return false;
    out.name       = f[0].trimmed();
    out.rollNumber = f[1].trimmed();
    out.fatherName = f[2].trimmed();
    out.caste      = f[3].trimmed();
    out.district   = f[4].trimmed();
    out.gpa        = f[5].trimmed();
    return true;
}

QList<Student> StudentFile::loadAll() const
{
    QList<Student> list;
    QFile file(m_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return list;                       // file not created yet -> no records

    QTextStream in(&file);
    while (!in.atEnd()) {
        const QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;
        Student s;
        if (fromLine(line, s))
            list.append(s);
    }
    return list;
}

bool StudentFile::saveAll(const QList<Student> &students) const
{
    QFile file(m_path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return false;

    QTextStream out(&file);
    for (const Student &s : students)
        out << toLine(s) << '\n';
    return true;
}

bool StudentFile::append(const Student &s) const
{
    QFile file(m_path);
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return false;
    QTextStream out(&file);
    out << toLine(s) << '\n';
    return true;
}

bool StudentFile::exists(const QString &rollNumber) const
{
    for (const Student &s : loadAll())
        if (s.rollNumber.compare(rollNumber, Qt::CaseInsensitive) == 0)
            return true;
    return false;
}

bool StudentFile::update(const Student &s) const
{
    QList<Student> all = loadAll();
    for (Student &rec : all) {
        if (rec.rollNumber.compare(s.rollNumber, Qt::CaseInsensitive) == 0) {
            rec = s;
            return saveAll(all);
        }
    }
    return false;                           // roll number not found
}

bool StudentFile::remove(const QString &rollNumber) const
{
    QList<Student> all = loadAll();
    for (int i = 0; i < all.size(); ++i) {
        if (all[i].rollNumber.compare(rollNumber, Qt::CaseInsensitive) == 0) {
            all.removeAt(i);
            return saveAll(all);
        }
    }
    return false;
}
