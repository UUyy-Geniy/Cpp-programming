#include "XML_node.h"

class XML_document {
public:
    XML_document() : root_node(nullptr) {};
    void parse(const std::string& xml);
    bool load(const std::string& path);
    void save(const std::string& path);
    void print();
    void for_each(std::function<void(const XML_node&)> callback);
    Iterator find(std::function<bool(XML_node* node)>);
    Iterator find_by_tag(const std::string& tag);
    Iterator find_by_value(const std::string& value);
    bool add(std::string const& tag, std::string const& value, Iterator it);
    bool erase(Iterator it);
    Iterator begin();
    Iterator end();
private:
    std::unique_ptr<XML_node> root_node;
    std::unique_ptr<XML_node> parse_node(const std::string& xml, int& pos, XML_node* parent);
    std::string get_next_tag(const std::string& xml, int& pos);
    std::string get_next_value(const std::string& xml, int& pos);
    std::string read_file(const std::string& path);
    void write_file(const std::string& path, const std::string& content);
    std::string stringify();
    std::string trim(const std::string& str);
    bool isIteratorValid(Iterator it);
};
