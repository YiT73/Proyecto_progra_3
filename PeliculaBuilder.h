//
// Created by yitzh on 13/07/2024.
//

#ifndef PROJECTO_PROGRA_3_PELICULABUILDER_H
#define PROJECTO_PROGRA_3_PELICULABUILDER_H
#include <string>
#include <unordered_set>
#include <algorithm>
#include <stdexcept>
#include "Pelicula.h"

class PeliculaBuilder {
private:
    std::string titulo;
    std::string sinopsis;
    std::unordered_set<std::string> tags;

    void limpiarTexto(std::string& texto) {
        texto.erase(std::remove_if(texto.begin(), texto.end(),
                                   [](unsigned char c) { return std::isspace(c) && c != ' '; }), texto.end());
    }

public:
    PeliculaBuilder& conTitulo(std::string t) {
        limpiarTexto(t);
        if (t.empty()) {
            throw std::invalid_argument("El título no puede estar vacío");
        }
        this->titulo = std::move(t);
        return *this;
    }

    PeliculaBuilder& conSinopsis(std::string s) {
        if (s.length() > 500) {
            throw std::invalid_argument("La sinopsis no puede exceder los 500 caracteres");
        }
        this->sinopsis = std::move(s);
        return *this;
    }

    PeliculaBuilder& agregarTag(const std::string& tag) {
        std::string tagLimpio = tag;
        limpiarTexto(tagLimpio);
        if (!tagLimpio.empty()) {
            this->tags.insert(tagLimpio);
        }
        return *this;
    }

    PeliculaBuilder& conTags(const std::unordered_set<std::string>& nuevasTags) {
        for (const auto& tag : nuevasTags) {
            agregarTag(tag);
        }
        return *this;
    }

    Pelicula construir() {
        if (titulo.empty()) {
            throw std::runtime_error("No se puede construir una película sin título");
        }
        return Pelicula(std::move(titulo), std::move(sinopsis), std::move(tags));
    }
};
#endif //PROJECTO_PROGRA_3_PELICULABUILDER_H
