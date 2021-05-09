#ifndef WINDOWS_ATTRS_HPP
#define WINDOWS_ATTRS_HPP

// Заголовочный файл для работы с windows api only windows
#include <windows.h>

// Qt debug
#include <QDebug>
#include <QDir>

// std
#include <string>

class WindowsAttrs
{
public:
    WindowsAttrs();
    // Разбираем файлы согласно заданию.
    QStringList parseFiles(const QDir &dir);

};

#endif // WINDOWS_ATTRS_HPP
