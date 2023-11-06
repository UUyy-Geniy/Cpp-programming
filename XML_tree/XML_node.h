#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <functional>

class Iterator;

class XML_node {
private:
    int numberInChildren(XML_node* element) const;
public:
    std::vector<std::unique_ptr<XML_node>> children;
    std::string tag;
    std::string value;
    XML_node* parent;
    XML_node(const std::string& tag, const std::string& value, XML_node* parent_) : tag(tag), value(value), parent(parent_) {}
    void add(std::unique_ptr<XML_node> child);
    std::string stringify(const int = 0);
    void for_each(std::function<void(const XML_node&)> callback);
    XML_node* next();
    std::string getValue() const;
    std::string getTag() const;
    Iterator begin();
    Iterator end();
    void erase(Iterator& it) noexcept;
};

class Iterator : std::iterator<std::input_iterator_tag, XML_node> {
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
    void deleteNode();
};