#include "university.hpp"

#include <chrono>
#include <iomanip>

/**
* ����������� � �����������.
*/
University::University(std::string name,
	int foundationYear,
	int facultyCount,
	int studentCount)
	: _name(name),
	_foundationYear(foundationYear),
	_facultyCount(facultyCount),
	_studentCount(studentCount),
	_isAnniversary(check�nniversary())
{
	// ���� ��������� ���� ������ ����, ����������� ����������.
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
* ��������� ���������� ������� ��� ���� ��������� ����� ������.
* ��� ����� ��������� getters ��� ������� ��������� ���� ������.
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

/**
* �����, ��� �������� ��������� �� ������ ��� ���.
* �� ������ �������, �������, ������� ������ 25.
* 
* ���������� -1, ����� ���� �� ������, �.� ������ �� �����������.
*/
int University::check�nniversary()
{
	// ������� ���������, ������� ������ ������� ����.
	std::time_t now = std::time(nullptr);
	tm ltm;
	localtime_s(&ltm, &now);

	// ������ ������� ����.
	int universityAge = (1900 + ltm.tm_year) - _foundationYear;
	int anniversaryYear = universityAge % MULTIPLICITY;

	return (anniversaryYear == 0) ? universityAge : -1;
}
