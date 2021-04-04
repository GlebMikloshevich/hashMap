#include <iostream>
#include "HashMapItem.h"


template <class Type>
HashMapItem<Type>::HashMapItem(std::string key_, Type data_) {
    this->data = data_;
    this->key = key_;
    this->init = true;
}

template <class Type>
HashMapItem<Type>::HashMapItem(std::string key_, Type data_, bool init_) {
    this->data = data_;
    this->key = key_;
    this->init = init_;
}


template <class Type>
HashMapItem<Type>::~HashMapItem() = default;

template <class Type>
std::string HashMapItem<Type>::get_key() {
    return this->key;
}

template <class Type>
Type HashMapItem<Type>::get_value() {
    return this->data;
}
