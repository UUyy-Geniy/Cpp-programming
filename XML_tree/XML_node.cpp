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

XML_node* XML_node::next()
{
    if (!children.empty()) {
        return children[0].get();
    }
    else {
        XML_node* currentNode = this;
        XML_node* parent = this->parent;
        while (parent != nullptr) {
            int index = parent->numberInChildren(currentNode);
            if (index < parent->children.size() - 1) {
                return parent->children[index + 1].get();
            }
            currentNode = parent;
            parent = currentNode->parent;
        }
    }
}

std::string XML_node::getValue() const
{
    return value;
}

std::string XML_node::getTag() const
{
    return tag;
}

Iterator XML_node::begin()
{
    return Iterator(this, nullptr);
}

Iterator XML_node::end()
{
    return Iterator(nullptr, nullptr);
}
