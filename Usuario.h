//
// Created by yitzh on 14/07/2024.
//

#ifndef PROJECTO_PROGRA_3_USUARIO_H
#define PROJECTO_PROGRA_3_USUARIO_H
#include <iostream>
using std::cout,std::cin,std::endl,std::string;
class Usuario {
private:
    int edad;
    int pwd;
    string nombre;
    bool acceso = false;
    static Usuario *tem;
    Usuario(){
        int pwd_tem;
        cout<<"Bienvenido a Streamflix"<<endl;
        cout<<"Cual es su nombre o nick:";
        cin>>nombre;
        cout<<"Cual es su edad:";
        cin>>edad;
        cout<<"Ingrese su contraseña:";
        cin>>pwd;
        cout<<"Rectifique su contraseña:";
        cin>>pwd_tem;
        while (pwd_tem!=pwd){
            cout<<"Ingrese correctamente la contraseña!:";
            cin>>pwd_tem;
        }
        cout<<"Se verifico correctamente la contraseña :D";

    }

public:
    void view() {
        if (acceso){
            cout<<"Bienvenido"<<endl;
        } else{
            cout<<"No tiene acceso"<<endl;
        }
    }
    // Constructor privado para evitar la creación de instancias
    void iniciar_sesion(){
        string nombre_b;
        cout<<"Ingresa tu usuario:";
        cin>>nombre;
        int pwd_b=0;
        cout<<"Password:";
        cin>>pwd;
        if(pwd_b==pwd&&nombre_b==nombre){
            acceso= true;
        }
    }
    static Usuario* get(){
        if (tem== nullptr){
            tem=new Usuario();
        }
        return tem;
    }
};

#endif //PROJECTO_PROGRA_3_USUARIO_H