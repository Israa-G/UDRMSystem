#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu()
{
}

Menu::Menu(const vector<string> &dishes)
{
    this->dishes = dishes;
}

void Menu::setDishes(const vector<string> &dishes)
{
    this->dishes = dishes;
}

const vector<string> &Menu::getDishes() const
{
    return dishes;
}

bool Menu::addDish(const string &dish)
{
    if (dish.empty())
    {
        return false;
    }

    for (size_t i = 0; i < dishes.size(); i++)
    {
        if (dishes[i] == dish)
        {
            return false;
        }
    }

    dishes.push_back(dish);
    return true;
}

bool Menu::removeDish(const string &dish)
{
    for (size_t i = 0; i < dishes.size(); i++)
    {
        if (dishes[i] == dish)
        {
            dishes.erase(dishes.begin() + i);
            return true;
        }
    }
    return false;
}

void Menu::clear()
{
    dishes.clear();
}

void Menu::display() const
{
    if (dishes.empty())
    {
        cout << "  No dishes set.\n";
        return;
    }

    cout << "Dishes:" << endl;
    for (size_t i = 0; i < dishes.size(); i++)
    {
        cout << "  - " << dishes[i] << endl;
    }
}