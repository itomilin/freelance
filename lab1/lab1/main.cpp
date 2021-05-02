#include "universities.hpp"


int main(int argc, char **argv)
{
	Universities universities;
	static const std::string PATH_TO_FILE = ".\\output\\universities.csv";

	while (true)
	{
		std::cout << "1 - Add new\n"
			<< "2 - Delete by number\n"
			<< "3 - Show all\n"
			<< "4 - Write to file\n"
			<< "5 - Read from file\n"
			<< "6 - Show with sort\n"
			<< "0 - exit\n" << std::endl;

		std::cout << "Select number: ";
		int answer;
		std::cin >> answer;

		switch (answer)
		{
		case 0:
			return 0;
		case 1:
			universities.addNewUniversity();
			break;
		case 2:
			universities.deleteUniversity();
			break;
		case 3:
			universities.showUniversities();
			break;
		case 4:
			universities.writeToFile(PATH_TO_FILE);
			break;
		case 5:
			universities.readFromFile(PATH_TO_FILE);
			break;
		case 6:
			std::cout << "Sort type <from greatest to least>:\n"
				<< "1 - By foundation year\n"
				<< "2 - By name\n"
				<< "3 - By count of students\n"
				<< "4 - By count of faculties\n"
				<< "5 - By anniversary date\n";
			std::cout << "\nSelect number: ";
			std::cin >> answer;
			universities.sortVectorByType(answer);
			break;
		default:
			std::cout << "Invalid number!\n" << std::endl;
		}

		// Задержка консоли.
		system("pause");
		// Очистка консоли.
		system("cls");
	}
}
