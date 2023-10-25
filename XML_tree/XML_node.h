#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <functional>


class XML_node {
public:
    std::string tag;
    std::string value;
    std::vector<std::unique_ptr<XML_node>> children;

    XML_node(const std::string& tag, const std::string& value) : tag(tag), value(value) {}
    void append(std::unique_ptr<XML_node> child);
    std::string stringify(const int = 0);
    void for_each(std::function<void(const XML_node&)> callback);
};