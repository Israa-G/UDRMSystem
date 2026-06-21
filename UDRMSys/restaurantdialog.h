#ifndef RESTAURANTDIALOG_H
#define RESTAURANTDIALOG_H
#include "University.h"
#include "Restaurant.h"
#include <QDialog>

namespace Ui
{
    class RestaurantDialog;
}

class RestaurantDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RestaurantDialog(Restaurant *resto, const QString &dormName, QWidget *parent = nullptr);
    ~RestaurantDialog();

private slots:
    void on_comboMeal_currentIndexChanged(int index);
    void on_btnAddDish_clicked();
    void on_btnRemoveDish_clicked();
    void on_btnScan_clicked();
    void on_btnNextDay_clicked();
    void on_buttonBox_rejected();

private:
    Ui::RestaurantDialog *ui;

    Restaurant *restaurant;
    MealType currentMeal() const;
    void refreshDishes();
};

#endif // RESTAURANTDIALOG_H
