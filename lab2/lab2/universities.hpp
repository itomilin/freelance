#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include "university.hpp"
#include "linked_list.hpp"

class Universities
{
public:
	Universities() = default;
	~Universities() = default;
	Universities(const Universities& universities) = default;

	void addNewUniversity();

	void showUniversities();

	void deleteUniversity(int index);

	void readFromFile(const std::string &path);

	void writeToFile(const std::string &path);

	void sortVectorByType(int sortType);

	void update(size_t index);

private:
	// Инициализируем собственную реализацию двунаправленного списка.
	DoublyLinkedList _universities;

};
