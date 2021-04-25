#include "universities.hpp"

/**
* ��������� ����� ����������� � ������.
*/
void Universities::addNewUniversity()
{
	std::cout << "Input a university name: ";
	std::string universityName;
	std::cin >> universityName;

	std::cout << "Input a foundation year: ";
	int foundationYear;
	std::cin >> foundationYear;

	std::cout << "Input faculties count: ";
	int facultiesCount;
	std::cin >> facultiesCount;

	std::cout << "Input students count: ";
	int studentsCount;
	std::cin >> studentsCount;

	// �������������� ������ ������ ���, ���������� ���� �������.
	University university(universityName,
		foundationYear,
		facultiesCount,
		studentsCount);

	_universities.emplace_back(std::make_unique<University>(university));
}

/**
* ������� ������� �� ������ �� ������ ��������.
* ����� �������� � �������� ���������.
*/
void Universities::deleteUniversity()
{
	// ������ ��������, ���� ������ �� ����, ����� ������� �������.
	if (!_universities.empty())
	{
		std::cout << "Input number: ";
		int number;
		std::cin >> number;
		//auto it = _universities.cbegin();
		_universities.erase(_universities.cbegin() + number);
	}
	else
	{
		std::cout << "List is empty! Nothing to do." << std::endl;
	}
}

/**
* ������� ������ ���� �������������, ����� ��� ����������� ��������, �� ������
* ��������� ��� ��� ������� ���� � ������.
*/
void Universities::showUniversities()
{
	for (size_t i = 0; i < _universities.size(); ++i)
	{
		std::string anniversaryMsg;
		if (_universities.at(i)->getAnniversary() != -1)
		{
			anniversaryMsg = "in the year university celebrate " +
				std::to_string(_universities.at(i)->getAnniversary()) +
				" anniversary!!";
		}
		else
		{
			anniversaryMsg = "NONE";
		}

		std::cout << "[ " << i << " ]" << "\n"
			<< "Name:\t" << _universities.at(i)->getName() << std::endl
			<< "Foundation year:\t" << _universities.at(i)->getFoundationYear() << std::endl
			<< "Count of faculties:\t" << _universities.at(i)->getFacultyCount() << std::endl
			<< "Count of students:\t" << _universities.at(i)->getStudentCount() << std::endl
			<< "Anniversary:\t" << anniversaryMsg << std::endl
			<< std::endl;
	}
}

/**
* ������� ������ �������� ������ � ����.
* ���� ���� ��� �� ������, �� ��� ���������� ����� ������������.
*/
void Universities::writeToFile(const std::string &path)
{
	std::fstream file;
	// ��������� ���� �� ������
	file.open(path, std::ios::out);

	if (file.is_open())
	{
		// ������ �� ����� �����
		for (size_t i = 0; i < _universities.size(); ++i)
		{
			file << _universities.at(i)->getName() << ";"
				<< _universities.at(i)->getFoundationYear() << ";"
				<< _universities.at(i)->getFacultyCount() << ";"
				<< _universities.at(i)->getStudentCount() << "\n";
		}
		file.close();
		std::cout << "********File successfull wrote!********" << std::endl;
	}
	else
	{
		// ���� ���� �� ������ ��������, ����� �������� ��������� � ����� � �������.
		std::cout << "********Could not open the file!********" << std::endl;
		system("pause"); // �������� �������
		exit(1);
	}
}

/**
* ������ ���� � ����������� ������ �� ����� � ������ ������.
*/
void Universities::readFromFile(const std::string &path)
{
	// ������ ���� ������� ������.
	_universities.clear();

	std::string line = "";

	// ����������, ���� ����� ���������� �������� �� �����.
	std::string name = "";
	std::string foundationYear = "";
	std::string facultyCount = "";
	std::string studentCount = "";

	std::fstream file;
	// ��������� ���� �� ������
	file.open(path, std::ios::in | std::ios::binary);

	if (file.is_open())
	{
		std::getline(file, line);
		while (!file.eof())
		{
			std::istringstream iss(line);
			// ������������ ����������� ������ �� ����.
			getline(iss, name, ';');
			getline(iss, foundationYear, ';');
			getline(iss, facultyCount, ';');
			getline(iss, studentCount, ';');

			// ������� ������, �������� ����������� ���� � ������ ����.
			University university(name,
				std::stoi(foundationYear),
				std::stoi(facultyCount),
				std::stoi(studentCount));

			// �������� ����������� ������ � ������.
			_universities.emplace_back(std::make_unique<University>(university));

			// ������� �� ��������� ������.
			std::getline(file, line);
		}

		file.close();
		std::cout << "********File successfull read!********" << std::endl;
	}
	else
	{
		// ���� ���� �� ������ ��������, ����� ��������� � ����� � �������.
		std::cout << "********Could not open the file!********" << std::endl;
		system("pause"); // �������� �������
		exit(1);
	}
}

void Universities::sortVectorByType(int sortType)
{
	for (size_t i = 0; i < _universities.size(); ++i)
	{
		for (size_t j = 0; j < _universities.size() - 1 - i; ++j)
		{
			switch (sortType)
			{
			case 1:
				if (_universities.at(j)->getFoundationYear() < _universities.at(j + 1)->getFoundationYear())
				{
					std::swap(_universities.at(j), _universities.at(j + 1));
				}
				break;
			case 2:
				if (_universities.at(j)->getName() < _universities.at(j + 1)->getName())
				{
					std::swap(_universities.at(j), _universities.at(j + 1));
				}
				break;
			case 3:
				if (_universities.at(j)->getStudentCount() < _universities.at(j + 1)->getStudentCount())
				{
					std::swap(_universities.at(j), _universities.at(j + 1));
				}
				break;
			case 4:
				if (_universities.at(j)->getFacultyCount() < _universities.at(j + 1)->getFacultyCount())
				{
					std::swap(_universities.at(j), _universities.at(j + 1));
				}
				break;
			case 5:
				if (_universities.at(j)->getAnniversary() < _universities.at(j + 1)->getAnniversary())
				{
					std::swap(_universities.at(j), _universities.at(j + 1));
				}
				break;
			default:
				break;
			}
		}
	}

	showUniversities(); // �������� ��������������� ������.
}
