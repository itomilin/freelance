#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <QDebug>

// Класс для создания сущностей пациентов.
class Patient
{
public:
    ~Patient();
    Patient(std::string gender,
            std::string initials,
            size_t      age);

    std::string getInfo();

private:
    const std::string _gender;
    const std::string _initials;
    const size_t      _age;
};

#endif // PATIENT_H
