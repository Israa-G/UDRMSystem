#ifndef DORMITORYEXCEPTIO_H
#define DORMITORYEXCEPTIO_H
#include <exception>
#include <string>

class DormitoryException : public std::exception
{
private:
    std::string message;

public:
    DormitoryException(const std::string &);

    const char *what() const noexcept override;
};
#endif