#include <iostream>
#include "GrafoPeliculas.h"
#include "Pelicula.h"
#include "Usuario.h"
#include "Repertorio.h"
#include "ControlEdad.h"
using std::cout;
int main(){
    Usuario* u1= Usuario::get();
    cout<<"---------------------------------------------------"<<endl;
    u1->iniciar_sesion();
    u1->view();
    Repertorio repertorio;
    auto peliculas = repertorio.leerCSV("peliculas.csv");

    GrafoPeliculas grafo;

    // Agregar todas las películas al grafo
    for (const auto& [id, pelicula] : peliculas) {
        grafo.agregarPelicula( pelicula);
    }

    // Crear conexiones basadas en tags compartidos
    grafo.crearConexionesPorTags();
    cout<<"---------------------------------------------------"<<endl;
    cout<<"Que esta buscando?";
    cout<<"Si decea hacer una busqueda espefica ponga lo siguiente al inicio de lo que va a escribir\n"
          "# para búsqueda por tag\n"
          "\" al inicio y final para búsqueda por título exacto\n"
          "* para búsqueda por palabra en la sinopsis";
    cout<<endl;
    string movie;
    cin>>movie;
    vector<Pelicula> movies;
    movies=grafo.busquedaGeneral(movie);
    ControlEdad proxy(u1->get_edad(),movies);


    return 0;
}