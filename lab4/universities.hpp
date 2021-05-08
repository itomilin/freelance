#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include "university.hpp"
#include "linked_list.hpp"


class Universities
{
public:
    Universities() = default;
    ~Universities() = default;
    Universities(const Universities& universities) = default;

    void addNewUniversity(const std::string &universityName,
                          const int &foundationYear,
                          const int &facultiesCount,
                          const int &studentsCount);

    std::string showUniversities();

    int deleteUniversity(const int &index,
                         const int &number);

    int readFromFile(const std::string &path);

    int writeToFile(const std::string &path);

    int readFromFileBinary(const std::string &path);

    int writeToFileBinary(const std::string &path);

    void sortVectorByType(int sortType);

    void clear();

    size_t getSize();

    University *loadInfo(const size_t &index);

private:
    // Инициализируем собственную реализацию двунаправленного списка.
    DoublyLinkedList _universities;

};
