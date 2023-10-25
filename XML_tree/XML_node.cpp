#include "XML_node.h"

void XML_node::append(std::unique_ptr<XML_node> child) {
	children.push_back(std::move(child));
}
std::string XML_node::stringify(const int depth) {
    const std::string indent = std::string(depth * 2, ' ');
    std::string result = "";

    result += indent + "<" + tag + ">" + value;
    if (children.size()) {
        result += "\n";
    }
    for (const auto& child : children) {
        result += child->stringify(depth + 1);
    }
    if (children.size()) {
        result += indent;
    }
    result += "</" + tag + ">" + "\n";

    return result;
}

void XML_node::for_each(std::function<void(const XML_node&)> callback) {
    callback(*this);
    for (const auto& child : children) {
        child->for_each(callback);
    }
}