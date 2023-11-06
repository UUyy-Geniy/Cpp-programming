#include "XML_document.h"

void XML_document::parse(const std::string& xml) {
	int pos = 0;
	root_node = parse_node(xml, pos, nullptr);
}

bool XML_document::load(const std::string& path) {
	const std::string xml = read_file(path);
	parse(xml);
	return true;
}

void XML_document::save(const std::string& path) {
	std::string xml = stringify();
	write_file(path, xml);
}

void XML_document::print() {
	std::string xml = stringify();
	std::cout << xml << std::endl;
}

void XML_document::for_each(std::function<void(const XML_node&)> callback) {
	root_node->for_each(callback);
}

std::unique_ptr<XML_node> XML_document::parse_node(const std::string& xml, int& pos, XML_node* parent) {
	std::string tag = get_next_tag(xml, pos);
	std::string value = get_next_value(xml, pos);
	std::unique_ptr<XML_node> node(new XML_node(tag, value, parent));

	std::string next_tag = get_next_tag(xml, pos);
	while (next_tag != ("/" + tag) && pos < xml.size()) {
		pos -= next_tag.size() + 2;
		node->add(parse_node(xml, pos, node.get()));
		next_tag = get_next_tag(xml, pos);
	}

	return node;
}

std::string XML_document::get_next_tag(const std::string& xml, int& pos) {
	pos = xml.find("<", pos) + 1;
	int end = xml.find(">", pos);
	std::string tag = xml.substr(pos, end - pos);
	pos = end + 1;
	return tag;
}

std::string XML_document::get_next_value(const std::string& xml, int& pos) {
	int start = pos;
	pos = xml.find("<", pos);
	return trim(xml.substr(start, pos - start));
}

std::string XML_document::read_file(const std::string& path) {
	std::ifstream file(path);

	if (!file) {
		throw std::runtime_error("File not found");
	}

	return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void XML_document::write_file(const std::string& path, const std::string& content) {
	std::ofstream file(path);

	if (!file) {
		throw std::runtime_error("File not found");
	}

	file << content;
}

std::string XML_document::stringify() {
	return root_node->stringify();
}

std::string XML_document::trim(const std::string& str) {
	std::string result = "";
	int start_pos = 0;
	int end_pos = str.length() - 1;


	for (; start_pos < str.length(); start_pos += 1) {
		char ch = str[start_pos];

		if (isspace(ch)) {
			continue;
		}
		else {
			break;
		}
	};
	for (; end_pos >= 0; end_pos -= 1) {
		char ch = str[end_pos];

		if (isspace(ch)) {
			continue;
		}
		else {
			break;
		}
	};

	return str.substr(start_pos, end_pos - start_pos + 1);
}

Iterator XML_document::begin() {
	return root_node->begin();
};

Iterator XML_document::end() {
	return root_node->end();
};

Iterator XML_document::find(std::function<bool(XML_node* node)> callback) {
	auto begin_ = begin();
	auto end_ = end();
	while (begin_ != end_) {
		if (callback(&*begin_)) {
			return begin_;
		}
		begin_++;
	}
};

Iterator XML_document::find_by_tag(const std::string& tag) {
	if (!root_node) {
		return end();
	}
	return find([&tag](XML_node* node) {
		return node->tag == tag;
	});
};
Iterator XML_document::find_by_value(const std::string& value) {
	if (!root_node) {
		return end();
	}
	return find([&value](XML_node* node) {
		return node->value == value;
	});
};

bool XML_document::add(std::string const& tag, std::string const& value, Iterator it) {
	if (!isIteratorValid(it)) return false;
	(*it).add(std::unique_ptr<XML_node>(new XML_node(tag, value, &(*it))));
	return true;
};

bool XML_document::isIteratorValid(Iterator it){
	auto begin_ = begin();
	auto end_ = end();
	if (it == end_) return false;
	while (begin_ != end_) {
		if (begin_ == it) return true;
		begin_++;
	}
	return false;
};

bool XML_document::erase(Iterator it)  {
	if (!isIteratorValid(it) || it == begin()) return false;
	root_node->erase(it);
	return true;
}
