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

Iterator XML_resource::find(std::function<bool(XML_node* node)> callback) {
	return document->find(callback);
};

Iterator XML_resource::find_by_tag(const std::string& tag) {
	return document->find_by_tag(tag);
};
Iterator XML_resource::find_by_value(const std::string& tag) {
	return document->find_by_value(tag);
};

bool XML_resource::add(std::string const& tag, std::string const& value, Iterator it) noexcept {
	bool res = true;
	res = document->add(tag, value, it);
	if (!res) std::cerr << "Adding " << tag << " with value " << value << " is failed!" << std::endl;
	return res;
};
bool XML_resource::erase(Iterator it) {
	return document->erase(it);
};