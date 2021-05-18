#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <QDebug>
#include <sstream>
#include <iomanip>

// Класс для создания сущностей препаратов.
class Medicines
{
public:
    ~Medicines();
    Medicines(std::string name,
            double      price,
            size_t      expireDate);

    std::string getInfo();

    std::string getName();

private:
    const std::string _name;
    const double      _price;
    const size_t      _expireDate;
};

#endif // PATIENT_H
