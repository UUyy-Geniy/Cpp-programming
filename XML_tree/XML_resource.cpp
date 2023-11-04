#include "XML_resource.h"

std::unique_ptr<XML_resource> XML_resource::create()
{
	return std::unique_ptr<XML_resource>(new XML_resource());
}

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

