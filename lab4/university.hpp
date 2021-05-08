#pragma once

#include <string>
#include <ctime>
#include <iostream>

// Класс, который описывает объект ВУЗ, согласно варианту.
class University
{
public:
    // Конструктор по умолчанию всегда есть по умолчанию, определили явно.
    University() = default;

    // Деструктор всегда есть по умолчанию, определили явно.
    ~University() = default;

    // Собственный Перегруженный конструктор с параметрами.
    University(std::string name,
    int foundationYear,
    int facultyCount,
    int studentCount);

    // Конструктор копирования всегда есть по умолчанию, определили явно.
    University(const University& university) = default;

    // Геттеры
    std::string getName();

    int getFoundationYear();

    int getFacultyCount();

    int getStudentCount();

    int getAnniversary();

    // Сеттеры
    void setName(std::string value);

    void setFoundationYear(int value);

    void setFacultyCount(int value);

    void setStudentCount(int value);

// Создаем ЗАКРЫТЫЕ поля(private), доступные для изменения.
private:
    std::string _name {""};   // Название вуза.
    int _foundationYear {0}; // Год открытия.
    int _facultyCount {0};   // Количество факультетов.
    int _studentCount {0};   // Количество студентов.
    int _isAnniversary { false }; // Если празднует юбилей, значит true.

    // Кратность, для определения юбилея.
    static const int MULTIPLICITY { 25 };

    int checkAnniversary();

};
