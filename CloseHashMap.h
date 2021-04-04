#ifndef HASHMAP_CLOSEHASHMAP_H
#define HASHMAP_CLOSEHASHMAP_H
#include "HashMapItem.h"
#include "HashMapItem.cpp"
#include <string>
#include <cstdint>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
template <class Type>
class CloseHashMap {
private:

    uint32_t cur_size;
    uint32_t size;
    void resize(int new_size);
    u_int32_t get_hash(std::string str, int hash_len);
    bool enable_resize = false; //TODO enable resize
public:
    explicit CloseHashMap(int size_ = 131072);
    std::vector< HashMapItem< Type> > data;
    void push(std::string key_, Type data_);
    void erase(std::string key_);
    bool is_key(std::string key_);
    Type& operator[] (std::string key_);


    static u_int32_t get_mod_hash(const std::string& str, int hash_len);

};


#endif //HASHMAP_CLOSEHASHMAP_H
