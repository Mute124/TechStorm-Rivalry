#pragma once
#include <algorithm>
#include <iostream>
#include <list>

class Listable {
public:
    virtual ~Listable() = default;

    template <typename T>
    void AddToList(std::list<T>& list) {
        
    }

    void CreateList() {
        
    }

    private:

        std::list
};
