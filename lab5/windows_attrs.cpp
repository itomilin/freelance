#include "windows_attrs.hpp"

WindowsAttrs::WindowsAttrs()
{
}

/**
 * @brief WindowsAttrs::showAttrs Определяем атрибуты файла, используя win api
 * @param filename - абсолютный путь до файла
 */
QStringList WindowsAttrs::parseFiles(const QDir &dir)
{
    // Помещаем в список элементы для будущего отображения.
    QStringList filesWithAttrs;
    // Берем полный путь для дополнения.
    QString absolutePath = dir.absolutePath();
    // Формируем строку для вывода, похожим образом, как в команде attrs
    QString itemString = "";

    QStringList allDirFiles = dir.entryList(QStringList(), QDir::Hidden | QDir::AllEntries | QDir::NoDotAndDotDot);

    // Перебираем все элементы для выбранной директории.
    for(const auto &item : allDirFiles)
    {
        QString pathToFile = absolutePath + "/" + item;
        // Пишем в переменную атрибуты по переданному пути.
        DWORD d = GetFileAttributesA((LPCSTR)pathToFile.toStdString().c_str());

        // If directory
        if (d & FILE_ATTRIBUTE_DIRECTORY)
            itemString += "<DIR>";

        // У одного файла может быть несколько атрибутов, в win api атрибуты
        // заданы по битовой маске, поэтому используем побитовый оператор &
        if (d & FILE_ATTRIBUTE_ARCHIVE)
            itemString += "A";
        if (d & FILE_ATTRIBUTE_SYSTEM)
            itemString += "S";
        if (d & FILE_ATTRIBUTE_HIDDEN)
            itemString += "H";
        if (d & FILE_ATTRIBUTE_READONLY)
            itemString += "R";



        itemString += "\t\t" + pathToFile;
        // Разворачиваем слеши, чтобы путь как в Windows
        itemString.replace('/', '\\');
        filesWithAttrs.emplaceBack(itemString);
        // Чистим строку перед новой записью.
        itemString.clear();
    }

    return filesWithAttrs;
}
