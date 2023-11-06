#pragma once
#include "XML_document.h"
class XML_resource
{
private:
	std::unique_ptr<XML_document> document;
	XML_resource() : document(std::make_unique<XML_document>()) {};
public:
	static std::unique_ptr<XML_resource> create();
	static std::unique_ptr<XML_resource> create(const std::string& path);
	bool load(const std::string& path);
	void save(const std::string& path);
	void print();
	
	Iterator begin();
	Iterator end();
	Iterator find(std::function<bool(XML_node* node)> callback);
	Iterator find_by_tag(const std::string& tag);
	Iterator find_by_value(const std::string& value);
	bool add(std::string const& tag, std::string const& value, Iterator it) noexcept;
	bool erase(Iterator it);
	
	~XML_resource() = default;
	XML_resource(const XML_resource&) = delete;
	XML_resource(XML_resource&&) = delete;
	XML_resource& operator = (const XML_resource&) = delete;
	XML_resource& operator = (XML_resource&&) = delete;
};

