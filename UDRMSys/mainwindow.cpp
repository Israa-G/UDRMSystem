#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>  // popup windows (like for warning and errors)
#include <QInputDialog> // popup window for input
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), uni("Israa's university")
{
    ui->setupUi(this);
    uni.loadFromFile("udrms_data.txt");
    // connect buttons:
    // student tab:
    connect(ui->btnAddStudent, &QPushButton::clicked, this, &MainWindow::on_btnAddStudent_clicked);
    connect(ui->btnRmStu, &QPushButton::clicked, this, &MainWindow::on_btnRmStu_clicked);
    connect(ui->searchStu, &QLineEdit::textChanged, this, &MainWindow::on_searchStu_textChanged);

    // dorm tab:
    connect(ui->btnAddDorm, &QPushButton::clicked, this, &MainWindow::on_btnAddDorm_clicked);
    connect(ui->btnAddDorm_2, &QPushButton::clicked, this, &MainWindow::on_btnAddDorm_2_clicked);
    // room tab:
    connect(ui->comboDormForRoom, &QComboBox::currentTextChanged, this, &MainWindow::on_comboDormForRoom_currentTextChanged);
    connect(ui->btnAddRoom, &QPushButton::clicked, this, &MainWindow::on_btnAddRoom_clicked);
    connect(ui->btnAssignStudent, &QPushButton::clicked, this, &MainWindow::on_btnAssignStudent_clicked);
    connect(ui->btnRemoveFromRoom, &QPushButton::clicked, this, &MainWindow::on_btnRemoveFromRoom_clicked);

    // resto tab:
    connect(ui->btnOpenResto, &QPushButton::clicked, this, &MainWindow::on_btnOpenResto_clicked);

    // stretch cols of table till it fill the table
    ui->tableStudents->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableDorms->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableRooms->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    log("System start");
}

void MainWindow::log(const QString &msg)
{
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->logBox->append("[" + time + "] " + msg);
}

// students tab:
void MainWindow::on_btnAddStudent_clicked()
{
    StudentDialog dlg(this);
    if (dlg.exec() != QDialog::Accepted)
        return;
    try
    {
        int year = dlg.getYear();

        Student s(dlg.getName().toStdString(), dlg.getId(), year);
        if (!uni.addStudent(s))
        {
            QMessageBox::warning(this, "Duplicate", "Student ID already exists!");
            return;
        }
        int row = ui->tableStudents->rowCount();
        ui->tableStudents->insertRow(row);
        ui->tableStudents->setItem(row, 0, new QTableWidgetItem(QString::number(dlg.getId())));
        ui->tableStudents->setItem(row, 1, new QTableWidgetItem(dlg.getName()));
        ui->tableStudents->setItem(row, 2, new QTableWidgetItem(QString::number(dlg.getYear())));
        log("✔ Added student: " + dlg.getName());
    }

    catch (DormitoryException &e)
    {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_btnRmStu_clicked()
{

    int row = ui->tableStudents->currentRow();
    if (row < 0)
    {
        QMessageBox::information(this, "No selection", "Please select a student first.");
        return;
    }

    long long id = ui->tableStudents->item(row, 0)->text().toLongLong();
    QString name = ui->tableStudents->item(row, 1)->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Remove", "Remove student " + name + " (ID: " + QString::number(id) + ")?", QMessageBox::Yes | QMessageBox::No);

    if (reply != QMessageBox::Yes)
    {
        return;
    }
    try
    {
        if (!uni.removeStudent(id))
        {
            QMessageBox::warning(this, "Not Found", "Student not found in system.");
            return;
        }
        ui->tableStudents->removeRow(row);
        ui->tableDorms->clearSelection();
        log("🗑 Removed student: " + name);
    }
    catch (DormitoryException &e)
    {
        QString errorMsg = QString::fromStdString(e.what());
        // just for type compatibility but even wihtout it it works
        QMessageBox::critical(this, "Error", errorMsg);
    }
}

void MainWindow::on_searchStu_textChanged(const QString &text)
{
    for (int row = 0; row < ui->tableStudents->rowCount(); row++)
    {
        bool match = text.isEmpty() || ui->tableStudents->item(row, 0)->text().contains(text, Qt::CaseInsensitive) || ui->tableStudents->item(row, 1)->text().contains(text, Qt::CaseInsensitive);

        ui->tableStudents->setRowHidden(row, !match);
    }
}

// Dorm tab:
void MainWindow::refreshDormCombos()
{
    // clear them to rebuild them later form tha table
    ui->comboDormForRoom->clear();
    ui->comboDormForResto->clear();

    for (int row = 0; row < ui->tableDorms->rowCount(); row++)
    {
        QString name = ui->tableDorms->item(row, 0)->text();
        ui->comboDormForRoom->addItem(name);
        ui->comboDormForResto->addItem(name);
    }
}

void MainWindow::on_btnAddDorm_clicked()
{
    bool ok;

    QString name = QInputDialog::getText(this, "Add Dormitory", "Dormitory name:", QLineEdit::Normal, "", &ok);
    if (!ok || name.trimmed().isEmpty())
        return;

    QString pavStr = QInputDialog::getText(this, "Add Dormitory", "Max pavilion letter (A–Z):", QLineEdit::Normal, "E", &ok);
    if (!ok || pavStr.isEmpty())
        return;
    char pav = pavStr.toUpper()[0].toLatin1();

    int floors = QInputDialog::getInt(this, "Add Dormitory", "Max floors:", 4, 1, 30, 1, &ok);
    if (!ok)
        return;

    int rPF = QInputDialog::getInt(this, "Add Dormitory", "Max rooms per floor:", 48, 1, 100, 1, &ok);
    if (!ok)
        return;

    try
    {
        Restaurant r;
        Dormitory d(name.toStdString(), pav, floors, rPF, r);

        if (!uni.addDormitory(d))
        {
            QMessageBox::warning(this, "Duplicate", "A dormitory with that name already exists.");
            return;
        }

        // Add row to the dorm table
        int row = ui->tableDorms->rowCount();
        ui->tableDorms->insertRow(row);
        ui->tableDorms->setItem(row, 0, new QTableWidgetItem(name));
        ui->tableDorms->setItem(row, 1, new QTableWidgetItem(QString(pav)));
        ui->tableDorms->setItem(row, 2, new QTableWidgetItem(QString::number(floors)));
        ui->tableDorms->setItem(row, 3, new QTableWidgetItem(QString::number(rPF)));

        refreshDormCombos();
        ui->tableDorms->clearSelection();
        log("✔ Added dormitory: " + name);
    }
    catch (DormitoryException &e)
    {
        QMessageBox::critical(this, "Validation Error", e.what());
    }
}

void MainWindow::on_btnAddDorm_2_clicked()
{
    int row = ui->tableDorms->currentRow();
    if (row < 0)
    {
        QMessageBox::information(this, "No selection", "Please click a dormitory row first.");
        return;
    }

    QString name = ui->tableDorms->item(row, 0)->text();

    auto ans = QMessageBox::question(this, "Confirm", "Remove dormitory " + name + "?", QMessageBox::Yes | QMessageBox::No);
    if (ans != QMessageBox::Yes)
        return;

    uni.removeDormitory(name.toStdString());
    ui->tableDorms->removeRow(row);

    // update combos
    refreshDormCombos();
    log("🗑 Removed dormitory: " + name);
}

// Rooms tab

void MainWindow::on_comboDormForRoom_currentTextChanged(const QString &text)
{

    refreshRoomTable(text);
}

void MainWindow::refreshRoomTable(const QString &dormName)
{
    ui->tableRooms->setRowCount(0);
    if (dormName.isEmpty())
        return;

    Dormitory *dorm = uni.findDormitory(dormName.toStdString());
    if (!dorm)
        return;

    const auto &rooms = dorm->getRooms();
    for (const auto &room : rooms)
    {
        int row = ui->tableRooms->rowCount();
        ui->tableRooms->insertRow(row);
        ui->tableRooms->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(room.getRoomCode())));
        ui->tableRooms->setItem(row, 1, new QTableWidgetItem(QString::number(room.getCapacity())));
        ui->tableRooms->setItem(row, 2, new QTableWidgetItem(QString::number(room.getOccupied())));

        // building student names string
        QString names;
        for (const auto *stu : room.getStudents())
        {
            if (!names.isEmpty())
                names += ", ";
            names += QString::fromStdString(stu->getName());
        }
        ui->tableRooms->setItem(row, 3, new QTableWidgetItem(names));
    }
}
void MainWindow::on_btnAddRoom_clicked()
{
    QString dormName = ui->comboDormForRoom->currentText();
    if (dormName.isEmpty())
    {
        QMessageBox::warning(this, "No dorm", "Add a dormitory first.");
        return;
    }

    Dormitory *dorm = uni.findDormitory(dormName.toStdString());
    if (!dorm)
    {
        QMessageBox::warning(this, "Error", "Dormitory not found.");
        return;
    }

    bool ok;
    // input info of the room
    QString pavStr = QInputDialog::getText(this, "Add Room", "Pavilion letter:", QLineEdit::Normal, "A", &ok);
    if (!ok || pavStr.isEmpty())
        return;
    char pav = pavStr.toUpper()[0].toLatin1();

    int floor = QInputDialog::getInt(this, "Add Room", "Floor:", 1, 1, 50, 1, &ok);
    if (!ok)
        return;

    int num = QInputDialog::getInt(this, "Add Room", "Room number:", 1, 1, 200, 1, &ok);
    if (!ok)
        return;

    int cap = QInputDialog::getInt(this, "Add Room", "Capacity:", 2, 1, 10, 1, &ok);
    if (!ok)
        return;

    try
    {
        dorm->addroom(pav, floor, num, cap);

        QString code = QString("%1-%2-%3").arg(pav).arg(floor).arg(num);
        refreshRoomTable(dormName);
        log("✔ Added room " + code + " in " + dormName);
    }
    catch (DormitoryException &e)
    {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_btnAssignStudent_clicked()
{
    // regular cheching (depend on class)
    QString dormName = ui->comboDormForRoom->currentText();
    if (dormName.isEmpty())
    {
        QMessageBox::warning(this, "No dorm", "Select a dormitory first.");
        return;
    }

    Dormitory *dorm = uni.findDormitory(dormName.toStdString());
    if (!dorm)
    {
        QMessageBox::warning(this, "Error", "Dormitory not found.");
        return;
    }

    bool ok;
    QString idStr = QInputDialog::getText(this, "Assign Student", "Student ID:", QLineEdit::Normal, "", &ok);
    if (!ok)
        return;

    // stu id entring and checkin
    Student *stu = uni.findStudent(idStr.toLongLong());
    if (!stu)
    {
        QMessageBox::warning(this, "Not found", "Student not found.");
        return;
    }

    // enetering room properties
    QString pavStr = QInputDialog::getText(this, "Assign Student", "Pavilion:", QLineEdit::Normal, "A", &ok);
    if (!ok || pavStr.isEmpty())
        return;
    char pav = pavStr.toUpper()[0].toLatin1();

    int floor = QInputDialog::getInt(this, "Assign Student", "Floor:", 1, 1, 50, 1, &ok);
    if (!ok)
        return;

    int num = QInputDialog::getInt(this, "Assign Student", "Room number:", 1, 1, 200, 1, &ok);
    if (!ok)
        return;

    try
    {
        dorm->assignStuToRoom(*stu, pav, floor, num);

        QString code = QString("%1-%2-%3").arg(pav).arg(floor).arg(num);
        refreshRoomTable(dormName);
        log("✔ Assigned student " + idStr + " to room " + code);
    }
    catch (DormitoryException &e)
    {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_btnRemoveFromRoom_clicked()
{
    QString dormName = ui->comboDormForRoom->currentText();
    if (dormName.isEmpty())
    {
        QMessageBox::warning(this, "No dorm", "Select a dormitory first.");
        return;
    }

    Dormitory *dorm = uni.findDormitory(dormName.toStdString());
    if (!dorm)
    {
        QMessageBox::warning(this, "Error", "Dormitory not found.");
        return;
    }

    // Step 2: Get student ID
    bool ok;
    QString idStr = QInputDialog::getText(this, "Remove from Room", "Student ID:", QLineEdit::Normal, "", &ok);
    if (!ok)
        return;

    Student *stu = uni.findStudent(idStr.toLongLong());
    if (!stu)
    {
        QMessageBox::warning(this, "Not found", "Student not found.");
        return;
    }

    // Step 3: Get room location
    QString pavStr = QInputDialog::getText(this, "Remove from Room", "Pavilion:", QLineEdit::Normal, "A", &ok);
    if (!ok || pavStr.isEmpty())
        return;
    char pav = pavStr.toUpper()[0].toLatin1();

    int floor = QInputDialog::getInt(this, "Remove from Room", "Floor:", 1, 1, 50, 1, &ok);
    if (!ok)
        return;

    int num = QInputDialog::getInt(this, "Remove from Room", "Room number:", 1, 1, 200, 1, &ok);
    if (!ok)
        return;

    try
    {
        dorm->removeStuFromRoom(idStr.toLongLong(), pav, floor, num);

        QString code = QString("%1-%2-%3").arg(pav).arg(floor).arg(num);
        refreshRoomTable(dormName);
        log("🗑 Removed student " + idStr + " from room " + code);
    }
    catch (DormitoryException &e)
    {
        QMessageBox::critical(this, "Error", e.what());
    }
}

// resto tab:
void MainWindow::on_btnOpenResto_clicked()
{
    QString dormName = ui->comboDormForResto->currentText();
    if (dormName.isEmpty())
    {
        QMessageBox::warning(this, "No dorm", "Select a dormitory first.");
        return;
    }

    Dormitory *dorm = uni.findDormitory(dormName.toStdString());
    if (!dorm)
    {
        QMessageBox::warning(this, "Error", "Dormitory not found.");
        return;
    }

    // Create and show the restaurant dialog
    RestaurantDialog dlg(&dorm->getRestaurant(), dormName, this);
    dlg.exec();
    log("Opened restaurant for: " + dormName);
}

MainWindow::~MainWindow()
{
    uni.saveToFile("udrms_data.txt");
    delete ui;
}
