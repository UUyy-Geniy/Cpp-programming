#include "XML_node.h"
void Iterator::next()
{
    XML_node* tmp = ptr->next();
    if (tmp)
    {
        root = tmp->parent;
        ptr = tmp;
        return;
    }
    ptr = nullptr;
    root = nullptr;
}