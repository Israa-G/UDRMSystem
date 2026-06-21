#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <string>
#include <vector>
#include "Dormitory.h"
#include "Student.h"
using namespace std;

class University
{
private:
    string name;
    vector<Dormitory> dormitories;
    vector<Student> students;

public:
    University(string);

    string getName() const;
    void setName(const string &);

    // dormitory management
    bool addDormitory(const Dormitory &);
    bool removeDormitory(const string &);

    Dormitory *findDormitory(const string &);

    // student management
    bool addStudent(const Student &);
    bool removeStudent(long long);

    Student *findStudent(long long);

    void displayAll() const;

    // storage functions
    void saveToFile(const string &);
    void loadFromFile(const string &);
};

#endif