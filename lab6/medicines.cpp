#include "medicines.hpp"

Medicines::Medicines(std::string name,
                 double price,
                 size_t expireDate)
    : _name(name),
      _price(price),
      _expireDate(expireDate)
{

}

Medicines::~Medicines()
{
}

// Возврващем информацию в CSV формате для удобства.
std::string Medicines::getInfo()
{
    std::ostringstream out;
    out << _price;
    return _name + ";" +
           out.str() + ";" +
            std::to_string(_expireDate);
}

std::string Medicines::getName()
{
    return _name;
}
