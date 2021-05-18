#include "department.hpp"

Department::Department(std::string name,
                       size_t      staffCount)
    : _name(name),
      _staffCount(staffCount)
{

}

Department::~Department()
{
}

// Возвращаем информацию о отделе сразу в CSV формате для удобства.
std::string Department::getInfo()
{
    return _name+ ";" +
            std::to_string(_staffCount);
}

std::string Department::getName()
{
    return _name;
}
