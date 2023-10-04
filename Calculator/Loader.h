#pragma once
#include <string>

class Loader {
private:
    Loader();
public:
    Loader(const Loader&) = delete;
    Loader& operator=(Loader const&) = delete;
    Loader(Loader&&) = delete;
    Loader& operator=(Loader&&) = delete;

    static Loader& getInstance();

};

