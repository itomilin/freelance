#ifndef DOCTOR_HPP
#define DOCTOR_HPP

#include <string>
#include <QDebug>

// Класс, описывает сущность доктор.
// Добавим поля по заданию, и вывод информации об объекте.
class Doctor
{
public:
    ~Doctor();
    Doctor(std::string specialization,
           std::string initials,
           size_t      roomNumber);

    std::string getInfo();

private:
    const std::string _specialization;
    const std::string _initials;
    const size_t      _roomNumber;
};

#endif // DOCTOR_HPP
