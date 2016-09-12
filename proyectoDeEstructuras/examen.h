//
//  examen.h
//  proyectoDeEstructuras
//
//  Created by Jafeth  Vásquez on 11/9/16.
//  Copyright © 2016 Jafeth Vásquez. All rights reserved.
//

#ifndef examen_h
#define examen_h
#include "seccion.h"

struct nodoSeccion{
    seccion seccionActual;
    nodoSeccion *siguiente;
};

class examen{
private:
    int puntaje;
    int puntajeObtenido;
    nodoSeccion listasecciones;
    string estudiante;
    string profesor;
public:
    int calificar();
    void añadirSeccion();
    seccion borrarSeccion();
    void imprimirInforme();
    void modificar();
    

};
#endif /* examen_h */
