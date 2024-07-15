//
// Created by yitzh on 13/07/2024.
//

#ifndef PROJECTO_PROGRA_3_GRAFOPELICULAS_H
#define PROJECTO_PROGRA_3_GRAFOPELICULAS_H
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <string>
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
    vector<Pelicula> busquedaPorTag(const string& tag, int limite = 20) {
        vector<Pelicula> resultado;
        for (const auto& [id, nodo] : nodos) {
            if (nodo->pelicula.getTags().find(tag) != nodo->pelicula.getTags().end()) {
                resultado.push_back(nodo->pelicula);
                if (resultado.size() == limite) break;
            }
        }
        return resultado;
    }

    vector<Pelicula> busquedaPorTitulo(const string& titulo, int limite = 10) {
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

    vector<Pelicula> busquedaPorPalabraEnSinopsis(const string& palabra, int limite = 10) {
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

    vector<Pelicula> busquedaGeneral( string& consulta, int limite = 10) {
        vector<Pelicula> resultado;
        unordered_set<string> idsEncontrados;

        auto agregarResultadosUnicos = [&](const vector<Pelicula>& nuevosResultados) {
            for (const auto& pelicula : nuevosResultados) {
                if (idsEncontrados.insert(pelicula.getId()).second) {
                    resultado.push_back(pelicula);
                    if (resultado.size() == limite) return true;
                }
            }
            return false;
        };
        bool esTag = false;
        bool esTituloExacto = false;
        bool esPalabraSinopsis = false;

        if (!consulta.empty()) {
            if (consulta.front() == '#') {
                esTag = true;
                consulta.erase(0, 1);  // Eliminar el '#'
            } else if (consulta.front() == '"' && consulta.back() == '"') {
                esTituloExacto = true;
                consulta = consulta.substr(1, consulta.length() - 2);  // Eliminar las comillas
            } else if (consulta.front() == '*') {
                esPalabraSinopsis = true;
                consulta.erase(0, 1);  // Eliminar el '*'
            }
        }
        // Buscar por tag
        if (esTag) {
            // Búsqueda por tag (eliminar el '#' inicial)
            auto porTag = busquedaPorTag(consulta, limite);
            for (const auto& pelicula : porTag) {
                if (idsEncontrados.insert(pelicula.getId()).second) {
                    resultado.push_back(pelicula);
                    if (resultado.size() == limite) return resultado;
                }
            }
            if (agregarResultadosUnicos(busquedaPorTag(consulta.substr(1), limite))) return resultado;
        } else if (esTituloExacto) {
            // Búsqueda por título exacto (eliminar las comillas)
            auto porTitulo = busquedaPorTitulo(consulta, limite);
            for (const auto& pelicula : porTitulo) {
                if (idsEncontrados.insert(pelicula.getId()).second) {
                    resultado.push_back(pelicula);
                    if (resultado.size() == limite) return resultado;
                }
            }
            if (agregarResultadosUnicos(busquedaPorTitulo(consulta.substr(1, consulta.length() - 2), limite))) return resultado;
        } else if (esPalabraSinopsis) {
            // Búsqueda por palabra en sinopsis (eliminar el '*' inicial)
            auto porCaracteres = busquedaPorCaracteres(consulta, limite);
            for (const auto& pelicula : porCaracteres) {
                if (idsEncontrados.insert(pelicula.getId()).second) {
                    resultado.push_back(pelicula);
                    if (resultado.size() == limite) return resultado;
                }
            }
            if (agregarResultadosUnicos(busquedaPorPalabraEnSinopsis(consulta.substr(1), limite))) return resultado;
        } else {
            // Búsqueda general (primero por caracteres en el título, luego por otros criterios)
            auto porPalabraEnSinopsis = busquedaPorPalabraEnSinopsis(consulta, limite);
            for (const auto& pelicula : porPalabraEnSinopsis) {
                if (idsEncontrados.insert(pelicula.getId()).second) {
                    resultado.push_back(pelicula);
                    if (resultado.size() == limite) return resultado;
                }
            }
            if (agregarResultadosUnicos(busquedaPorCaracteres(consulta, limite))) return resultado;
        }
        auto porTag = busquedaPorTag(consulta, limite);
        for (const auto& pelicula : porTag) {
            if (idsEncontrados.insert(pelicula.getId()).second) {
                resultado.push_back(pelicula);
                if (resultado.size() == limite) return resultado;
            }
        }
        if (!esTag && agregarResultadosUnicos(busquedaPorTag(consulta, limite))) return resultado;
        if (!esTituloExacto && agregarResultadosUnicos(busquedaPorTitulo(consulta, limite))) return resultado;
        if (!esPalabraSinopsis && agregarResultadosUnicos(busquedaPorPalabraEnSinopsis(consulta, limite))) return resultado;

        return resultado;
    }

};
#endif //PROJECTO_PROGRA_3_GRAFOPELICULAS_H
