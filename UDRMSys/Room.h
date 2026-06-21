#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

#include "Student.h"

using namespace std;

class Room
{
private:
    char pavilion;
    int floor;
    int number;   // room num
    int capacity; // how many stu room can hold

    vector<Student *> students;

public:
    Room(char, int, int, int);

    char getPavilion() const;
    int getFloor() const;
    int getNumber() const;

    int getCapacity() const;
    int getOccupied() const;

    string getRoomCode() const;

    const vector<Student *> &getStudents() const;

    // room status
    bool isFull() const;
    bool isEmpty() const;

    // Search helpers
    bool matches(char, int, int) const;
    Student *findStudent(long long);

    // Student management
    bool addStudent(Student &);
    bool removeStudent(long long);

    bool hasStudent(long long) const;

    void display() const;
};

#endif