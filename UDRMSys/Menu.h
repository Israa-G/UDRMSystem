#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
using namespace std;

class Menu
{
private:
    vector<string> dishes;

public:
    Menu();
    Menu(const vector<string> &dishes);

    void setDishes(const vector<string> &dishes);
    const vector<string> &getDishes() const;

    bool addDish(const string &dish);
    bool removeDish(const string &dish);
    void clear();

    void display() const;
};

#endif