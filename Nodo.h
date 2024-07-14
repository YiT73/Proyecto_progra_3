//
// Created by yitzh on 13/07/2024.
//

#ifndef PROJECTO_PROGRA_3_NODO_H
#define PROJECTO_PROGRA_3_NODO_H

#include <iostream>
#include "Pelicula.h"
using std::string;
class Nodo {
public:
    string id;
    Pelicula pelicula;
    unordered_set<Nodo*> conexiones;

    Nodo(string id, Pelicula pelicula) : id(id), pelicula(std::move(pelicula)) {}

    void agregarConexion(Nodo* otroNodo) {
        conexiones.insert(otroNodo);
    }

};
#endif //PROJECTO_PROGRA_3_NODO_H
