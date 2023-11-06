#include "XML_resource.h"
int main() {
    auto T = XML_resource::create("./save_test.xml");
    T->save("./save_test.xml");
    auto it = T->begin();
    auto en = T->end();
    while (it != en) {
        std::cout << it->getTag() <<" - "<<it->getValue()<< std::endl;
        it++;
    }
    T->print();

    auto it_2 = T->find_by_tag("age");
    T->erase(it_2);
    T->print();

    auto it_begin = T->begin();
    T->add("height", "194", it_begin);
    T->print();

    T->save("./test_after_changing.xml");


    return 0;
};