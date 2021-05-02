#include "universities.hpp"


/**
* Добавляем новый университет в список.
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

	// Инициализируем объект класса ВУЗ, введенными выше данными.
	University *university = new University(universityName,
		foundationYear,
		facultiesCount,
		studentsCount);

	// Добавляем в конец списка новую запись.
	_universities.addEnd(university);
}

/**
* Удаляем элемент из списка по номеру элемента.
* Номер передаем в качестве параметра.
*/
void Universities::deleteUniversity(int index)
{
	// Делаем проверку, если список не пуст, тогда удаляем элемент.
	if (_universities.size() != 0)
	{
		if (index == 1)
		{
			std::cout << "Input number: ";
			int number;
			std::cin >> number;
			_universities.remove(number);
		}
		else if (index == 2)
		{
			_universities.removeHead();
		}
		else if (index == 3)
		{
			_universities.removeTail();
		}
		else
		{
			std::cout << "Invalid number!" << std::endl;
		}
	}
	else
	{
		std::cout << "List is empty! Nothing to do." << std::endl;
	}
}

/**
* Выводим список всех университетов, также для дальнейшего удаления, по номеру
* указываем его для каждого вуза в списке.
*/
void Universities::showUniversities()
{
	if (_universities.size() == 0)
	{
		std::cout << "List is empty!" << std::endl;
	}

	for (size_t i = 0; i < _universities.size(); ++i)
	{
		std::string anniversaryMsg;
		if (_universities[i]->getAnniversary() != -1)
		{
			anniversaryMsg = "in the year university celebrate " +
				std::to_string(_universities[i]->getAnniversary()) +
				" anniversary!!";
		}
		else
		{
			anniversaryMsg = "NONE";
		}

		std::cout << "[ " << i << " ]" << "\n"
			<< "Name:\t" << _universities[i]->getName() << std::endl
			<< "Foundation year:\t" << _universities[i]->getFoundationYear() << std::endl
			<< "Count of faculties:\t" << _universities[i]->getFacultyCount() << std::endl
			<< "Count of students:\t" << _universities[i]->getStudentCount() << std::endl
			<< "Anniversary:\t" << anniversaryMsg << std::endl
			<< std::endl;
	}
}

/**
* Функция записи текущего списка в файл.
* Если файл был не пустым, то вся информация будет перезаписана.
*/
void Universities::writeToFile(const std::string& path)
{
	if (_universities.size() == 0)
	{
		std::cout << "List is empty!" << std::endl;
		return;
	}

	std::ofstream file;
	// Открываем файл на запись
	file.open(path, std::ios::out);

	if (file.is_open())
	{
		// Читаем до конца файла
		for (size_t i = 0; i < _universities.size(); ++i)
		{
			file << _universities[i]->getName() << ";"
				<< _universities[i]->getFoundationYear() << ";"
				<< _universities[i]->getFacultyCount() << ";"
				<< _universities[i]->getStudentCount() << "\n";
		}
		file.close();
		std::cout << "********File successfull wrote!********" << std::endl;
	}
	else
	{
		// Если файл не смогли прочесть, тогда печатаем сообщение и выход с ошибкой.
		std::cout << "********Could not open the file!********" << std::endl;
		system("pause"); // Задержка консоли
		exit(1);
	}
}

/**
* Читает файл и преобразует строку из файла в объект класса.
*/
void Universities::readFromFile(const std::string& path)
{
	// Чистим весь текущий список.
	_universities.clear();

	std::string line = "";

	// Переменные, куда будет записывать значения из файла.
	std::string name = "";
	std::string foundationYear = "";
	std::string facultyCount = "";
	std::string studentCount = "";

	std::ifstream file;
	// Открываем файл на чтение
	file.open(path, std::ios::in | std::ios::binary);

	if (file.is_open())
	{
		file >> line;
		// Читаем файл, пока он не дошел до конца.
		while (file)
		{
			std::istringstream iss(line);
			// Раскладываем прочитанную строку на поля.
			getline(iss, name, ';');
			getline(iss, foundationYear, ';');
			getline(iss, facultyCount, ';');
			getline(iss, studentCount, ';');

			// Создаем объект, приводим необходимые поля к целому типу.
			University *university = new University(name,
				std::stoi(foundationYear),
				std::stoi(facultyCount),
				std::stoi(studentCount));

			// Помещаем прочитанный объект в список.
			_universities.addEnd(university);

			// Читаем следующую строку.
			file >> line;
		}

		file.close();
		std::cout << "********File successfull read!********" << std::endl;
	}
	else
	{
		// Если файл не смогли прочесть, тогда сообщение и выход с ошибкой.
		std::cout << "********Could not open the file!********" << std::endl;
		system("pause"); // Задержка консоли
		exit(1);
	}
}

void Universities::update(size_t index)
{
	if (index > _universities.size() || index < 0)
	{
		std::cout << "Invalid index!" << std::endl;
		return;
	}

	University *pUniversity = nullptr;
	for (size_t i = 0; i < _universities.size(); ++i)
	{
		if (i == index)
		{
			pUniversity = _universities[i];
		}
	}

	std::cout << "Change the university name?(y/n): ";
	char answer;
	std::cin >> answer;
	if (answer == 'y')
	{
		std::cout << "Input the university name: ";
		std::string universityName;
		std::cin >> universityName;
		pUniversity->setName(universityName);
	}

	std::cout << "Change the foundation year name?(y/n): ";
	std::cin >> answer;
	if (answer == 'y')
	{
		std::cout << "Input the foundation year: ";
		int foundationYear;
		std::cin >> foundationYear;
		pUniversity->setFoundationYear(foundationYear);
	}


	std::cout << "Change faculties count?(y/n): ";
	std::cin >> answer;
	if (answer == 'y')
	{
		std::cout << "Input facilities count: ";
		int facultiesCount;
		std::cin >> facultiesCount;
		pUniversity->setFacultyCount(facultiesCount);
	}

	std::cout << "Change students count?(y/n): ";
	std::cin >> answer;
	if (answer == 'y')
	{
		std::cout << "Input students count: ";
		int studentsCount;
		std::cin >> studentsCount;
		pUniversity->setStudentCount(studentsCount);
	}

	_universities.update(index, pUniversity);
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
				if (_universities[j]->getFoundationYear() < _universities[j + 1]->getFoundationYear())
				{
					std::swap(*_universities[j], *_universities[j + 1]);
				}
				break;
			case 2:
				if (_universities[j]->getName() < _universities[j + 1]->getName())
				{
					std::swap(*_universities[j], *_universities[j + 1]);
				}
				break;
			case 3:
				if (_universities[j]->getStudentCount() < _universities[j + 1]->getStudentCount())
				{
					std::swap(*_universities[j], *_universities[j + 1]);
				}
				break;
			case 4:
				if (_universities[j]->getFacultyCount() < _universities[j + 1]->getFacultyCount())
				{
					std::swap(*_universities[j], *_universities[j + 1]);
				}
				break;
			case 5:
				if (_universities[j]->getAnniversary() < _universities[j + 1]->getAnniversary())
				{
					std::swap(*_universities[j], *_universities[j + 1]);
				}
				break;
			default:
				return;
				break;
			}
		}
	}

	showUniversities(); // Показать отсортированный массив.
}
