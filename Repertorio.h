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
#include <vector>
using std::unordered_map,std::unordered_set,std::ifstream,std::getline,std::vector,std::istringstream;
class Repertorio {
private:
    unordered_map<string, Pelicula> peliculas;


public:
    unordered_set<string> dividirConComillas(const string& str) {
        unordered_set<string> tokens;
        istringstream tokenStream(str);
        string token;
        bool enComillas = false;
        string tagCompleto;
        char c;

        while (tokenStream.get(c)) {
            if (c == '"') {
                enComillas = !enComillas;
                if (!enComillas && !tagCompleto.empty()) {
                    tokens.insert(tagCompleto);
                    tagCompleto.clear();
                }
            } else if (c == ',' && !enComillas) {
                if (!tagCompleto.empty()) {
                    tokens.insert(tagCompleto);
                    tagCompleto.clear();
                }
            } else {
                tagCompleto += c;
            }
        }

        if (!tagCompleto.empty()) {
            tokens.insert(tagCompleto);
        }

        return tokens;
    }

    unordered_map<string, Pelicula> leerCSV(const string& nombreArchivo) {
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
            istringstream stream(linea);
            string imdb_id, title, plot_synopsis, tagsStr, split, synopsis_source;

            // Leer imdb_id
            getline(stream, imdb_id, ',');

            // Leer title
            if (stream.peek() == '"') {
                stream.get(); // Consumir la comilla inicial
                getline(stream, title, '"');
                stream.get(); // Consumir la coma después de las comillas
            } else {
                getline(stream, title, ',');
            }

            // Leer plot_synopsis
            if (stream.peek() == '"') {
                stream.get(); // Consumir la comilla inicial
                getline(stream, plot_synopsis, '"');
                stream.get(); // Consumir la coma después de las comillas
            } else {
                getline(stream, plot_synopsis, ',');
            }

            // Leer tags
            if (stream.peek() == '"') {
                stream.get(); // Consumir la comilla inicial
                getline(stream, tagsStr, '"');
                stream.get(); // Consumir la coma después de las comillas
            } else {
                getline(stream, tagsStr, ',');
            }

            // Leer split y synopsis_source
            getline(stream, split, ',');
            getline(stream, synopsis_source);

            // Procesar los tags
            std::unordered_set<string> tags = dividirConComillas(tagsStr);

            // Crear la película y añadirla al mapa
            Pelicula pelicula(imdb_id, title, plot_synopsis, tags);
            peliculas[imdb_id] = std::move(pelicula);
        }

        archivo.close();
        return peliculas;
    }
};

#endif //PROJECTO_PROGRA_3_REPERTORIO_H
