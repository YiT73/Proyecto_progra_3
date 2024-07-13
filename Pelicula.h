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
    string id;
    string titulo;
    string sinopsis;
    unordered_set<string> tags;
public:
    Pelicula()=default;
    Pelicula(string i, string t, string s, unordered_set<string> ta): id(i), titulo(t), sinopsis(s), tags(ta) {}

    const string& getId() const {
        return id;
    }

    const string& getTitulo() const {
        return titulo;
    }

    const string& getSinopsis() const {
        return sinopsis;
    }

    const unordered_set<string>& getTags() const {
        return tags;
    }
};


#endif //PROJECTO_PROGRA_3_PELICULA_H
