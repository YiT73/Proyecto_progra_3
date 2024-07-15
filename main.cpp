#include <iostream>
#include "GrafoPeliculas.h"
#include "Pelicula.h"
#include "Nodo.h"
#include "PeliculaBuilder.h"
#include "Usuario.h"
#include "Repertorio.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

void mostrarResultados(const vector<Pelicula>& resultados, int& indice, int limite = 5) {
    // Mostrar los resultados en lotes de 'limite'
    for (int i = indice; i < indice + limite && i < resultados.size(); ++i) {
        cout << "Titulo: " << resultados[i].getTitulo() << endl;
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

int main() {
    Repertorio* repertorio = Repertorio::getInstancia();
    repertorio->leerCSV("C:/Users/LENOVO/Desktop/Proyecto_progra_3/data_corrected.csv");

    GrafoPeliculas grafo;
    const auto& peliculas = repertorio->getPeliculas();
    for (const auto& par : peliculas) {
        grafo.agregarPelicula(par.second);
    }

    Usuario* u1 = Usuario::get();
    cout << "---------------------------------------------------" << endl;
    u1->iniciar_sesion();
    u1->view();

    while (true) {
        cout << "\nSeleccione el tipo de búsqueda:\n";
        cout << "1. Búsqueda por Título\n";
        cout << "2. Búsqueda por Palabra en Sinopsis\n";
        cout << "3. Búsqueda General\n";
        cout << "4. Búsqueda por Tag\n";
        cout << "5. Salir\n";
        cout << "Opción: ";
        int opcion;
        cin >> opcion;

        if (opcion == 5) {
            break;
        }

        cout << "Ingrese la palabra de búsqueda: ";
        string palabraBusqueda;
        cin.ignore();  // Limpiar el buffer
        getline(cin, palabraBusqueda);

        if (opcion == 1) {
            auto resultados = grafo.busquedaPorTitulo(palabraBusqueda);
            cout << "Resultados de la búsqueda por título '" << palabraBusqueda << "':" << endl;
            int indice = 0;
            mostrarResultados(resultados, indice);
        } else if (opcion == 2) {
            auto resultados = grafo.busquedaPorPalabraEnSinopsis(palabraBusqueda);
            cout << "Resultados de la búsqueda por palabra en sinopsis '" << palabraBusqueda << "':" << endl;
            int indice = 0;
            mostrarResultados(resultados, indice);
        } else if (opcion == 3) {
            auto resultados = grafo.busquedaGeneral(palabraBusqueda);
            cout << "Resultados de la búsqueda general '" << palabraBusqueda << "':" << endl;
            int indice = 0;
            mostrarResultados(resultados, indice);
        } else if (opcion == 4) {
            auto resultados = grafo.busquedaPorTag(palabraBusqueda);
            cout << "Resultados de la búsqueda por tag '" << palabraBusqueda << "':" << endl;
            int indice = 0;
            mostrarResultados(resultados, indice);
        } else {
            cout << "Opción no válida. Inténtelo de nuevo.\n";
        }
    }

    return 0;
}
