#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person
{
private:
    string name;
    long long id;

public:
    Person(const string &, long long);

    string getName() const;
    long long getId() const;

    void setName(const string &);
    void setId(long long);

    virtual ~Person() {}

    virtual string getRole() const = 0;
    virtual void displayInfo() const = 0;
};

#endif