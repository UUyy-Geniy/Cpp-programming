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

int XML_node::numberInChildren(XML_node* element) const
{
    for (int i = 0; i < children.size(); i++)
        if (element == children[i].get())
            return i;
    return -2;
}

XML_node* XML_node::take_ptr()
{
    XML_node* father = this;
    while (father->children.size() != 0)
        father = father->children[0].get();
    return father;
}

XML_node* XML_node::next()
{
    XML_node* father = parent;
    XML_node* ptr = this;
    if (father != nullptr)
    {
        int i = father->numberInChildren(this);
        if (i == father->children.size() - 1)
            return father;
        else
            return father->children[i + 1].get()->take_ptr();
        father = father->parent;
    }
    return nullptr;
}