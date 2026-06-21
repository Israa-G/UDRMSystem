#ifndef DORMITORY_H
#define DORMITORY_H

#include <vector>
#include "Room.h"
#include "Student.h"
#include "Restaurant.h"
using namespace std;

class Dormitory
{
private:
    string name;
    vector<Room> rooms;

    // Max limits
    char maxPavLet; // ex: 'E' (Meaning only A, B, C, D, E are allowed)
    int maxFloors;
    int maxRoomsPerFloor;

    Restaurant restaurant;

public:
    Dormitory(const string &, char, int, int, const Restaurant &);

    string getName() const;
    void setName(const string &);

    const vector<Room> &getRooms() const;

    char getMaxPavLet() const;
    int getMaxFlrs() const;
    int getMaxRoomPerFlr() const;

    const Restaurant &getRestaurant() const;
    Restaurant &getRestaurant();

    Room *findRoom(char, int, int);

    bool addroom(char, int, int, int);

    bool assignStuToRoom(Student &, char, int, int);
    bool removeStuFromRoom(long long, char, int, int);

    void locateStu(long long) const;

    void displayDormStatus() const;
};

#endif