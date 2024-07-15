// busqueda.h

#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include <iostream>
#include <vector>
#include "Pelicula.h"
#include "GrafoPeliculas.h"
#include "Usuario.h"
#include "ControlEdad.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

void filtrarPeliculasPorEdad(vector<Pelicula>& peliculas) {
    Usuario* usuario = Usuario::get();
    ControlEdad controlEdad(usuario->getEdad(), peliculas);
    peliculas = controlEdad.obtenerPeliculasFiltradas();
}

void mostrarResultados(vector<Pelicula>& resultados, int& indice, int limite = 5) {
    filtrarPeliculasPorEdad(resultados);

    // Mostrar los resultados en lotes de 'limite'
    for (int i = indice; i < indice + limite && i < resultados.size(); ++i) {
        cout << i + 1 << ". Titulo: " << resultados[i].getTitulo() << endl;
    }
    // Incrementar el índice para la próxima llamada
    indice += limite;
    // Verificar si hay más resultados para mostrar
    if (indice < resultados.size()) {
        cout << "Mostrar más resultados? (s/n): ";
        char opcion;
        cin >> opcion;
        if (opcion == 's' || opcion == 'S') {
            mostrarResultados(resultados, indice, limite);
        }
    } else {
        cout << "No hay más resultados." << endl;
    }
}

void mostrarDetallesPelicula(Pelicula pelicula) {
    Usuario* usuario = Usuario::get();
    ControlEdad controlEdad(usuario->getEdad(), {pelicula});
    vector<Pelicula> peliculasFiltradas = controlEdad.obtenerPeliculasFiltradas();

    if (peliculasFiltradas.empty()) {
        cout << "No se puede mostrar la película por restricción de edad." << endl;
        return;
    }

    pelicula = peliculasFiltradas.front();

    cout << "Titulo: " << pelicula.getTitulo() << endl;
    cout << "Sinopsis: " << pelicula.getSinopsis() << endl;
    cout << "Tags: ";
    for (const auto& tag : pelicula.getTags()) {
        cout << tag << " ";
    }
    cout << endl;

    cout << "Opciones:\n";
    cout << "1. Dar like\n";
    cout << "2. Ver más tarde\n";
    cout << "3. Volver a los resultados\n";
    cout << "Seleccione una opción: ";
    int opcion;
    cin >> opcion;
    if (opcion == 1) {
        usuario->darLike(pelicula);
        cout << "Has dado like a la película.\n";
    } else if (opcion == 2) {
        usuario->agregarVerMasTarde(pelicula);
        cout << "Has agregado la película a 'ver más tarde'.\n";
    }
}

void mostrarPeliculasSimilares(GrafoPeliculas& grafo) {
    Usuario* usuario = Usuario::get();
    const auto& peliculasLiked = usuario->getPeliculasLiked();

    if (peliculasLiked.empty()) {
        cout << "No has dado like a ninguna película.\n";
        return;
    }

    string primerTag = peliculasLiked.front().getTags().empty() ? "" : *peliculasLiked.front().getTags().begin();
    if (primerTag.empty()) {
        cout << "La primera película que te gusta no tiene tags para recomendar.\n";
        return;
    }

    auto peliculasSimilares = grafo.busquedaPorTag(primerTag);
    filtrarPeliculasPorEdad(peliculasSimilares);

    if (peliculasSimilares.empty()) {
        cout << "No se encontraron películas similares basadas en el tag '" << primerTag << "'.\n";
    } else {
        cout << "Películas similares basadas en tu primer tag favorito ('" << primerTag << "'):\n";
        int indice = 0;
        mostrarResultados(peliculasSimilares, indice);
    }
}

void realizarBusqueda(GrafoPeliculas& grafo) {
    Usuario* usuario = Usuario::get();
    while (true) {
        cout << "\nPelículas 'ver más tarde':\n";
        usuario->mostrarVerMasTarde();

        cout << "\nSeleccione el tipo de búsqueda:\n";
        cout << "1. Búsqueda por Título\n";
        cout << "2. Búsqueda por Palabra en Sinopsis\n";
        cout << "3. Búsqueda General\n";
        cout << "4. Búsqueda por Tag\n";
        cout << "5. Ver recomendaciones basadas en favoritos\n";
        cout << "6. Salir\n";
        cout << "Opción: ";
        int opcion;
        cin >> opcion;

        if (opcion == 6) {
            break;
        }

        if (opcion == 5) {
            mostrarPeliculasSimilares(grafo);
            continue;
        }

        cout << "Ingrese la palabra de búsqueda: ";
        string palabraBusqueda;
        cin.ignore();  // Limpiar el buffer
        getline(cin, palabraBusqueda);

        vector<Pelicula> resultados;
        if (opcion == 1) {
            resultados = grafo.busquedaPorTitulo(palabraBusqueda);
            cout << "Resultados de la búsqueda por título '" << palabraBusqueda << "':" << endl;
        } else if (opcion == 2) {
            resultados = grafo.busquedaPorPalabraEnSinopsis(palabraBusqueda);
            cout << "Resultados de la búsqueda por palabra en sinopsis '" << palabraBusqueda << "':" << endl;
        } else if (opcion == 3) {
            resultados = grafo.busquedaGeneral(palabraBusqueda);
            cout << "Resultados de la búsqueda general '" << palabraBusqueda << "':" << endl;
        } else if (opcion == 4) {
            resultados = grafo.busquedaPorTag(palabraBusqueda);
            cout << "Resultados de la búsqueda por tag '" << palabraBusqueda << "':" << endl;
        } else {
            cout << "Opción no válida. Inténtelo de nuevo.\n";
            continue;
        }

        int indice = 0;
        mostrarResultados(resultados, indice);

        while (true) {
            cout << "Seleccione el número de la película para ver más detalles (0 para volver): ";
            int seleccion;
            cin >> seleccion;
            if (seleccion == 0) {
                break;
            } else if (seleccion > 0 && seleccion <= resultados.size()) {
                mostrarDetallesPelicula(resultados[seleccion - 1]);
            } else {
                cout << "Selección no válida. Inténtelo de nuevo.\n";
            }
        }
    }
}

#endif // BUSQUEDA_H