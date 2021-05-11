#include "patient.hpp"

Patient::Patient(std::string gender,
                 std::string initials,
                 size_t age)
    : _gender(gender),
      _initials(initials),
      _age(age)
{

}

Patient::~Patient()
{
    qDebug() << "~Patient";
}

// Возврващем информацию в CSV формате для удобства.
std::string Patient::getInfo()
{
    return _initials + ";" +
           std::to_string(_age) + ";" +
           _gender;
}
