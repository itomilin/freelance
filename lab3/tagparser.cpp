#include "tagparser.hpp"

// Перегруженный конструктор, записываем контент для разбора.
TagParser::TagParser(QString data)
    : _data(data)
{
}

QString TagParser::findAllH1()
{
    QString message = "";
    auto openPosition = 0;
    int current = 0;
    std::vector<int> v;
    while (true)
    {
        current = _data.indexOf(_tagH1Open, current);
        if (current == -1)
            break;
        v.emplace_back(current);
        openPosition = current;
        current += _tagH1Open.length();
    }

    if (openPosition != -1)
    {
        std::cout << "Found open tag" << std::endl;
    }
    else
    {
        message += "Open tag not found!";
    }

    if (openPosition != -1)
    {
        // Записываем позиция + длина тега, чтобы начать поиск с этой позиции в строке.
        bool isCorrectCloseTag = false;
        int currentPosition = openPosition + _tagH1Open.length();
        int startPosition = currentPosition;
        while (true)
        {
            auto t = _data[currentPosition];
            if (_data[currentPosition] == '<')
            {
                if (_tagH1Close == _data.mid(currentPosition, _tagH1Close.length()))
                {
                    message = "Close and open tags is correct!\n";
                    message += _tagH1Open;
                    message += _data.mid(startPosition, currentPosition - startPosition);
                    message += _tagH1Close;
                    isCorrectCloseTag = true;
                }
                else
                {
                    // Считаем количество переносов сначала до текущего символа.
                    // Чтобы узнать номер строки.
                    auto stringNumber = _data
                            .left(currentPosition + _tagH1Close.length())
                            .count('\n');
                    message += "Close tag is incorrect!\nLine number is: " +
                            QString::number(stringNumber);
                }
                break;
            }
            ++currentPosition;
        }
    }

    return message;
}

// Метод для разбора тегов согласно варианту.
QString TagParser::parseFile()
{
    QString message = "";
    bool foundOpenTag = false;
    // Ищем совпадение в тексте по строке открывающего тега.
    // Если совпадение не найдено, возвращает -1
    auto openPosition = _data.indexOf(_tagTitleOpen);

    if (openPosition != -1)
    {
        std::cout << "Found open tag" << std::endl;
    }
    else
    {
        message += "Open tag not found!";
    }

    if (openPosition != -1)
    {
        // Записываем позиция + длина тега, чтобы начать поиск с этой позиции в строке.
        bool isCorrectCloseTag = false;
        int currentPosition = openPosition + _tagTitleOpen.length();
        int startPosition = currentPosition;
        while (true)
        {
            auto t = _data[currentPosition];
            if (_data[currentPosition] == '<')
            {
                if (_tagTitleClose == _data.mid(currentPosition, _tagTitleClose.length()))
                {
                    message = "Close and open tags is correct!\n";
                    message += _tagTitleOpen;
                    message += _data.mid(startPosition, currentPosition - startPosition);
                    message += _tagTitleClose;
                    isCorrectCloseTag = true;
                }
                else
                {
                    // Считаем количество переносов сначала до текущего символа.
                    // Чтобы узнать номер строки.
                    auto stringNumber = _data
                            .left(currentPosition + _tagTitleClose.length())
                            .count('\n');
                    message += "Close tag is incorrect!\nLine number is: " +
                            QString::number(stringNumber);
                }
                break;
            }
            ++currentPosition;
        }
    }

    return message;
}
