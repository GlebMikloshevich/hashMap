#ifndef HASHMAP_HASHMAPITEM_H
#define HASHMAP_HASHMAPITEM_H
#include <string>
#include <vector>
template <class Type>
class HashMapItem {

private:
    std::string key;
    Type data;
    bool init = false;



public:
    std::string get_key();
    Type get_value();
    bool isInit() {return this->init;}
    HashMapItem()= default;
    HashMapItem(std::string key_, Type data_);
    HashMapItem(std::string key_, Type data_, bool init);
    ~HashMapItem();
    template <class T> friend class OpenHashMap;
    template <class T> friend class CloseHashMap;
};


#endif //HASHMAP_HASHMAPITEM_H
