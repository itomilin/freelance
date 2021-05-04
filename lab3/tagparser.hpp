#ifndef TAGPARSER_HPP
#define TAGPARSER_HPP

#include <QString>
#include <iostream>
#include <QStringList>
#include <vector>

class TagParser
{
public:
    TagParser() = default;
    // Перегруженный конструктор, устанавливает значение для поля.
    TagParser(QString data);
    ~TagParser() = default;

    QString parseHTML(QString openTag, QString closeTag);

private:
    // Храним контент страницы.
    const QString _data;
};

#endif // TAGPARSER_HPP
