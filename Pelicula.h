//
// Created by yitzh on 11/07/2024.
//

#ifndef PROJECTO_PROGRA_3_PELICULA_H
#define PROJECTO_PROGRA_3_PELICULA_H
#include <iostream>
#include <unordered_set>

using std::string,std::unordered_set;

class Pelicula {
private:
    string titulo;
    string simopsis;
    unordered_set<string> tags;
public:
    Pelicula(string t,string s, unordered_set<string> ta):titulo(std::move(t)),simopsis(std::move(s)),tags(std::move(ta)){};
};


#endif //PROJECTO_PROGRA_3_PELICULA_H
