#include "XML_document.h"


int main() {
    XML_document* doc = new XML_document();

    doc->load("./test.txt");
    doc->print();

    return 0;
}