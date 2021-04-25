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
	
	std::string getName();

	int getFoundationYear();

	int getFacultyCount();

	int getStudentCount();

	int getAnniversary();

// Создаем ЗАКРЫТЫЕ поля(private), НЕ доступные для изменения.
private:
	const std::string _name {""};   // Название вуза.
	const int _foundationYear {0}; // Год открытия.
	const int _facultyCount {0};   // Количество факультетов.
	const int _studentCount {0};   // Количество студентов.
	const int _isAnniversary { false }; // Если празднует юбилей, значит true.

	// Кратность, для определения юбилея.
	static const int MULTIPLICITY { 25 };

	int checkАnniversary();

};
