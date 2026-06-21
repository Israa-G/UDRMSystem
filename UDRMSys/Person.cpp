#include "Person.h"
#include "DormitoryException.h"

Person::Person(const string &n, long long i)
{
    setName(n);
    setId(i);
}

string Person::getName() const
{
    return name;
}
long long Person::getId() const
{
    return id;
}

void Person::setId(long long id)
{
    if (id >= 100000000000 && id <= 999999999999)
    {
        this->id = id;
    }
    else
    {
        throw DormitoryException("Id not valid");
    }
}

void Person::setName(const string &Name)
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