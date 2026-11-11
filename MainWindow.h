#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Student.h"
#include "StudentFile.h"

#include <QWidget>

class QLineEdit;
class QPushButton;

// Main (and only) window of the Student Record Management System.
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onAddClicked();
    void onUpdateClicked();
    void onDeleteClicked();
    void onNextClicked();

private:
    // ---- UI building ----
    void buildUi();
    QLineEdit *makeField(const QString &placeholder);
    void applyStyle();

    // ---- helpers ----
    void setAddMode();                    // blank form, Add enabled
    void setBrowseMode();                 // record shown, Update/Delete enabled
    void showStudent(const Student &s);
    void clearFields();
    bool readStudent(Student &out, QString &error) const;
    static bool isValidText(const QString &t);

    // ---- widgets ----
    QLineEdit *m_name;
    QLineEdit *m_roll;
    QLineEdit *m_father;
    QLineEdit *m_caste;
    QLineEdit *m_district;
    QLineEdit *m_gpa;
    QPushButton *m_addBtn;
    QPushButton *m_updateBtn;
    QPushButton *m_deleteBtn;
    QPushButton *m_nextBtn;

    // ---- data ----
    StudentFile m_file;
    int m_index = -1;                     // index of record currently shown (-1 = none)
};

#endif // MAINWINDOW_H
