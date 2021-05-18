#include "file_worker.hpp"

/**
* Функция записи текущего списка в файл.
* Если файл был не пустым, то вся информация будет перезаписана.
*/
int FileWorker::writeToFile(const std::string& path,
                            const std::string& data)
{
    if (data.empty())
        return EXIT_FAILURE;

    std::ofstream file;
    // Открываем файл на запись
    file.open(path, std::ios::out);

    if (file.is_open())
    {
        std::istringstream dataStream(data);
        std::string line;
        while(std::getline(dataStream, line))
        {
            auto v = QString::fromStdString(line).split(' ');
            // skip empty string
            if (v.size() == 1 and v.at(0) == "")
                continue;

            for(const auto& item : v)
            {
                file << item.toStdString() << ';';
            }
            file << std::endl;
        }
        file.close();
        qDebug() << "********File successfull wrote!********";
        return EXIT_SUCCESS;
    }
    else
    {
        // Если файл не смогли прочесть, тогда печатаем сообщение и возвращаем 1.
        qDebug() << "********Could not open the file!********";
        return EXIT_FAILURE;
    }
}

/**
* Читает файл и преобразует строку из файла в объект класса.
*/
int FileWorker::readFromFile(const std::string& path,
                             QString& outText)
{
    std::string line = "";

    std::ifstream file;
    // Открываем файл на чтение
    file.open(path, std::ios::in | std::ios::binary);

    if (file.is_open())
    {
        file >> line;
        // Читаем файл, пока он не дошел до конца.
        while (file)
        {
            // parse to stream
            std::istringstream dataStream(line);
            QString outLine = QString::fromStdString(dataStream.str());
            // change string to simple
            outText.append(outLine
                           .remove(outLine.size() - 1, 1)
                           .replace(';', ' '));
            // linebreak
            outText += '\n';
            // Читаем следующую строку.
            file >> line;
        }

        file.close();
        qDebug() << "********File successfull read!********";
        // Возвращаем 0, если успешно прочитали.
        return EXIT_SUCCESS;
    }
    else
    {
        // Если файл не смогли прочесть, тогда сообщение и выход с ошибкой.
        qDebug() << "********Could not open the file!********";
        // Иначе возвращаем 1
        return EXIT_FAILURE;
    }
}

// --------------------------------------------------------------------------

/**
* Функция записи текущего списка в файл.
* Если файл был не пустым, то вся информация будет перезаписана.
*/
int FileWorker::writeToFileBinary(const std::string& path,
                                  const std::string& data)
{
    if (data.empty())
        return EXIT_FAILURE;

    // Открываем файл на запись out, добавляем флаг binary
    std::ofstream file(path, std::ostream::out | std::ostream::binary);
    if (file.is_open())
    {
        std::istringstream dataStream(data);
        std::string line;
        while(std::getline(dataStream, line))
        {
            size_t sizeString = line.length();
            file.write((char*)&sizeString, sizeof(size_t));
            file.write(line.data(), sizeString);
        }
        // Закрываем файл после записи
        file.close();
        qDebug() << "********File successfull wrote!********";
        return EXIT_SUCCESS;
    }
    else
    {
        // Если файл не смогли прочесть, тогда печатаем сообщение и возвращаем 1.
        qDebug() << "********Could not open the file!********";
        return EXIT_FAILURE;
    }
}

/**
* Читает файл и преобразует строку из файла в объект класса.
*/
int FileWorker::readFromFileBinary(const QString& path,
                                   QString& outText)
{
    // Длина имени, необходимо для бинарного чтения
    size_t stringSize;
    // Буфер для записи байтов из файла
    char buffer[255];

    // Открываем файл на чтение
    std::ifstream file(path.toStdString(), std::ifstream::in | std::ifstream::binary);
    if (file.is_open())
    {
        size_t readedBytes = 0;
        QFile qFile(path);
        size_t fSize = qFile.size();
        // Читаем файл, пока он не дошел до конца.
        do
        {
            // Порядок чтения из файла, должен быть таким же как и при записи.
            // Читаем информацию о длине имени
            file.read((char*)&stringSize, sizeof(size_t));
            // read n string bytes
            file.read(buffer, stringSize);
            // Чистим буфер
            buffer[stringSize] = 0;
            outText.append(buffer);
            // Суммируем прочитанные байты.
            readedBytes += sizeof(size_t);
            readedBytes += stringSize;
            // Как только достигли длины файла, завершаем чтение.
            if (fSize == readedBytes)
                break;
            outText += '\n';
        } while (true);
        // Закрываем файл
        file.close();

        qDebug() << "********File successfull read!********";
        // Возвращаем 0, если успешно прочитали.
        return EXIT_SUCCESS;
    }
    else
    {
        // Если файл не смогли прочесть, тогда сообщение и выход с ошибкой.
        qDebug() << "********Could not open the file!********";
        // Иначе возвращаем 1
        return EXIT_FAILURE;
    }
}
