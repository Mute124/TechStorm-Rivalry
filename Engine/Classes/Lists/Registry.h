#pragma once

#include "../../DataSets/ListEntry.h"



#include <stdio.h>
#include <stdlib.h>
#include <vector>

template <typename T>
class Registry
{
public:


    Registry() {}

    ListEntry<T> GetEntryById(int id) {
        return registry[id];
    }

    void RemoveEntryById(int id) {
        registry.erase(id);
    }

    void Register(ListEntry<T> *Entry) {
        registry.push_back(Entry);

    }

private:

    std::vector<ListEntry<T>> registry;
};
