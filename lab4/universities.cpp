#include "universities.hpp"
#include <algorithm>

#include <filesystem>

using namespace::std::filesystem;


/**
* Добавляем новый университет в список.
*/
void Universities::addNewUniversity(const std::string &universityName,
                                    const int &foundationYear,
                                    const int &facultiesCount,
                                    const int &studentsCount)
{
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
* Когда удаляем по конкретному номеру, тогда используем второй параметр number
* он отвечает за номер элемента в списке.
*/
int Universities::deleteUniversity(const int &index,
                                   const int &number)
{
    // Заведем переменную для возвращаемого значения.
    int retCode = EXIT_SUCCESS;
    // Делаем проверку, если список не пуст, тогда удаляем элемент.
    if (_universities.size() != 0)
    {
        if (index == 1)
        {
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
            retCode = EXIT_FAILURE;
        }
    }
    else
    {
        std::cout << "List is empty! Nothing to do." << std::endl;
        retCode = EXIT_FAILURE;
    }

    return retCode;
}

/**
* Выводим список всех университетов, также для дальнейшего удаления, по номеру
* указываем его для каждого вуза в списке.
*/
std::string Universities::showUniversities()
{
    if (_universities.size() == 0)
    {
        std::cout << "List is empty!" << std::endl;
        // Возвращаем пустую строку.
        return {};
    }
    std::stringstream ss;

    for (size_t i = 0; i < _universities.size(); ++i)
    {
        std::string anniversaryMsg = "";
        auto u = _universities[i];
        // Проверяем, если празднует юбилей, то вызываем функцию расчета юбилея.
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

        // Выполняем построение строки.
        ss  <<"[ " << i << " ]" << std::endl
        << "Name:\t" << _universities[i]->getName() << std::endl
        << "Foundation year:\t" << _universities[i]->getFoundationYear() << std::endl
        << "Count of faculties:\t" << _universities[i]->getFacultyCount() << std::endl
        << "Count of students:\t" << _universities[i]->getStudentCount() << std::endl
        << "Anniversary:\t" << anniversaryMsg << std::endl
        << std::endl;
    }
    // Возвращаем строку с информацией об университетах.
    return ss.str();
}

/**
* Функция записи текущего списка в файл.
* Если файл был не пустым, то вся информация будет перезаписана.
*/
int Universities::writeToFile(const std::string& path)
{
    if (_universities.size() == 0)
    {
        std::cout << "List is empty!" << std::endl;
        return EXIT_FAILURE;
    }

    std::ofstream file;
    // Открываем файл на запись
    file.open(path, std::ios::out);

    if (file.is_open())
    {
        // Читаем список до конца, берем данные и пишем в файл.
        for (size_t i = 0; i < _universities.size(); ++i)
        {
            file << _universities[i]->getName() << ";"
                 << _universities[i]->getFoundationYear() << ";"
                 << _universities[i]->getFacultyCount() << ";"
                 << _universities[i]->getStudentCount() << "\n";
        }
        file.close();
        std::cout << "********File successfull wrote!********" << std::endl;
        return EXIT_SUCCESS;
    }
    else
    {
        // Если файл не смогли прочесть, тогда печатаем сообщение и возвращаем 1.
        std::cout << "********Could not open the file!********" << std::endl;
        return EXIT_FAILURE;
    }
}

/**
* Функция записи текущего списка в файл.
* Если файл был не пустым, то вся информация будет перезаписана.
*/
int Universities::writeToFileBinary(const std::string &path)
{
    if (_universities.size() == 0)
    {
        std::cout << "List is empty!" << std::endl;
        return EXIT_FAILURE;
    }

    // Открываем файл на запись out, добавляем флаг binary
    std::ofstream file(path, std::ostream::out | std::ostream::binary);
    if (file.is_open())
    {
        // Читаем список до конца, берем данные и пишем в файл.
        for (size_t i = 0; i < _universities.size(); ++i)
        {
            // Записываем название вуза + длину названия
            size_t sizeName = _universities[i]->getName().length();
            std::string name = _universities[i]->getName();

            // Записываем год, кол-во факультетов и студентов
            int year = _universities[i]->getFoundationYear();
            int students = _universities[i]->getStudentCount();
            int faculties = _universities[i]->getFacultyCount();

            /**
             *  Пишем в бинарном формате все данные класса
             *  Конструкция выглядит следующим образом, параметры
             *  1)ссылка на переменную приведенная в char*, 2)размер типа переменной
             */
            file.write((char *)&sizeName, sizeof(size_t));
            file.write(name.data(), sizeName);

            file.write((char *)&year, sizeof(int));
            file.write((char *)&students, sizeof(int));
            file.write((char *)&faculties, sizeof(int));
        }
        // Закрываем файл после записи
        file.close();
        std::cout << "********File successfull wrote!********" << std::endl;
        return EXIT_SUCCESS;
    }
    else
    {
        // Если файл не смогли прочесть, тогда печатаем сообщение и возвращаем 1.
        std::cout << "********Could not open the file!********" << std::endl;
        return EXIT_FAILURE;
    }
}

/**
* Читает файл и преобразует строку из файла в объект класса.
*/
int Universities::readFromFile(const std::string& path)
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
        // Возвращаем 0, если успешно прочитали.
        return EXIT_SUCCESS;
    }
    else
    {
        // Если файл не смогли прочесть, тогда сообщение и выход с ошибкой.
        std::cout << "********Could not open the file!********" << std::endl;
        // Иначе возвращаем 1
        return EXIT_FAILURE;
    }
}

/**
* Читает файл и преобразует строку из файла в объект класса.
*/
int Universities::readFromFileBinary(const std::string &path)
{
    // Чистим весь текущий список.
    _universities.clear();

    // Ниже, переменные, куда будем записывать значения из файла.
    std::string name;
    // Длина имени, необходимо для бинарного чтения
    size_t nameSize;
    // Буфер для записи байтов из файла
    char buffer[255];
    int foundationYear = 1;
    int facultyCount = 1;
    int studentCount = 1;

    // Открываем файл на чтение
    std::ifstream file(path, std::ifstream::in | std::ifstream::binary);
    if (file.is_open())
    {
        size_t readedBytes = 0;
        size_t fSize = file_size(path);
        // Читаем файл, пока он не дошел до конца.
        do
        {
            // Порядок чтения из файла, должен быть таким же как и при записи.
            // Читаем информацию о длине имени
            file.read((char *)&nameSize, sizeof(size_t));
            // Читаем n байтов имени
            file.read(buffer, nameSize);
            // Чистим буфер
            buffer[nameSize] = 0;
            name = buffer;
            // год
            file.read((char *)&foundationYear, sizeof(int));
            // кол-во студентов
            file.read((char *)&studentCount, sizeof(int));
            // кол-во факультетов
            file.read((char *)&facultyCount, sizeof(int));
            // Создаем объект, который будем добавлять в список
            University *university = new University(name,
                                                    foundationYear,
                                                    facultyCount,
                                                    studentCount);
            // Помещаем прочитанный объект в список.
            _universities.addEnd(university);
            // Суммируем прочитанные байты.
            readedBytes += sizeof(size_t);
            readedBytes += nameSize;
            readedBytes += sizeof(int) * 3;
            // Как только достигли длины файла, завершаем чтение.
            if (fSize == readedBytes)
                break;
        } while (true);
        // Закрываем файл
        file.close();

        std::cout << "********File successfull read!********" << std::endl;
        // Возвращаем 0, если успешно прочитали.
        return EXIT_SUCCESS;
    }
    else
    {
        // Если файл не смогли прочесть, тогда сообщение и выход с ошибкой.
        std::cout << "********Could not open the file!********" << std::endl;
        // Иначе возвращаем 1
        return EXIT_FAILURE;
    }
}

/**
 * Метод, который ищет объект в списке по индексу, строит его и возвращает.
 * Необходимо, чтобы заполнить поля в контролах.
 */
University *Universities::loadInfo(const size_t &index)
{
    // Создаем переменную в которую будем писать объект.
    University *pUniversity = nullptr;
    // Ищем объект по индексу.
    for (size_t i = 0; i < _universities.size(); ++i)
    {
        // Если индекс найден, то записываем в объект данные.
        // Соответственно nullptr сменится на существующий адрес в памяти.
        if (i == index)
        {
            pUniversity = _universities[i];
            // Завершаем цикл, как только нашли нужный индекс.
            break;
        }
    }
    // Возвращаем указатель на nullptr если индекс не найден, или на данные.
    return pUniversity;
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
}

size_t Universities::getSize()
{
    return _universities.size();
}

void Universities::clear()
{
    _universities.clear();
}
