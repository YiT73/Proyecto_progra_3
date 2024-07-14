#include <iostream>
#include "GrafoPeliculas.h"
#include "Pelicula.h"
#include "Nodo.h"
#include "PeliculaBuilder.h"
#include "Usuario.h"
using std::cout;
int main(){
    Usuario* u1= Usuario::get();
    cout<<"---------------------------------------------------"<<endl;
    u1->iniciar_sesion();
    u1->view();

}