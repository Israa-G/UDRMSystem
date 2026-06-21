#include "Room.h"
#include "DormitoryException.h"
#include <iostream>

using namespace std;

Room::Room(char pavilion, int floor, int number, int capacity)
{
    if (pavilion < 'A' || pavilion > 'Z')
    {
        throw DormitoryException("Invalid pavilion letter.");
    }

    if (floor <= 0)
    {
        throw DormitoryException("Floor number must be positive.");
    }

    if (number <= 0)
    {
        throw DormitoryException("Room number must be positive.");
    }

    if (capacity <= 0)
    {
        throw DormitoryException("Room capacity must be positive.");
    }

    this->pavilion = pavilion;
    this->floor = floor;
    this->number = number;
    this->capacity = capacity;
}

char Room::getPavilion() const
{
    return pavilion;
}
int Room::getFloor() const
{
    return floor;
}
int Room::getNumber() const
{
    return number;
}
int Room::getCapacity() const
{
    return capacity;
}
int Room::getOccupied() const
{
    return static_cast<int>(students.size());
}

string Room::getRoomCode() const
{
    return string(1, pavilion) + "-" + to_string(floor) + "-" + to_string(number);
}

const vector<Student *> &Room::getStudents() const
{
    return students;
}

bool Room::isFull() const
{
    return static_cast<int>(students.size()) >= capacity;
}

bool Room::isEmpty() const
{
    return students.empty();
}

bool Room::matches(char pav, int flr, int num) const
{
    return pavilion == pav && floor == flr && number == num;
}

Student *Room::findStudent(long long id)
{
    for (size_t i = 0; i < students.size(); i++)
    {
        if (students[i]->getId() == id)
        {
            return students[i];
        }
    }

    return nullptr;
}

bool Room::addStudent(Student &student)
{
    if (isFull())
        throw DormitoryException("Room is full.");

    if (student.hasroom())
        throw DormitoryException("Student already has a room.");

    student.setHasRoom(true);

    students.push_back(&student);

    return true;
}

bool Room::removeStudent(long long id)
{
    for (size_t i = 0; i < students.size(); i++)
    {
        if (students[i]->getId() == id)
        {
            students[i]->setHasRoom(false);
            students.erase(students.begin() + i);
            return true;
        }
    }

    throw DormitoryException("Student not found in room.");
}

bool Room::hasStudent(long long id) const
{
    for (size_t i = 0; i < students.size(); i++)
    {
        if (students[i]->getId() == id)
        {
            return true;
        }
    }

    return false;
}

void Room::display() const
{
    cout << "Room: " << getRoomCode()
         << " Occupancy: " << getOccupied() << "/" << capacity << endl;
    cout << " Students: " << endl;

    for (size_t i = 0; i < students.size(); i++)
    {
        cout << " (" << students[i]->getName() << "," << students[i]->getId() << ")" << endl;
    }
}