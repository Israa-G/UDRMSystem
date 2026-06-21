#include "Meal.h"
#include <iostream>

using namespace std;

Meal::Meal()
{
}

Meal::Meal(const string &name)
{
    this->name = name;
}

string Meal::getName() const
{
    return name;
}

void Meal::setName(const string &name)
{
    this->name = name;
}

const Menu &Meal::getMenu() const
{
    return menu;
}

Menu &Meal::getMenu()
{
    return menu;
}

void Meal::setMenu(const Menu &menu)
{
    this->menu = menu;
}

const vector<long long> &Meal::getConsumers() const
{
    return consumers;
}

bool Meal::hasConsumed(long long studentId) const
{
    for (long long consumerId : consumers)
    {
        if (consumerId == studentId)
        {
            return true;
        }
    }
    return false;
}

bool Meal::addConsumer(long long studentId)
{
    if (hasConsumed(studentId))
        return false;

    consumers.push_back(studentId);
    return true;
}

void Meal::clearConsumers()
{
    consumers.clear();
}

void Meal::display() const
{
    cout << name << " menu:" << endl;
    menu.display();

    cout << "  Consumers today: " << consumers.size() << endl;
}