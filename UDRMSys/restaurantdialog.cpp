#include "restaurantdialog.h"
#include "ui_restaurantdialog.h"
#include "DormitoryException.h"
#include <QMessageBox> // popup

RestaurantDialog::RestaurantDialog(Restaurant *resto, const QString &dormName, QWidget *parent)
    : QDialog(parent), ui(new Ui::RestaurantDialog), restaurant(resto)
{
    ui->setupUi(this);

    setWindowTitle("Restaurant — " + dormName);

    ui->lblTitle->setText("Restaurant — " + dormName);

    ui->lblDay->setText("Day: " + QString::number(restaurant->getDayNumber()));

    refreshDishes();
}

// helper functions:
MealType RestaurantDialog::currentMeal() const
{
    switch (ui->comboMeal->currentIndex())
    {
    case 0:
        return MealType::Breakfast;
    case 1:
        return MealType::Lunch;
    default:
        return MealType::Dinner;
    }
}

void RestaurantDialog::refreshDishes()
{
    ui->listDishes->clear();

    const Meal &meal = restaurant->getMeal(currentMeal());
    const auto &dishes = meal.getMenu().getDishes();

    if (dishes.empty())
    {

        ui->listDishes->addItem("(no dishes set)");
    }
    else
    {
        for (const auto &dish : dishes)
        {
            ui->listDishes->addItem(QString::fromStdString(dish));
        }
    }

    // Update meal count
    int count = meal.getConsumers().size();
    ui->lblMealsServed->setText("📊 Meals served today: " + QString::number(count));
}

void RestaurantDialog::on_comboMeal_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    refreshDishes();
}

void RestaurantDialog::on_btnAddDish_clicked()
{
    QString dish = ui->lineDish->text().trimmed();
    if (dish.isEmpty())
    {
        QMessageBox::warning(this, "Empty", "Please type a dish name first.");
        return;
    }

    restaurant->getMeal(currentMeal()).getMenu().addDish(dish.toStdString());
    ui->lineDish->clear();
    refreshDishes();
}

void RestaurantDialog::on_btnRemoveDish_clicked()
{
    QListWidgetItem *item = ui->listDishes->currentItem();
    if (!item || item->text().startsWith("("))
    {
        QMessageBox::warning(this, "Nothing selected", "Click a dish first.");
        return;
    }

    restaurant->getMeal(currentMeal()).getMenu().removeDish(item->text().toStdString());
    refreshDishes();
}

void RestaurantDialog::on_btnScan_clicked()
{
    bool ok;
    long long id = ui->lineScanId->text().toLongLong(&ok);

    if (!ok || ui->lineScanId->text().isEmpty())
    {
        QMessageBox::warning(this, "Invalid ID", "Enter a valid student ID.");
        return;
    }

    try
    {
        restaurant->scanner(id, currentMeal());
        QMessageBox::information(this, "Recorded", "Meal recorded for student " + QString::number(id) + ".");
        ui->lineScanId->clear();
        refreshDishes();
    }
    catch (DormitoryException &e)
    {
        QMessageBox::warning(this, "Already consumed", e.what());
    }
}

void RestaurantDialog::on_btnNextDay_clicked()
{
    restaurant->newDay();
    ui->lblDay->setText("Day: " + QString::number(restaurant->getDayNumber()));
    refreshDishes();

    QMessageBox::information(this, "New Day", "Advanced to Day " + QString::number(restaurant->getDayNumber()) + ".\nAll meal records cleared.");
}

void RestaurantDialog::on_buttonBox_rejected()
{
    reject(); // Close the dialog
}

RestaurantDialog::~RestaurantDialog()
{
    delete ui;
}
