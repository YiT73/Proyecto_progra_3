//
// Created by yitzh on 13/07/2024.
//

#ifndef PROJECTO_PROGRA_3_GRAFOPELICULAS_H
#define PROJECTO_PROGRA_3_GRAFOPELICULAS_H
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include "Pelicula.h"
#include "Nodo.h"
using std::string,std::unordered_map,std::vector,std::istringstream;

class GrafoPeliculas {
private:
    unordered_map<string, Nodo*> nodos;

    // Función auxiliar para comparar strings ignorando mayúsculas/minúsculas
    static bool comparaIgnorandoCase(const string& a, const string& b) {
        return std::equal(a.begin(), a.end(), b.begin(), b.end(),
                          [](char a, char b) { return tolower(a) == tolower(b); });
    }

public:
    void agregarPelicula(const Pelicula& pelicula) {
        string id = pelicula.getId();
        if (nodos.find(id) == nodos.end()) {
            nodos[id] = new Nodo(id, pelicula);
        }
    }

    void conectarPeliculas(const string& id1, const string& id2) {
        if (nodos.find(id1) != nodos.end() && nodos.find(id2) != nodos.end()) {
            nodos[id1]->agregarConexion(nodos[id2]);
            nodos[id2]->agregarConexion(nodos[id1]);
        }
    }

    // Método para crear conexiones basadas en tags compartidos
    void crearConexionesPorTags() {
        for (const auto& [id1, nodo1] : nodos) {
            for (const auto& [id2, nodo2] : nodos) {
                if (id1 != id2) {
                    // Compara los tags de las dos películas
                    const auto& tags1 = nodo1->pelicula.getTags();
                    const auto& tags2 = nodo2->pelicula.getTags();

                    // Si tienen al menos un tag en común, crea una conexión
                    for (const auto& tag : tags1) {
                        if (tags2.find(tag) != tags2.end()) {
                            conectarPeliculas(id1, id2);
                            break;
                        }
                    }
                }
            }
        }
    }
    vector<Pelicula> busquedaPorTag(const string& tag, int limite = 5) {
        vector<Pelicula> resultado;
        for (const auto& [id, nodo] : nodos) {
            if (nodo->pelicula.getTags().find(tag) != nodo->pelicula.getTags().end()) {
                resultado.push_back(nodo->pelicula);
                if (resultado.size() == limite) break;
            }
        }
        return resultado;
    }

    vector<Pelicula> busquedaPorTitulo(const string& titulo, int limite = 5) {
        vector<Pelicula> resultado;
        for (const auto& [id, nodo] : nodos) {
            if (comparaIgnorandoCase(nodo->pelicula.getTitulo(), titulo)) {
                resultado.push_back(nodo->pelicula);
                if (resultado.size() == limite) break;
            }
        }
        return resultado;
    }

    vector<Pelicula> busquedaPorCaracteres(const string& caracteres, int limite = 5) {
        vector<Pelicula> resultado;
        for (const auto& [id, nodo] : nodos) {
            if (nodo->pelicula.getTitulo().find(caracteres) != string::npos) {
                resultado.push_back(nodo->pelicula);
                if (resultado.size() == limite) break;
            }
        }
        return resultado;
    }

    vector<Pelicula> busquedaPorPalabraEnSinopsis(const string& palabra, int limite = 5) {
        vector<Pelicula> resultado;
        for (const auto& [id, nodo] : nodos) {
            istringstream iss(nodo->pelicula.getSinopsis());
            string palabraSinopsis;
            while (iss >> palabraSinopsis) {
                if (comparaIgnorandoCase(palabraSinopsis, palabra)) {
                    resultado.push_back(nodo->pelicula);
                    break;
                }
            }
            if (resultado.size() == limite) break;
        }
        return resultado;
    }

    // Método general de búsqueda que combina todos los criterios
    vector<Pelicula> busquedaGeneral(const string& consulta, int limite = 5) {
        vector<Pelicula> resultado;
        unordered_set<string> idsEncontrados;

        // Buscar por tag
        auto porTag = busquedaPorTag(consulta, limite);
        for (const auto& pelicula : porTag) {
            if (idsEncontrados.insert(pelicula.getId()).second) {
                resultado.push_back(pelicula);
                if (resultado.size() == limite) return resultado;
            }
        }

        // Buscar por título
        auto porTitulo = busquedaPorTitulo(consulta, limite);
        for (const auto& pelicula : porTitulo) {
            if (idsEncontrados.insert(pelicula.getId()).second) {
                resultado.push_back(pelicula);
                if (resultado.size() == limite) return resultado;
            }
        }

        // Buscar por caracteres en el título
        auto porCaracteres = busquedaPorCaracteres(consulta, limite);
        for (const auto& pelicula : porCaracteres) {
            if (idsEncontrados.insert(pelicula.getId()).second) {
                resultado.push_back(pelicula);
                if (resultado.size() == limite) return resultado;
            }
        }

        // Buscar por palabra en la sinopsis
        auto porPalabraEnSinopsis = busquedaPorPalabraEnSinopsis(consulta, limite);
        for (const auto& pelicula : porPalabraEnSinopsis) {
            if (idsEncontrados.insert(pelicula.getId()).second) {
                resultado.push_back(pelicula);
                if (resultado.size() == limite) return resultado;
            }
        }

        return resultado;
    }

};
#endif //PROJECTO_PROGRA_3_GRAFOPELICULAS_H
