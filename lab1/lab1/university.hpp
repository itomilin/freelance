#pragma once

#include <string>
#include <ctime>
#include <iostream>

// �����, ������� ��������� ������ ���, �������� ��������.
class University
{
public:
	// ����������� �� ��������� ������ ���� �� ���������, ���������� ����.
	University() = default;

	// ���������� ������ ���� �� ���������, ���������� ����.
	~University() = default;

	// ����������� ������������� ����������� � �����������.
	University(std::string name,
		int foundationYear,
		int facultyCount,
		int studentCount);

	// ����������� ����������� ������ ���� �� ���������, ���������� ����.
	University(const University& university) = default;
	
	std::string getName();

	int getFoundationYear();

	int getFacultyCount();

	int getStudentCount();

	int getAnniversary();

// ������� �������� ����(private), �� ��������� ��� ���������.
private:
	const std::string _name {""};   // �������� ����.
	const int _foundationYear {0}; // ��� ��������.
	const int _facultyCount {0};   // ���������� �����������.
	const int _studentCount {0};   // ���������� ���������.
	const int _isAnniversary { false }; // ���� ��������� ������, ������ true.

	// ���������, ��� ����������� ������.
	static const int MULTIPLICITY { 25 };

	int check�nniversary();

};
