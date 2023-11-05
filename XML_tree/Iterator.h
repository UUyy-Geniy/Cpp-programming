#pragma once
#include <iostream>
#include "XML_node.h"
class Iterator:std::iterator<std::input_iterator_tag, XML_node>
{
private:
	pointer ptr;
	pointer root;
	void next();
public:
    Iterator(pointer ptr_, pointer root_) : ptr(ptr_), root(root_) {};
    reference operator*() { return *ptr; };
    pointer operator ->() { return ptr; };
    Iterator operator++ () { next(); return *this; };
    Iterator& operator++(int i) { Iterator tmp = *this; ++(*this); return tmp; };
    bool operator == (const Iterator& a) { return (a.ptr == ptr) && (a.root == root); };
    bool operator != (const Iterator& a) { return (a.ptr != ptr) || (a.root != root); };
};

