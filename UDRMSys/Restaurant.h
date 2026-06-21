#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Meal.h"
#include "DormitoryException.h"

enum class MealType
{
    Breakfast,
    Lunch,
    Dinner
};

class Restaurant
{
private:
    Meal breakfast;
    Meal lunch;
    Meal dinner;
    int dayNumber;

public:
    Restaurant();
    Restaurant(const Menu &breakfastMenu, const Menu &lunchMenu, const Menu &dinnerMenu);

    int getDayNumber() const;

    Meal &getMeal(MealType type);
    const Meal &getMeal(MealType type) const;

    void setMenu(MealType type, const Menu &menu);

    bool scanner(long long studentId, MealType type);

    void newDay();

    void display() const;
};

#endif