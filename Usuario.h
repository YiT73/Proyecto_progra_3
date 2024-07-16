#ifndef PROJECTO_PROGRA_3_USUARIO_H
#define PROJECTO_PROGRA_3_USUARIO_H

#include <iostream>
#include <vector>
#include "Pelicula.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

class Usuario {
private:
    int edad;
    int pwd;
    string nombre;
    bool acceso = false;
    static Usuario *tem;
    vector<Pelicula> verMasTarde; // Lista de películas para ver más tarde
    vector<Pelicula> peliculasLiked; // Lista de películas que el usuario ha dado like

    // Constructor privado para evitar la creación de instancias
    Usuario() {
        int pwd_tem=0;
        cout << "Bienvenido a Streamflix" << endl;
        cout << "Cual es su nombre o nick: ";
        cin >> nombre;
        cout << "Cual es su edad: ";
        cin >> edad;
        cout << "Ingrese su contrasena: ";
        cin >> pwd;
        cout << "Rectifique su contrasena: ";
        cin >> pwd_tem;
        while (pwd_tem != pwd) {
            cout << "Ingrese correctamente la contraseña!: ";
            cin >> pwd_tem;
        }
        cout << "Se verifico correctamente la contrasena :D" << endl;
    }

public:
    // Método para mostrar la vista del usuario
    bool view() {
        if (acceso) {
            cout << "Bienvenido" << endl;
        } else {
            cout << "No tiene acceso" << endl;

        }
        return acceso;
    }

    // Método para iniciar sesión
    void iniciar_sesion() {
        string nombre_b;
        cout << "Inicie sesion" << endl;
        cout << "Ingresa tu usuario: ";
        cin >> nombre_b;
        int pwd_b = 0;
        cout << "Password: ";
        cin >> pwd_b;
        if (pwd_b == pwd && nombre_b == nombre) {
            acceso = true;
        }
    }

    // Método estático para obtener la instancia de Usuario
    static Usuario* get() {
        if (tem == nullptr) {
            tem = new Usuario();
        }
        return tem;
    }

    int getEdad() const {
        return edad;
    }

    // Método para agregar una película a "ver más tarde"
    void agregarVerMasTarde(const Pelicula& pelicula) {
        verMasTarde.push_back(pelicula);
    }

    // Método para mostrar las películas en "ver más tarde"
    void mostrarVerMasTarde() {
        cout << "Peliculas 'ver mas tarde':" << endl;
        for (const auto& pelicula : verMasTarde) {
            cout << "- " << pelicula.getTitulo() << endl;
        }
        if (verMasTarde.empty()) {
            cout << "No tienes peliculas en 'ver mas tarde'." << endl;
        }
    }

    // Método para agregar una película a la lista de likes
    void darLike(const Pelicula& pelicula) {
        peliculasLiked.push_back(pelicula);
    }
    void mostrarlike() {
        cout << "Peliculas 'que diste like':" << endl;
        for (const auto& pelicula : peliculasLiked) {
            cout << "- " << pelicula.getTitulo() << endl;
        }
        if (peliculasLiked.empty()) {
            cout << "No tienes peliculas en 'lista de me gusta'." << endl;
        }
    }

    // Método para obtener las películas a las que el usuario ha dado like
    const vector<Pelicula>& getPeliculasLiked() const {
        return peliculasLiked;
    }
};

// Inicialización de la instancia estática
Usuario* Usuario::tem = nullptr;

#endif // PROJECTO_PROGRA_3_USUARIO_H
