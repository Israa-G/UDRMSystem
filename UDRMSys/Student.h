#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <string>

using namespace std;

class Student : public Person
{
private:
    int academicYear;
    bool hasRoom;

public:
    Student(const string & name, long long id, int academicYear);

    int getAcademicYear() const;
    void setAcademicYear(int);

    bool hasroom () const;
    void setHasRoom(bool);

    string getRole() const override;
    void displayInfo() const override;
};

#endif