#include "Iterator.h"
void Iterator::next()
{
    XML_node* tmp = ptr->next();
    if (tmp)
    {
        ptr = tmp;
        return;
    }
    ptr = nullptr;
}