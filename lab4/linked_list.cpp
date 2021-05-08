#include "linked_list.hpp"

void DoublyLinkedList::addEnd(University *university)
{
    // Создаем новый элемент.
    Node* newNode = new Node();
    newNode->data = university;
    newNode->pNext = nullptr;
    newNode->pPrev = nullptr;

    // Проверяем, список на пустоту.
    if (isEmpty())
    {
        /**
         * Когда список пустой, тогда присваиваем на
         * голову и хвост созданный элемент.
         */
        head = newNode;
        tail = newNode;
    }
    else
    {
        /**
         * Текущий head является первым, поэтому ставим на его pNext
         * на новый элемент.
         */
        head->pNext = newNode;
        // На pPrev ставим предыдущий head
        newNode->pPrev = head;
        // Смещаем голову списка на newNode, новый элемент становится головой.
        head = newNode;
    }

    // Увеличиваем количество элементов в списке.
    ++_count;
}

void DoublyLinkedList::showList()
{
    // Задаем текущему элементу хвост списка т.е первый элемент.
    auto current = tail;
    /**
     * Как только pNext == nullptr, значит дошли до головного элемента и список
     * завершился. Пока pNext != nullptr, смещаем указатель.
     */
    while (current != nullptr)
    {
        //std::cout << current->data << std::endl;
        // Сдвигаем элементы, перемещая указатель на следующий элемент.
        current = current->pNext;
    }
}

University *DoublyLinkedList::operator[](int index)
{
    if (isEmpty())
    {
        std::cout << "List is empty! Nothing to update!" << std::endl;
        return nullptr;
    }

    if (index > _count - 1 || index < 0)
    {
        std::cout << "Index out of range" << std::endl;
        return nullptr;
    }

    // Ставим указатель первого элемента на current
    Node* current = tail;

    // Смещаем указатель на заданный индекс.
    for (int i = 0; i != index; ++i)
    {
        current = current->pNext;
    }
    return current->data;
}

size_t DoublyLinkedList::size()
{
    return _count;
}

void DoublyLinkedList::removeHead()
{
    if (head == nullptr)
    {
        std::cout << "List is empty! Nothing to remove!" << std::endl;
        return;
    }

    // Берем адрес головы.
    Node* current = head;
    if (_count == 1)
    {
        head = nullptr;
        tail = nullptr;
        delete current;
    }
    else
    {
        // Смещаем голову на предыдущий элемент, теперь он становится первым.
        head = current->pPrev;
        // Изменяем указатель pNext на nullptr, тем самым обрывая список.
        head->pNext = nullptr;
        // Освобождаем память текущей головы.
        delete current;
    }
    --_count;
}

void DoublyLinkedList::removeTail()
{
    if (tail == nullptr)
    {
        std::cout << "List is empty! Nothing to remove!" << std::endl;
        return;
    }

    // Алгоритм тот же, что и для головы, только теперь для хвоста.
    Node* current = tail;
    if (_count == 1)
    {
        head = nullptr;
        tail = nullptr;
        delete current;
    }
    else
    {
        tail = current->pNext;
        tail->pPrev = nullptr;
        delete current;
    }
    --_count;
}

void DoublyLinkedList::remove(int index)
{
    if (isEmpty())
    {
        std::cout << "List is empty! Nothing to remove!" << std::endl;
        return;
    }

    if (index > _count - 1 || index < 0)
    {
        std::cout << "Index out of range" << std::endl;
        return;
    }

    // Особый случай, если удаляем первый элемент.
    if (index == 0)
    {
        removeTail();
    }
    // Особый случай, если удаляем последний элемент т.е голову списка.
    else if (index == _count - 1)
    {
        removeHead();
    }
    else
    {
        // Задаем переменную для работу с указателем.
        Node* current = tail;
        for (int i = 0; i != index; ++i)
        {
            current = current->pNext;
        }
        auto prev = current->pPrev;
        auto next = current->pNext;
        prev->pNext = next;
        delete current;
        --_count;
    }
}

void DoublyLinkedList::clear()
{
    if (tail == nullptr)
    {
        //std::cout << "List is empty! Nothing to clear!" << std::endl;
        return;
    }

    // Создаем переменную для временного хранения следующего элемента.
    Node* tmpNext = tail;
    while (_count != 0)
    {
        // Записываем следующий элемент во временную переменную.
        tmpNext = tail->pNext;
        // Удаляем участок динамической памяти.
        delete tail;
        // Смещаем указатель хвоста на следующий элемент.
        tail = tmpNext;
        // Уменьшаем количество элемента в списке.
        --_count;
    }
    head = nullptr;
}

bool DoublyLinkedList::isEmpty()
{
    return head == nullptr;
}
