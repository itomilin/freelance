#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "university.hpp"

class Universities
{
public:
	Universities() = default;
	~Universities() = default;
	Universities(const Universities& universities) = default;

	void addNewUniversity();

	void showUniversities();

	void deleteUniversity();

	void readFromFile(const std::string &path);

	void writeToFile(const std::string &path);

	void sortVectorByType(int sortType);

private:
	// Инициализируем вектор, типом которого является класс ВУЗ.
	std::vector<std::unique_ptr<University>> _universities;

};
