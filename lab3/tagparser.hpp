#ifndef TAGPARSER_HPP
#define TAGPARSER_HPP

#include <QString>
#include <iostream>
#include <QStringList>
#include <QRegExp>
#include <vector>

class TagParser
{
public:
    TagParser() = default;
    TagParser(QString data);
    ~TagParser() = default;

    QString parseFile();
    QString findAllH1();

private:
    // Храним контент страницы.
    const QString _data;

    // Открывающий и закрывающий теги для сравнения.
    const QString _tagTitleOpen { "<title>" };
    const QString _tagTitleClose { "</title>" };

    const QString _tagH1Open { "<h1>" };
    const QString _tagH1Close { "</h1>" };

    const QString _tagH2Open { "<h2>" };
    const QString _tagH2Close { "</h2>" };
};

#endif // TAGPARSER_HPP
