#ifndef MEAL_H
#define MEAL_H

#include <string>
#include <vector>
#include "Menu.h"

class Meal
{
private:
    string name;
    Menu menu;
    vector<long long> consumers; // student ids who already ate

public:
    Meal();
    Meal(const string &);

    string getName() const;
    void setName(const string &);

    const Menu &getMenu() const;
    Menu &getMenu();

    void setMenu(const Menu &);

    const vector<long long> &getConsumers() const;

    bool hasConsumed(long long) const;
    bool addConsumer(long long);

    void clearConsumers();

    void display() const;
};

#endif