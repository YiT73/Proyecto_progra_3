//
// Created by yitzh on 14/07/2024.
//

#ifndef PROJECTO_PROGRA_3_CONTROLEDAD_H
#define PROJECTO_PROGRA_3_CONTROLEDAD_H
#include "Pelicula.h"
#include <vector>
#include <unordered_set>
using std::vector,std::cout,std::endl,std::cin;
class ControlEdad{
private:
    int edad;
    vector<Pelicula> peliculas;
public:
    ControlEdad(int e,vector<Pelicula> p):edad(e),peliculas(p){};
    void Resultados(){
        bool opcion;
        cout<<"Desea ver la siponisis (0) o no (1)?";
        cin>>opcion;
        cout<<"Resultados:"<<endl;
        int num=1;
        for(auto pelicula:peliculas){
            cout<<num<<".";
            unordered_set<string > tags=pelicula.getTags();
            if(tags.find("pornographic") != tags.end()||edad<18){
                cout<<"No se puede mostrar la pelicula por restriccion de edad"<<endl;
            } else{
                cout<<"Titulo:"<<pelicula.getTitulo()<<endl;
                cout<<"Tags:";
                for(auto tag:tags){
                    cout<<" "<<tag;
                }
                cout<<endl;
                if (opcion){
                    cout<<"Sinopsis:"<<endl;
                    cout<<pelicula.getSinopsis();
                }
            }
            num++;
        }
    }
};
#endif //PROJECTO_PROGRA_3_CONTROLEDAD_H
