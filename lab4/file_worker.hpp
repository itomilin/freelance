#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <fstream>
#include <sstream>

#include <QString>
#include <QDebug>
#include <QFile>

class FileWorker
{
public:
    FileWorker() = default;

    int readFromFile(const std::string& path,
                     QString& outText);

    int writeToFile(const std::string& path,
                    const std::string& data);

    int readFromFileBinary(const QString& path,
                           QString& outText);

    int writeToFileBinary(const std::string& path,
                          const std::string& data);


};

#endif // FILEREADER_HPP
