#include "Restaurant.h"
#include <iostream>

using namespace std;

Restaurant::Restaurant()
{
    breakfast.setName("Breakfast");
    lunch.setName("Lunch");
    dinner.setName("Dinner");
    dayNumber = 1;
}

Restaurant::Restaurant(const Menu &breakfastMenu, const Menu &lunchMenu, const Menu &dinnerMenu)
{
    breakfast.setName("Breakfast");
    lunch.setName("Lunch");
    dinner.setName("Dinner");

    breakfast.setMenu(breakfastMenu);
    lunch.setMenu(lunchMenu);
    dinner.setMenu(dinnerMenu);

    dayNumber = 1;
}

int Restaurant::getDayNumber() const
{
    return dayNumber;
}

Meal &Restaurant::getMeal(MealType type)
{
    switch (type)
    {
    case MealType::Breakfast:
        return breakfast;
    case MealType::Lunch:
        return lunch;
    case MealType::Dinner:
        return dinner;
    default:
        throw DormitoryException("Invalid meal type.");
    }
}

const Meal &Restaurant::getMeal(MealType type) const
{
    switch (type)
    {
    case MealType::Breakfast:
        return breakfast;
    case MealType::Lunch:
        return lunch;
    case MealType::Dinner:
        return dinner;
    default:
        throw DormitoryException("Invalid meal type.");
    }
}

void Restaurant::setMenu(MealType type, const Menu &menu)
{
    getMeal(type).setMenu(menu);
}

bool Restaurant::scanner(long long studentId, MealType type)
{
    Meal &meal = getMeal(type);

    if (meal.hasConsumed(studentId))
        throw DormitoryException("Student already consumed this meal today.");

    meal.addConsumer(studentId);
    return true;
}

void Restaurant::newDay()
{
    breakfast.clearConsumers();
    lunch.clearConsumers();
    dinner.clearConsumers();
    dayNumber++;
}

void Restaurant::display() const
{
    cout << "Restaurant - Day " << dayNumber << endl;

    cout << "Breakfast:" << endl;
    breakfast.display();

    cout << "Lunch:" << endl;
    lunch.display();

    cout << "Dinner:" << endl;
    dinner.display();
}