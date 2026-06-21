#include "Student.h"
#include "DormitoryException.h"
#include <iostream>

using namespace std;

Student::Student(const string &name, long long id, int academicYear)
    : Person(name, id)
{
    setAcademicYear(academicYear);
    hasRoom = false;
}

int Student::getAcademicYear() const
{
    return academicYear;
}

void Student::setAcademicYear(int y)
{
    if (y < 1 || y > 7)
    {
        throw DormitoryException("Invalid academic year.");
    }

    academicYear = y;
}

bool Student::hasroom() const
{
    return hasRoom;
}

void Student::setHasRoom(bool hasRoom)
{
    this->hasRoom = hasRoom;
}

string Student::getRole() const
{
    return "Student";
}

void Student::displayInfo() const
{
    cout << "Student" << endl;
    cout << " ID: " << getId()
         << " | Name: " << getName()
         << " | Year: " << academicYear << endl;
}