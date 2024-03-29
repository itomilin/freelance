#include "university.hpp"

#include <chrono>

/**
* Конструктор с параметрами.
*/
University::University(std::string name,
	int foundationYear,
	int facultyCount,
	int studentCount)
	: _name(name),
	_foundationYear(foundationYear),
	_facultyCount(facultyCount),
	_studentCount(studentCount),
	_isAnniversary(checkАnniversary())
{
	// Если введенные даты меньше нуля, выбрасываем исключение.
	if (foundationYear < 0)
	{
		throw "Invalid date!";
	}

	if (facultyCount < 0)
	{
		throw "Invalid faculty count!";
	}

	if (studentCount <= 0)
	{
		throw "Invalid student count!";
	}
}

/**
* Реализуем интерфейсы доступа для всех приватных полей класса.
* Для этого определим getters для каждого закрытого поля класса.
*/
std::string University::getName()
{
	return _name;
}

int University::getFacultyCount()
{
	return _facultyCount;
}

int University::getFoundationYear()
{
	return _foundationYear;
}

int University::getStudentCount()
{
	return _studentCount;
}

int University::getAnniversary()
{
	return _isAnniversary;
}

// Сеттеры

void University::setName(std::string value)
{
	_name = value;
}

void University::setFacultyCount(int value)
{
	_facultyCount = value;
}

void University::setFoundationYear(int value)
{
	_foundationYear = value;
}

void University::setStudentCount(int value)
{
	_studentCount = value;
}

/**
* Метод, для проверки празднует ли юбилей или нет.
* За юбилей считаем, возраст, который кратен 25.
* 
* Возвращаем -1, когда дата не кратна, т.е юбилей не празднуется.
*/
int University::checkАnniversary()
{
	// Получим структуру, которая хранит текущую дату.
	std::time_t now = std::time(nullptr);
	tm ltm;
	localtime_s(&ltm, &now);

	// Узнаем возраст ВУЗа.
	int universityAge = (1900 + ltm.tm_year) - _foundationYear;
	int anniversaryYear = universityAge % MULTIPLICITY;

	return (anniversaryYear == 0) ? universityAge : -1;
}
