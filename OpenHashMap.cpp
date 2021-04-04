#include "OpenHashMap.h"

template <class Type>
 OpenHashMap<Type>::OpenHashMap(uint32_t size_) {
    this->cur_size = 0;
    this->size = size_;
    for (int i = 0; i < size_; i++) {
        std::vector< HashMapItem< Type> > row;
        this->data.push_back(row);
    }
}


template <class Type>
void OpenHashMap<Type>::push(std::string key_, Type data_) {
    if (this->size / (this->cur_size + 1) <= 8 and this->enable_resize) {
        this->resize(this->size * 8);
    }


    int hash = this->get_hash(key_, this->size);
//    std::cout<<key_<<": "<<hash<<'\n';
    bool key_is_found = this->is_key(key_);

    if (!key_is_found) {
        HashMapItem<Type> item = HashMapItem(key_, data_);
        this->data[hash].push_back(item);
        this->cur_size++ ;
//        std::cout<<"hash is "<<hash<<'\n';
    } else {
        //TODO throw an exception or call is_key()
    }
}


template <class Type>
void OpenHashMap<Type>::erase(std::string key_) {
    int hash = this->get_hash(key_, this->size);
    for (int i = 0; i < this->data[hash].size(); i++) {
        if (this->data[hash][i].get_key() == key_) {
            this->cur_size-- ;
            this->data[hash].erase(this->data[hash].begin()+i);
            return;
        }
    }
    //throw std::out_of_range("no such element");
}


template <class Type>
bool OpenHashMap<Type>::is_key(std::string key_) {
    int hash = this->get_hash(key_, this->size);
    for (auto item : this->data[hash])
        if (item.get_key() == key_)
            return true;
    return false;
}


template <class Type>
void OpenHashMap<Type>::set_value(std::string key_, Type data_) {
    int hash = this->get_hash(key_, this->size);

    for (auto& item: data[hash]) {
        if (item.get_key() == key_){
            item.data = data_;
            return;
        }
    }

    throw std::out_of_range("no such element"); //TODO check for this. maybe return
}

template<class Type>
Type &OpenHashMap<Type>::operator[](std::string key_) {
    int hash = this->get_hash(key_, this->size);
    bool key_is_found = this->is_key(key_);

    for (auto& item: data[hash]) {
        if (item.get_key() == key_){
            return item.data;
        }
    }
    throw std::out_of_range("no such element"); //TODO check for this. maybe return
}

template <class Type>
Type OpenHashMap<Type>::get_value(std::string key_) {
    int hash = this->get_hash(key_, this->size);

    for (auto& item: data[hash]) {
        if (item.get_key() == key_){
            return item.get_value();
        }
    }
    throw std::out_of_range("no such element");
}


template <class Type>
void OpenHashMap<Type>::resize(int new_size) {
    std::vector<std::vector< HashMapItem< Type> > > new_data;
    for (int i = 0; i < new_size; i++) {
        std::vector< HashMapItem< Type> > row;
        new_data.push_back(row);
    }

    for (auto vec : this->data) {
        for (auto item : vec) {
            int hash = this->get_hash(item.get_key(), new_size);
            HashMapItem<Type> new_item = HashMapItem(item.get_key(), item.get_value());
            new_data[hash].push_back(new_item);
        }
    }
    this->size = new_size;
    this->data = new_data; //TODO optimize it
}


template <class Type>
int OpenHashMap<Type>::get_hash(std::string str, int hash_len) {
//    return get_mid_square_hash(str, hash_len);
//    return this->get_mod_hash(str, hash_len);
    return get_shift_hash(str, hash_len);

}

template <class Type>
int OpenHashMap<Type>::get_mod_hash(const std::string& str, int hash_len) {
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

template <class Type>
int OpenHashMap<Type>::get_mid_square_hash(const std::string& str, int hash_len) {
    //16 bits
    uint64_t hash_ = 1;
    int power = 263;
    long long cur_value_exp = 1;
    int sixteen_bits_on = 65535; // 2^17 - 1
    for (char i : str) {
        cur_value_exp *= power;
        hash_ += int(i) * cur_value_exp;
    }
    hash_ *= hash_;
//    std::cout<<str<<' '<<hash_;
    int bits = 0;
    uint64_t tmp_hash = hash_;
    for (int i = 0;; i++) {
        if (tmp_hash == 0)
            break;
        tmp_hash >>= 1;
        bits++;
    }
//    std::cout<<str<<' '<<hash_<<' '<<bits<<' ';

    //TODO hash_ generator is not good
    if (bits <= 16) {
        return hash_;
    } else {
        int bits_to_skip = (bits - 16) / 2;
        hash_ >>=bits_to_skip;
//        std::cout<<(u_int16_t(hash_ & sixteen_bits_on)) % hash_len<<'\n';

        return (u_int16_t(hash_ & sixteen_bits_on)) % hash_len;
    }
}

template <class Type>
int OpenHashMap<Type>::get_shift_hash(std::string str, int hash_len) {
    u_int16_t hash_ = 0;
    u_int16_t x = 0;

    for (int i = 0; i < str.length(); i += 2) {
        x = (uint16_t(str[i])<<8) + uint16_t(str[i+1]);
        x = (x>>i) | (x<<(16 - i));
        hash_ ^= x;
    }
//    std::cout<<hash_<<'\n';

    return (hash_) % hash_len;
}


