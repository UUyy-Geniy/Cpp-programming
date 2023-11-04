#pragma once
#include "XML_document.h"

class XML_resource
{
private:
	std::unique_ptr<XML_document> document;
	XML_resource() : document(std::make_unique<XML_document>()) {};
public:
	static std::unique_ptr<XML_resource> create();

	bool load(const std::string& path);
	void save(const std::string& path);
	void print();


	~XML_resource() = default;
	XML_resource(const XML_resource&) = delete;
	XML_resource(XML_resource&&) = delete;
	XML_resource& operator = (const XML_resource&) = delete;
	XML_resource& operator = (XML_resource&&) = delete;
};

