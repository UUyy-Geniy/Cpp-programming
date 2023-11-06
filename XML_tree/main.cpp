#include "XML_resource.h"
int main() {
    /*auto T = XML_resource::create();
    T->load("./test.txt");
    T->print();
    T->save("./save_test.xml");*/

    auto T = XML_resource::create("./test.txt");
    auto it = T->begin();
    auto en = T->end();
    while (it != en) {
        std::cout << it->getTag() << std::endl;
        it++;
    }

    return 0;
};