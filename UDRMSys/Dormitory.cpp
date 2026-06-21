#include "Dormitory.h"
#include "DormitoryException.h"
#include "Restaurant.h"
#include <iostream>
Dormitory::Dormitory(const string &name, char pav, int flr, int roomperflr, const Restaurant &resto)
    : restaurant(resto)
{
    this->name = name;
    if (pav < 'A' || pav > 'Z')
    {
        throw DormitoryException("Invalid maximum pavilion letter.");
    }

    if (flr <= 0)
    {
        throw DormitoryException("Maximum floors must be positive.");
    }

    if (roomperflr <= 0)
    {
        throw DormitoryException("Maximum rooms per floor must be positive.");
    }

    maxPavLet = pav;
    maxFloors = flr;
    maxRoomsPerFloor = roomperflr;
}

string Dormitory::getName() const
{
    return name;
}

void Dormitory::setName(const string &Name)
{
    if (Name.empty())
    {
        throw DormitoryException("Error: Name cannot be empty!");
    }

    for (size_t i = 0; i < Name.size(); i++)
    {
        char c = Name[i];

        if (!std::isalpha(c) && !std::isspace(c))
        {
            throw DormitoryException("Error: Name can only contain letters and spaces!");
        }
    }
    name = Name;
}

const vector<Room> &Dormitory::getRooms() const
{
    return rooms;
}

char Dormitory::getMaxPavLet() const
{
    return maxPavLet;
}
int Dormitory::getMaxFlrs() const
{
    return maxFloors;
}
int Dormitory::getMaxRoomPerFlr() const
{
    return maxRoomsPerFloor;
}

const Restaurant &Dormitory::getRestaurant() const
{
    return restaurant;
}
Restaurant &Dormitory::getRestaurant()
{
    return restaurant;
}

Room *Dormitory::findRoom(char pav, int floor, int number)
{
    for (size_t i = 0; i < rooms.size(); i++)
    {
        if (rooms[i].getPavilion() == pav && rooms[i].getFloor() == floor && rooms[i].getNumber() == number)
        {
            return &rooms[i];
        }
    }

    return nullptr;
}

bool Dormitory::addroom(char pav, int flr, int num, int cap)
{
    if (pav < 'A' || pav > maxPavLet)
        throw DormitoryException("Invalid pavilion.");

    if (flr < 1 || flr > maxFloors)
        throw DormitoryException("Invalid floor number.");

    if (num < 1 || num > maxRoomsPerFloor)
        throw DormitoryException("Invalid room number.");

    if (findRoom(pav, flr, num) != nullptr)
        throw DormitoryException("Room already exists.");

    rooms.push_back(Room(pav, flr, num, cap));
    return true;
}

bool Dormitory::assignStuToRoom(Student &student, char pav, int flr, int num)
{
    Room *room = findRoom(pav, flr, num);

    if (room == nullptr)
        throw DormitoryException("ERROR: Room not found.");

    return room->addStudent(student);
}

bool Dormitory::removeStuFromRoom(long long id, char pav, int flr, int num)
{
    Room *room = findRoom(pav, flr, num);

    if (room == nullptr)
    {
        throw DormitoryException("Room not found.");
    }

    return room->removeStudent(id);
}

void Dormitory::locateStu(long long id) const
{
    for (size_t i = 0; i < rooms.size(); i++)
    {
        if (rooms[i].hasStudent(id))
        {
            cout << "Student found in room " << rooms[i].getRoomCode() << endl;
            return;
        }
    }

    cout << "Student not found" << endl;
}

void Dormitory::displayDormStatus() const
{
    cout << "Rooms in the dorm:" << std::endl;
    for (size_t i = 0; i < rooms.size(); i++)
    {
        rooms[i].display();
    }
}
