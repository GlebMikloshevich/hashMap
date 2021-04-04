#ifndef HASHMAP_OPENHASHMAP_H
#define HASHMAP_OPENHASHMAP_H
#include "HashMapItem.h"
#include "HashMapItem.cpp"
#include <string>
#include <cstdint>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
template <class Type>
class OpenHashMap {
    //TODO change int to uint types
private:
    uint32_t cur_size;
    uint32_t size;
    void resize(int new_size);
    int get_hash(std::string str, int hash_len); //static to Hash Map Item
    bool enable_resize = false; //TODO enable resize

public:
    std::vector<std::vector< HashMapItem< Type> > > data; //TODO set private
    uint32_t get_size(){return this->cur_size;}
    explicit OpenHashMap(uint32_t size_ = 65535); //TODO change size_ 131072
//    OpenHashMap();
    void push(std::string key, Type data_);
    void erase(std::string key_);
    bool is_key(std::string key_);
    void set_value(std::string key_, Type data_);
    Type& operator[] (std::string key_);
    Type get_value(std::string key_);

    //SHOULD BE PRIVATE
    static int get_mod_hash(const std::string& str, int hash_len);
    static int get_mid_square_hash(const std::string& str, int hash_len);
    static int get_shift_hash(std::string str, int hash_len);

};




#endif //HASHMAP_OPENHASHMAP_H