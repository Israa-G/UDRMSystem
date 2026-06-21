#include "DormitoryException.h"
DormitoryException::DormitoryException(const std::string &msg) : message(msg) {}

const char *DormitoryException::what() const noexcept
{
    return message.c_str();
}