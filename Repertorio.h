//
// Created by yitzh on 11/07/2024.
//

#ifndef PROJECTO_PROGRA_3_REPERTORIO_H
#define PROJECTO_PROGRA_3_REPERTORIO_H
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include "Pelicula.h"
#include <fstream>
#include <sstream>
using std::unordered_map,std::unordered_set,std::ifstream,std::getline;
class Repertorio {
private:
    unordered_map<string,Pelicula> peliculas;
    Repertorio()=default;
public:
    unordered_map<string, Pelicula> leerCSV(const std::string& nombreArchivo) {
        unordered_map<string, Pelicula> peliculas;
        ifstream archivo(nombreArchivo);
        string linea;

        if (!archivo.is_open()) {
            std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
            return peliculas;
        }

        // Leer la cabecera del archivo
        getline(archivo, linea);

        while (getline(archivo, linea)) {
            std::istringstream stream(linea);
            string id, titulo, sinopsis,tag,split,recurso;
            unordered_set<string> tags;

            // Leer los valores de cada columna. Supongamos que las columnas están en el orden:
            // columna1, columna2, columna3, columna4, columna5, columna6
            getline(stream, id, ',');  // columna1
            getline(stream, titulo, ','); // columna2
            getline(stream, sinopsis, ',');// columna3
            while (getline(stream, tag, ',')){
                tags.insert(tag);
            }
              // columna4
            getline(stream, split, ',');  // columna5
            getline(stream, recurso, ','); // columna6

            peliculas[titulo] = Pelicula(titulo,sinopsis, tags);
        }

        archivo.close();
        return peliculas;
    }
};


#endif //PROJECTO_PROGRA_3_REPERTORIO_H
