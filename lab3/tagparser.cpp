#include "tagparser.hpp"

// Перегруженный конструктор, записываем контент для разбора.
TagParser::TagParser(QString data)
    : _data(data)
{
}

QString TagParser::parseHTML(QString openTag, QString closeTag)
{
    // Переменная в которую будем писать информацию о тегах.
    QString message = "";
    int current = 0;
    // Поскольку тегов может быть много, то заведем вектор, в котором будем
    // хранить номера символов с которых начинается открывающий тег.
    std::vector<int> v;

    // Находим все открывающие теги и помещаем их позиции в вектор.
    while (true)
    {
        current = _data.indexOf(openTag, current);
        if (current == -1)
            break;
        v.emplace_back(current);
        current += openTag.length();
    }

    // Начинаем разбирать элементы вектора.
    for(auto const &item : v)
    {
        // Записываем позиция + длина тега, чтобы начать поиск с этой позиции в строке.
        int currentPosition = item + openTag.length();
        int startPosition = currentPosition;
        // Начинаем поиск открывающей скобки
        while (true)
        {
            if (_data[currentPosition] == '<' ||
                _data.length() == currentPosition)
            {
                // Если открывающая скобка найдена, проверяем тег который начинается с нее.
                // Если тег совпадает с искомым, значит все верно.
                if (closeTag == _data.mid(currentPosition, closeTag.length()))
                {
                    // Когда оба тега верны, формируем строку для файла.
                    message += "Close and open tags is correct!\n";
                    message += openTag;
                    message += _data.mid(startPosition, currentPosition - startPosition);
                    message += closeTag + "\n\n";
                }
                // Если иначе, то сообщаем об ошибке и указываем позицию строки
                // открывающего тега, для которого неправильный закрывающий.
                else
                {
                    // Считаем количество переносов сначала до текущего символа.
                    // Чтобы узнать номер строки.
                    auto stringNumber = _data
                            .left(startPosition - 1)
                            .count('\n');
                    message += "Close tag " +
                            closeTag +" is incorrect!\nOpen tag at line №: " +
                            QString::number(++stringNumber) + "\n\n";
                }
                break;
            }
            ++currentPosition;
        }
    }

    return message;
}
