#include "XML_resource.h"

std::unique_ptr<XML_resource> XML_resource::create()
{
	return std::unique_ptr<XML_resource>(new XML_resource());
}

std::unique_ptr<XML_resource> XML_resource::create(const std::string& path) {
	std::unique_ptr<XML_resource> instance = XML_resource::create();
	instance->load(path);
	return instance;
};

bool XML_resource::load(const std::string& path)
{
	return document->load(path);
}

void XML_resource::save(const std::string& path)
{
	document->save(path);
}

void XML_resource::print()
{
	document->print();
}

Iterator XML_resource::begin() {
	return document->begin();
};
Iterator XML_resource::end() {
	return document->end();
};
