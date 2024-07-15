#include <iostream>
#include "GrafoPeliculas.h"
#include "Pelicula.h"
#include "Nodo.h"
#include "PeliculaBuilder.h"
#include "Usuario.h"
#include "Repertorio.h"
#include "Busqueda.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main() {
    Repertorio* repertorio = Repertorio::getInstancia();
    repertorio->leerCSV("data_corrected.csv");

    GrafoPeliculas grafo;
    const auto& peliculas = repertorio->getPeliculas();
    for (const auto& par : peliculas) {
        grafo.agregarPelicula(par.second);
    }

    Usuario* u1 = Usuario::get();
    cout << "---------------------------------------------------" << endl;
    u1->iniciar_sesion();
    if(u1->view()){
        realizarBusqueda(grafo);
    }

    return 0;
}