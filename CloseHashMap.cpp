#include "CloseHashMap.h"


template <class Type>
CloseHashMap<Type>::CloseHashMap(int size_) {
    this->cur_size = 0;
    this->size = size_;
    HashMapItem<Type> item;
    for (int i = 0; i < size_; i++) {
        this->data.push_back(item);
    }
//        std::fill(this->data.begin(), this->data.end(), item);

}

template <class Type>
void CloseHashMap<Type>::resize(int new_size) {
    std::vector< HashMapItem< Type> > new_data;

    HashMapItem<Type> item;
    for (int i = 0; i < new_size; i++) {
        new_data.push_back(item);
    }

    for (auto item : this->data) {
        if (item.isInit()) {
            bool pushed = false;
            int hash_ = this->get_hash(item.get_key(), new_size);

            for (int i = hash_; i < new_size; i++) {
                if (!new_data[hash_].isInit()) {
                    HashMapItem<Type> new_item(item.get_key(), item.get_value(), true);
                    new_data[hash_] = new_item;
                    pushed = true;
                }
                if (pushed) {
                    break;
                }
            }

            for (int i = 0; i < hash_; i++){
                if (!new_data[hash_].isInit()) {
                    HashMapItem<Type> new_item(item.get_key(), item.get_value(), true);
                    new_data[hash_] = new_item;
                    pushed = true;
                }
                if (pushed) {
                    break;
                }
            }
        }
    }
    this->data = new_data;
    this->size = new_size;

}

template <class Type>
void CloseHashMap<Type>::push(std::string key_, Type data_) {
    if (this->size / (this->cur_size + 1) <= 8 and this->enable_resize) {
        this->resize(size * 8);
    }
    u_int32_t hash_ = this->get_hash(key_, this->size);


//    std::cout<<"close hash map push. hash = "<<hash_<<'\n';
    if (this->is_key(key_)) {
        return;
    }

    for (int i = hash_; i < this->size; i++) {
        if (!this->data[hash_].isInit()) {
            HashMapItem<Type> item(key_, data_, true);
            this->data[hash_] = item;
            return;
        }
    }

    for (int i = 0; i < hash_; i++){
        if (!this->data[hash_].isInit()) {
            HashMapItem<Type> item = HashMapItem(key_, data_, true);
            this->data[hash_] = item;
            return;
        }
    }
}

template <class Type>
void CloseHashMap<Type>::erase(std::string key_) {
    u_int32_t hash_ = this->get_hash(key_, this->size);
    for (int i = hash_; i < this->size; i++) {
        if (!this->data[hash_].isInit())
            return;

        if (this->data[hash_].get_key() == key_) {
            this->data[hash_].init = false;
            return;
        }
    }

    for (int i = 0; i < hash_ - 1; i++){
        if (!this->data[hash_].isInit())
            return;

        if (this->data[hash_].get_key() == key_) {
            this->data[hash_].init = false;
            return;
        }
    }
}




template <class Type>
bool CloseHashMap<Type>::is_key(std::string key_) {
    u_int32_t hash_ = this->get_hash(key_, this->size);
    for (int i = hash_; i < this->size; i++) {
        if (!this->data[hash_].isInit())
            return false;

        if (this->data[hash_].get_key() == key_)
            return true;
    }

    for (int i = 0; i < hash_ - 1; i++){
        if (!this->data[hash_].isInit())
            return false;
        if (this->data[hash_].get_key() == key_)
            return true;
    }
    return false;
}

template <class Type>
Type &CloseHashMap<Type>::operator[](std::string key_) {
    int hash_ = this->get_hash(key_, this->size);

    for (int i = hash_; i < this->size; i++) {
        if (this->data[hash_].get_key() == key_)
            return this->data[hash_].data;
    }

    for (int i = 0; i < hash_ - 1; i++){
        if (!this->data[hash_].isInit())
            throw std::out_of_range("no such element");

        if (this->data[hash_].get_key() == key_)
            return this->data[hash_].data;
    }

    throw std::out_of_range("no such element");
}

template <class Type>
u_int32_t CloseHashMap<Type>::get_hash(std::string str, int hash_len) {
    return this->get_mod_hash(str, hash_len);
}

template <class Type>
u_int32_t CloseHashMap<Type>::get_mod_hash(const std::string& str, int hash_len) {
    long long hash_ = 0;
    int power = 263;
    long long cur_value_exp = 1;

    for (char i : str) {
        cur_value_exp *= power;
        hash_ += int(i) * cur_value_exp;
    }

    int value = int((abs(hash_) % 1000000007) % hash_len);
    return value;
}
