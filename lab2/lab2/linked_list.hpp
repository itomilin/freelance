#pragma once

#include "node.hpp"
#include <iostream>

class DoublyLinkedList
{
public:
    DoublyLinkedList() = default;
    ~DoublyLinkedList() = default;

    // Очистка всех элементов списка.
    void clear();
    // Удаление элемента по индексу.
    void remove(int index);
    // Удаление первого элемента.
    void removeTail();
    // Удаление последнего элемента.
    void removeHead();

    // Показать количество элементов в списке.
    size_t size();
    // Вставить новый элемент в конец списка.
    void addEnd(University* university);
    // Изменить данные элемента по индексу. index - позиция, value - new данные
    void update(int index, University *value);

    // Показать весь список.
    void showList();

    // Перегрузим оператор взятия по индексу - [], чтобы обращаться к элементам
    University *operator[](int index);

private:
    // Проверка списка на пустоту.
    bool isEmpty();

    // Храним количество элементов в списке.
    int _count { 0 };
    // Храним первый элемент списка.
    Node *head { nullptr };
    // Храним последний элемент списка.
    Node *tail { nullptr };

};
