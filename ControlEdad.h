//
// Created by yoyoyopi on 15/07/2024.
//

#ifndef PROJECTO_PROGRA_3_CONTROLEDAD_H
#define PROJECTO_PROGRA_3_CONTROLEDAD_H

#include "Pelicula.h"
#include <vector>
#include <unordered_set>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;
using std::cin;
using std::unordered_set;

class ControlEdad {
private:
    int edad;
    vector<Pelicula> peliculas;
public:
    ControlEdad(int e, vector<Pelicula> p) : edad(e), peliculas(p) {}

    vector<Pelicula> obtenerPeliculasFiltradas() {
        vector<Pelicula> filtradas;
        for (const auto& pelicula : peliculas) {
            unordered_set<string> tags = pelicula.getTags();
            if (tags.find("pornographic") == tags.end() || edad >= 18) {
                filtradas.push_back(pelicula);
            }
        }
        return filtradas;
    }

    void mostrarResultados() {
        bool mostrarSinopsis;
        cout << "¿Desea ver la sinopsis (1) o no (0)? ";
        cin >> mostrarSinopsis;
        cout << "Resultados:" << endl;
        int num = 1;
        for (const auto& pelicula : peliculas) {
            cout << num << ".";
            unordered_set<string> tags = pelicula.getTags();
            if (tags.find("pornographic") != tags.end() && edad < 18) {
                cout << "No se puede mostrar la película por restricción de edad." << endl;
            } else {
                cout << " Título: " << pelicula.getTitulo() << endl;
                cout << "Tags:";
                for (const auto& tag : tags) {
                    cout << " " << tag;
                }
                cout << endl;
                if (mostrarSinopsis) {
                    cout << "Sinopsis:" << endl;
                    cout << pelicula.getSinopsis() << endl;
                }
            }
            num++;
        }
    }
};

#endif //PROJECTO_PROGRA_3_CONTROLEDAD_H
