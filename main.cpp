#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "OpenHashMap.h"
#include "OpenHashMap.cpp"
//#include "CloseHashMap.h"
//#include "CloseHashMap.cpp"
#include "string"


int main() {
    //collisions for mod has = 24117
    //collisions for mid square has = 24082
    //collisions for shift has = 24682
    //Лучшая функция - shift, поскольку работает быстрее всех


    // open hash map
    OpenHashMap<int> map;
    std::ifstream file("/home/gleb/CLionProjects/hashMap/endict-small.txt");
    int k = 0;
    std::string input_str;
    while (file)
    {
        k++;
        getline(file, input_str);
//        std::cout<<input_str<<'\n';
        map.push(input_str, 1);
    }


//     count collisions
    u_int16_t collisions = 0;
    for (const auto& vec : map.data)  {
        if (vec.size() > 1) {
            collisions += vec.size() - 1;
        }

    }
    std::cout<<"collisions: "<<collisions;



/*
// Close hash map
    CloseHashMap<int> close_map;
    std::ifstream file("/home/gleb/CLionProjects/hashMap/endict-small.txt");

    int k = 0;
    std::string input_str;
    while (file)
    {
        k++;
        getline(file, input_str);
//        std::cout<<input_str<<'\n';
        close_map.push(input_str, k);
    }
  */
}