#ifndef DOCTOR_HPP
#define DOCTOR_HPP

#include <string>
#include <QDebug>

// Класс, описывает сущность отдела.
// Добавим поля по заданию, и вывод информации об объекте.
class Department
{
public:
    ~Department();
    Department(std::string name,
               size_t      staffCount);

    std::string getInfo();

    std::string getName();

private:
    const std::string _name;
    const size_t      _staffCount;
};

#endif // DOCTOR_HPP
