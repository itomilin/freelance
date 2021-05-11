#include "doctor.hpp"

Doctor::Doctor(std::string specialization,
               std::string initials,
               size_t      roomNumber)
    : _specialization(specialization),
      _initials(initials),
      _roomNumber(roomNumber)
{

}

Doctor::~Doctor()
{
    qDebug() << "~Doctor";
}

// Возвращаем информацию о докторе сразу в CSV формате для удобства.
std::string Doctor::getInfo()
{
    return _specialization + ";" +
           _initials + ";" +
           std::to_string(_roomNumber);
}
