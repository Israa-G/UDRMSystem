#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "University.h"
#include "studentdialog.h"
#include "restaurantdialog.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    // stu tab
    void on_btnAddStudent_clicked();
    void on_btnRmStu_clicked();
    void on_searchStu_textChanged(const QString &text);

    // dorm tab
    void on_btnAddDorm_clicked();
    void on_btnAddDorm_2_clicked();

    // room tab
    void on_comboDormForRoom_currentTextChanged(const QString &text);
    void on_btnAddRoom_clicked();
    void on_btnAssignStudent_clicked();
    void on_btnRemoveFromRoom_clicked();

    // resto tab
    void on_btnOpenResto_clicked();

private:
    Ui::MainWindow *ui;
    University uni;

    void log(const QString &msg);
    void refreshDormCombos();
    void refreshRoomTable(const QString &dormName);
};
#endif