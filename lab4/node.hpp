#pragma once

#include "university.hpp"

/**
* Элемент двунаправленного списка.
*/
struct Node
{
    // Указатель на следующий элемент.
    Node *pNext { nullptr };

    // Указатель на предыдущий элемент.
    Node *pPrev { nullptr };

    // Данные об университете.
    University *data { nullptr };
};
