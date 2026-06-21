#include "University.h"
#include "DormitoryException.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

University::University(string name)
{
    this->name = name;
}

string University::getName() const
{
    return name;
}
const vector<Student> &University::getStudents() const
{
    return students;
}
const vector<Dormitory> &University::getDormitories() const
{
    return dormitories;
}

void University::setName(const string &Name)
{
    if (Name.empty())
    {
        throw DormitoryException("Error: Name of uni cannot be empty!");
    }

    for (size_t i = 0; i < Name.size(); i++)
    {
        char c = Name[i];

        if (!std::isalpha(c) && !std::isspace(c))
        {
            throw DormitoryException("Error: Name of uni can only contain letters and spaces!");
        }
    }
    name = Name;
}

bool University::addDormitory(const Dormitory &d)
{
    for (size_t i = 0; i < dormitories.size(); i++)
    {
        if (dormitories[i].getName() == d.getName())
        {
            return false;
        }
    }

    dormitories.push_back(d);
    return true;
}

bool University::removeDormitory(const string &name)
{
    for (size_t i = 0; i < dormitories.size(); i++)
    {
        if (dormitories[i].getName() == name)
        {
            dormitories.erase(dormitories.begin() + i);
            return true;
        }
    }
    return false;
}

Dormitory *University::findDormitory(const string &name)
{
    for (size_t i = 0; i < dormitories.size(); i++)
    {
        if (dormitories[i].getName() == name)
        {
            return &dormitories[i];
        }
    }
    return nullptr;
}

bool University::addStudent(const Student &s)
{
    for (size_t i = 0; i < students.size(); i++)
    {
        if (students[i].getId() == s.getId())
            return false; // already exists
    }

    students.push_back(s);
    return true;
}

bool University::removeStudent(long long id)
{
    for (size_t i = 0; i < students.size(); i++)
    {
        if (students[i].getId() == id)
        {
            students.erase(students.begin() + i);
            return true;
        }
    }

    return false;
}

Student *University::findStudent(long long id)
{
    for (size_t i = 0; i < students.size(); i++)
    {
        if (students[i].getId() == id)
            return &students[i];
    }

    return nullptr;
}

void University::displayAll() const
{
    cout << "UNIVERSITY: " << name << endl;

    for (size_t i = 0; i < dormitories.size(); i++)
    {
        dormitories[i].displayDormStatus();
    }
}

// storage funcs:

void University::saveToFile(const string &filename)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "cna't creat the file" << endl;
        return;
    }

    file << name << endl; // storing name of uni (data member)

    // storing num of student ndline and then all students info
    file << students.size() << endl;
    for (const Student &s : students)
    {
        file << s.getName() << "|" << s.getId() << "|" << s.getAcademicYear() << "|" << s.hasroom() << endl;
    }

    // saving dorms:
    file << dormitories.size() << endl;
    for (const Dormitory &d : dormitories)
    {
        file << d.getName() << "|" << d.getMaxPavLet() << "|" << d.getMaxFlrs() << "|" << d.getMaxRoomPerFlr() << endl;

        // rooms info:
        const vector<Room> &rooms = d.getRooms();
        for (const Room &r : rooms)
        {
            file << r.getPavilion() << "|" << r.getFloor() << "|" << r.getNumber() << "|" << r.getCapacity() << endl;

            const vector<Student *> &studentsInRoom = r.getStudents();
            file << studentsInRoom.size() << "|";
            for (const Student *stu : studentsInRoom)
            {
                file << stu->getId() << "|";
            }
            file << endl;
        }

        // resto info:
        const Restaurant &resto = d.getRestaurant();
        file << resto.getDayNumber() << endl;

        // Meals of resto:
        //-----------breakfast
        const Meal &breakfast = resto.getMeal(MealType::Breakfast);
        // menu dishes info:
        const vector<string> &breakfastDishes = breakfast.getMenu().getDishes();
        file << breakfastDishes.size() << endl;
        for (const auto &dish : breakfastDishes)
        {
            file << dish << "|";
        }
        file << endl;
        // breakfast consumers:
        const vector<long long> &breakfastConsumers = breakfast.getConsumers();
        file << breakfastConsumers.size() << endl;
        for (long long id : breakfastConsumers)
        {
            file << id << "|";
        }
        file << endl;
        //-----------lunch
        const Meal &lunch = resto.getMeal(MealType::Lunch);
        const auto &lunchDishes = lunch.getMenu().getDishes();
        file << lunchDishes.size() << endl;
        for (const auto &dish : lunchDishes)
        {
            file << dish << "|";
        }
        file << endl;

        const auto &lunchConsumers = lunch.getConsumers();
        file << lunchConsumers.size() << endl;
        for (long long id : lunchConsumers)
        {
            file << id << "|";
        }
        file << endl;

        //-----------dinner
        const Meal &dinner = resto.getMeal(MealType::Dinner);
        const auto &dinnerDishes = dinner.getMenu().getDishes();
        file << dinnerDishes.size() << endl;
        for (const auto &dish : dinnerDishes)
        {
            file << dish << "|";
        }
        file << endl;

        const auto &dinnerConsumers = dinner.getConsumers();
        file << dinnerConsumers.size() << endl;
        for (long long id : dinnerConsumers)
        {
            file << id << "|";
        }
        file << endl;
    }
    file.close();
}

void University::loadFromFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "No saved data found. Starting fresh!" << endl;
        return;
    }

    // clearing existing data
    students.clear();
    dormitories.clear();

    string line;
    int count;

    // load uni name
    getline(file, line);
    name = line;

    // load students
    file >> count;
    getline(file, line);

    for (int i = 0; i < count; i++)
    {
        getline(file, line);
        stringstream ss(line);
        string name, idStr, yearStr, hasRoomStr;

        getline(ss, name, '|');
        getline(ss, idStr, '|');
        getline(ss, yearStr, '|');
        getline(ss, hasRoomStr, '|');

        long long id = stoll(idStr);
        int year = stoi(yearStr);
        bool hasRoom = (hasRoomStr == "1");

        Student s(name, id, year);
        s.setHasRoom(hasRoom);
        students.push_back(s);
    }

    // load dorms info
    file >> count;
    getline(file, line);

    for (int i = 0; i < count; i++)
    {
        getline(file, line);
        stringstream ss(line);
        string dormName, pavStr, floorsStr, rpfStr;

        getline(ss, dormName, '|');
        getline(ss, pavStr, '|');
        getline(ss, floorsStr, '|');
        getline(ss, rpfStr, '|');

        char pav = pavStr[0];
        int floors = stoi(floorsStr);
        int rpf = stoi(rpfStr);

        Restaurant r;
        Dormitory d(dormName, pav, floors, rpf, r);

        // load rooms
        int roomCount;
        file >> roomCount;
        getline(file, line);

        for (int j = 0; j < roomCount; j++)
        {
            getline(file, line);
            stringstream rs(line);
            string pavStr2, floorStr, numStr, capStr, studentCountStr;

            getline(rs, pavStr2, '|');
            getline(rs, floorStr, '|');
            getline(rs, numStr, '|');
            getline(rs, capStr, '|');
            getline(rs, studentCountStr, '|');

            char pav2 = pavStr2[0];
            int floor = stoi(floorStr);
            int num = stoi(numStr);
            int cap = stoi(capStr);
            int studentCount = stoi(studentCountStr);

            // add room to dorm
            d.addroom(pav2, floor, num, cap);

            Room *roomPtr = d.findRoom(pav2, floor, num);

            if (roomPtr)
            {
                // add stus to room
                for (int k = 0; k < studentCount; k++)
                {
                    string idStr;
                    getline(rs, idStr, '|');
                    if (!idStr.empty())
                    {
                        long long id = stoll(idStr);
                        Student *stu = findStudent(id);
                        if (stu)
                        {
                            roomPtr->addStudent(*stu);
                        }
                    }
                }
            }
        }

        // load resto info
        int dayNumber;
        file >> dayNumber;
        getline(file, line);

        // -------breakfast
        int dishCount;
        file >> dishCount;
        getline(file, line);

        if (dishCount > 0)
        {
            getline(file, line);
            stringstream bss(line);
            string dish;
            while (getline(bss, dish, '|'))
            {
                if (!dish.empty())
                    d.getRestaurant().getMeal(MealType::Breakfast).getMenu().addDish(dish);
            }
        }
        else
        {
            getline(file, line);
        }

        // breakfast consumers
        int consumerCount;
        file >> consumerCount;
        getline(file, line); // consume newline

        if (consumerCount > 0)
        {
            getline(file, line);
            stringstream css(line);
            string idStr;
            while (getline(css, idStr, '|'))
            {
                if (!idStr.empty())
                {
                    long long id = stoll(idStr);
                    d.getRestaurant().getMeal(MealType::Breakfast).addConsumer(id);
                }
            }
        }
        else
        {
            getline(file, line);
        }

        //----------lunch
        file >> dishCount;
        getline(file, line);

        if (dishCount > 0)
        {
            getline(file, line);
            stringstream lss(line);
            string dish;
            while (getline(lss, dish, '|'))
            {
                if (!dish.empty())
                    d.getRestaurant().getMeal(MealType::Lunch).getMenu().addDish(dish);
            }
        }
        else
        {
            getline(file, line);
        }

        // lunch consumers
        file >> consumerCount;
        getline(file, line);

        if (consumerCount > 0)
        {
            getline(file, line);
            stringstream css(line);
            string idStr;
            while (getline(css, idStr, '|'))
            {
                if (!idStr.empty())
                {
                    long long id = stoll(idStr);
                    d.getRestaurant().getMeal(MealType::Lunch).addConsumer(id);
                }
            }
        }
        else
        {
            getline(file, line);
        }

        //---------dinner
        file >> dishCount;
        getline(file, line);

        if (dishCount > 0)
        {
            getline(file, line);
            stringstream dss(line);
            string dish;
            while (getline(dss, dish, '|'))
            {
                if (!dish.empty())
                    d.getRestaurant().getMeal(MealType::Dinner).getMenu().addDish(dish);
            }
        }
        else
        {
            getline(file, line);
        }

        // Dinner consumers
        file >> consumerCount;
        getline(file, line);

        if (consumerCount > 0)
        {
            getline(file, line);
            stringstream css(line);
            string idStr;
            while (getline(css, idStr, '|'))
            {
                if (!idStr.empty())
                {
                    long long id = stoll(idStr);
                    d.getRestaurant().getMeal(MealType::Dinner).addConsumer(id);
                }
            }
        }
        else
        {
            getline(file, line);
        }

        // add drom to uni
        dormitories.push_back(d);
    }

    file.close();
}
