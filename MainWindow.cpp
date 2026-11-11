#include "MainWindow.h"

#include <QApplication>
#include <QDoubleValidator>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      m_file(QApplication::applicationDirPath() + "/students.txt")
{
    setWindowTitle("Student Record Management System");
    resize(1000, 700);
    buildUi();
    applyStyle();
    setAddMode();                         // startup: Add enabled, Update/Delete disabled
}

// ---------------------------------------------------------------- UI

QLineEdit *MainWindow::makeField(const QString &placeholder)
{
    auto *e = new QLineEdit;
    e->setPlaceholderText(placeholder);
    e->setMinimumHeight(44);
    return e;
}

void MainWindow::buildUi()
{
    // Page title
    auto *title = new QLabel("Student Record Management System");
    title->setObjectName("pageTitle");
    title->setAlignment(Qt::AlignCenter);

    // Card
    auto *card = new QWidget;
    card->setObjectName("card");
    card->setFixedWidth(432);

    auto *header = new QLabel("Student Information");
    header->setObjectName("cardHeader");
    header->setAlignment(Qt::AlignCenter);
    header->setFixedHeight(52);

    m_name     = makeField("Enter name");
    m_roll     = makeField("Enter roll number");
    m_father   = makeField("Enter father's name");
    m_caste    = makeField("Enter caste");
    m_district = makeField("Enter district");
    m_gpa      = makeField("Enter GPA");

    auto label = [](const QString &t) {
        auto *l = new QLabel(t);
        l->setObjectName("fieldLabel");
        return l;
    };

    auto *form = new QGridLayout;
    form->setHorizontalSpacing(25);
    form->setVerticalSpacing(6);
    form->addWidget(label("Name:"),          0, 0);
    form->addWidget(label("Roll Number:"),   0, 1);
    form->addWidget(m_name,                  1, 0);
    form->addWidget(m_roll,                  1, 1);
    form->addWidget(label("Father's Name:"), 2, 0);
    form->addWidget(label("Caste:"),         2, 1);
    form->addWidget(m_father,                3, 0);
    form->addWidget(m_caste,                 3, 1);
    form->addWidget(label("District:"),      4, 0);
    form->addWidget(label("GPA:"),           4, 1);
    form->addWidget(m_district,              5, 0);
    form->addWidget(m_gpa,                   5, 1);
    form->setRowMinimumHeight(2, 30);
    form->setRowMinimumHeight(4, 30);

    m_addBtn    = new QPushButton("Add");
    m_updateBtn = new QPushButton("Update");
    m_deleteBtn = new QPushButton("Delete");
    m_nextBtn   = new QPushButton("Next");
    for (auto *b : {m_addBtn, m_updateBtn, m_deleteBtn, m_nextBtn}) {
        b->setMinimumHeight(44);
        b->setCursor(Qt::PointingHandCursor);
    }

    auto *buttons = new QGridLayout;
    buttons->setHorizontalSpacing(15);
    buttons->setVerticalSpacing(15);
    buttons->addWidget(m_addBtn,    0, 0);
    buttons->addWidget(m_updateBtn, 0, 1);
    buttons->addWidget(m_deleteBtn, 1, 0);
    buttons->addWidget(m_nextBtn,   1, 1);

    auto *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(30, 25, 30, 30);
    cardLayout->setSpacing(18);
    cardLayout->addWidget(header);
    cardLayout->addLayout(form);
    cardLayout->addLayout(buttons);

    // Page layout: title on top, card centred
    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(20, 40, 20, 20);
    root->addWidget(title);
    root->addSpacing(40);
    root->addWidget(card, 0, Qt::AlignHCenter);
    root->addStretch();

    connect(m_addBtn,    &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(m_updateBtn, &QPushButton::clicked, this, &MainWindow::onUpdateClicked);
    connect(m_deleteBtn, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);
    connect(m_nextBtn,   &QPushButton::clicked, this, &MainWindow::onNextClicked);
}

void MainWindow::applyStyle()
{
    setStyleSheet(R"(
        MainWindow { background: #dde9dc; }
        QLabel#pageTitle { color: #064e3b; font-size: 26px; font-weight: bold; }
        QWidget#card { background: #eff5ee; border-radius: 14px; }
        QLabel#cardHeader {
            background: #03503c; color: white;
            font-size: 18px; font-weight: bold; border-radius: 8px;
        }
        QLabel#fieldLabel { color: #1f2937; font-size: 13px; font-weight: bold; }
        QLineEdit {
            background: white; color: #111827;
            border: 1px solid #c3cfc3; border-radius: 8px;
            padding: 0 12px; font-size: 13px;
        }
        QLineEdit:focus { border: 2px solid #0f9d78; }
        QLineEdit:read-only { background: #e6ece5; color: #4b5563; }
        QPushButton {
            background: #bfbfbf; color: #1f2937;
            border: none; border-radius: 8px;
            font-size: 15px; font-weight: bold;
        }
        QPushButton:hover:enabled { background: #a9c9b9; }
        QPushButton:pressed:enabled { background: #8fb9a3; }
        QPushButton:disabled { background: #bfbfbf; color: #7b7b7b; }
    )");
}

// ----------------------------------------------------- mode handling

void MainWindow::setAddMode()
{
    m_index = -1;
    clearFields();
    m_roll->setReadOnly(false);
    m_addBtn->setEnabled(true);
    m_updateBtn->setEnabled(false);
    m_deleteBtn->setEnabled(false);
    m_name->setFocus();
}

void MainWindow::setBrowseMode()
{
    // Roll number is the unique identifier, so it cannot be edited here.
    m_roll->setReadOnly(true);
    m_addBtn->setEnabled(false);
    m_updateBtn->setEnabled(true);
    m_deleteBtn->setEnabled(true);
}

void MainWindow::showStudent(const Student &s)
{
    m_name->setText(s.name);
    m_roll->setText(s.rollNumber);
    m_father->setText(s.fatherName);
    m_caste->setText(s.caste);
    m_district->setText(s.district);
    m_gpa->setText(s.gpa);
}

void MainWindow::clearFields()
{
    for (auto *e : {m_name, m_roll, m_father, m_caste, m_district, m_gpa})
        e->clear();
}

// ------------------------------------------------------- validation

// Text must not contain commas (they separate the fields in the file).
bool MainWindow::isValidText(const QString &t)
{
    return !t.contains(',');
}

bool MainWindow::readStudent(Student &s, QString &error) const
{
    s.name       = m_name->text().trimmed();
    s.rollNumber = m_roll->text().trimmed();
    s.fatherName = m_father->text().trimmed();
    s.caste      = m_caste->text().trimmed();
    s.district   = m_district->text().trimmed();
    s.gpa        = m_gpa->text().trimmed();

    if (s.name.isEmpty() || s.rollNumber.isEmpty() || s.fatherName.isEmpty() ||
        s.caste.isEmpty() || s.district.isEmpty() || s.gpa.isEmpty()) {
        error = "Please fill in all the fields.";
        return false;
    }

    for (const QString &t : {s.name, s.rollNumber, s.fatherName, s.caste, s.district}) {
        if (!isValidText(t)) {
            error = "Commas (,) are not allowed in any field.";
            return false;
        }
    }

    // Names: letters, spaces, dots, hyphens and apostrophes only
    static const QRegularExpression nameRx("^[\\p{L} .'\\-]+$");
    for (const QString &t : {s.name, s.fatherName, s.caste, s.district}) {
        if (!nameRx.match(t).hasMatch()) {
            error = "Name, Father's Name, Caste and District must contain letters only.";
            return false;
        }
    }

    static const QRegularExpression rollRx("^[A-Za-z0-9\\-/]+$");
    if (!rollRx.match(s.rollNumber).hasMatch()) {
        error = "Roll Number may contain only letters, digits, '-' and '/' (no spaces).";
        return false;
    }

    bool ok = false;
    const double g = s.gpa.toDouble(&ok);
    if (!ok || g < 0.0 || g > 4.0) {
        error = "GPA must be a number between 0.0 and 4.0.";
        return false;
    }
    s.gpa = QString::number(g, 'f', 2);   // store in a consistent format
    return true;
}

// ----------------------------------------------------------- slots

void MainWindow::onAddClicked()
{
    Student s;
    QString error;
    if (!readStudent(s, error)) {
        QMessageBox::warning(this, "Invalid Input", error);
        return;
    }
    if (m_file.exists(s.rollNumber)) {
        QMessageBox::warning(this, "Duplicate Roll Number",
                             "A student with this Roll Number already exists.");
        return;
    }
    if (!m_file.append(s)) {
        QMessageBox::critical(this, "File Error", "Could not write to the records file.");
        return;
    }
    QMessageBox::information(this, "Success", "Student record added successfully.");
    setAddMode();                          // ready for the next entry
}

void MainWindow::onNextClicked()
{
    const QList<Student> all = m_file.loadAll();
    if (all.isEmpty()) {
        QMessageBox::information(this, "No Records", "There are no student records yet.");
        setAddMode();
        return;
    }

    ++m_index;
    if (m_index >= all.size()) {
        // Reached the end of the file: go back to blank form / Add mode.
        QMessageBox::information(this, "End of Records",
                                 "You have reached the end of the records.");
        setAddMode();
        return;
    }
    showStudent(all[m_index]);
    setBrowseMode();
}

void MainWindow::onUpdateClicked()
{
    Student s;
    QString error;
    if (!readStudent(s, error)) {
        QMessageBox::warning(this, "Invalid Input", error);
        return;
    }
    if (!m_file.update(s)) {                // matched by Roll Number
        QMessageBox::critical(this, "Update Failed", "Could not update this record.");
        return;
    }
    QMessageBox::information(this, "Success", "Student record updated successfully.");
}

void MainWindow::onDeleteClicked()
{
    const QString roll = m_roll->text().trimmed();
    const auto answer = QMessageBox::question(
        this, "Confirm Delete",
        QString("Delete the record of roll number %1?").arg(roll),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (answer != QMessageBox::Yes)
        return;

    if (!m_file.remove(roll)) {
        QMessageBox::critical(this, "Delete Failed", "Could not delete this record.");
        return;
    }
    QMessageBox::information(this, "Success", "Student record deleted successfully.");

    // Show the record that moved into this position, or go back to Add mode.
    const QList<Student> all = m_file.loadAll();
    if (m_index < all.size()) {
        showStudent(all[m_index]);
        setBrowseMode();
    } else {
        setAddMode();
    }
}
