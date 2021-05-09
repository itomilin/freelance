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

std::string Doctor::getInfo()
{
    return _specialization + " " +
           _initials + " " +
           std::to_string(_roomNumber);
}
