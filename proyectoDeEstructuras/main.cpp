//
//  main.cpp
//  proyectoDeEstructuras
//
//  Created by Jafeth  Vásquez and Kembly Quirós on 10/9/16.
//  Copyright © 2016 Jafeth Vásquez. All rights reserved.
//

#include <iostream>
#include  <limits.h>
#include <string>
#include <stdlib.h>
using namespace std;
/*

 SECCION CLASS

 Clase donde se encuentra la estructura de seccion y se pueden añadir preguntas.
 *********************************************************************************************************************************************

 */

struct preguntaSeleccionUnica{
    int numero;
    string textoPregunta;
    int cantOpciones;
    int respuestaCorrecta;
};

struct preguntaRespuestaCorta{
    int numero;
    string textoPregunta;
    string RespuestaCorrecta;
    int PuntajeDePregunta;
    int PuntajeObtenido;

};

struct nodoPreguntaSeleccionUnica{
    preguntaSeleccionUnica preguntaActual;
    nodoPreguntaSeleccionUnica *siguiente;
};

struct nodoPreguntaRespuestaCorta{
    preguntaSeleccionUnica preguntaActual;
    nodoPreguntaRespuestaCorta *siguiente;
};


class seccion{
private:
    string nombre;
    int PuntajeDeSeccion;
    int PuntajeDeSeccionObtenido;
    bool tipo; // true-> Respuesta Corta || false-> Seleccion Única

public:
    seccion(bool tipo1, string newnombre){
        tipo = tipo1;
        PuntajeDeSeccion = 0;
        nombre = newnombre;
    }

    void ImprimirInforme();
    int calificarSeccion();
    void anadirPregunta();
    void borrarPregunta();
    void setNombre();
    string getNombre();


};

string seccion::getNombre(){
    return nombre;
}

void seccion::anadirPregunta(){
    if (tipo == true)
        preguntaRespuestaCorta *nuevaPregunta = new preguntaRespuestaCorta;
    else
        preguntaSeleccionUnica *nuevaPregunta = new preguntaSeleccionUnica;


}




/*
 *********************************************************************************************************************************************

 CLASS EXAMEN.

 clase donde se define la estructura del examen y se almacenan sus respectivas secciones.

 *********************************************************************************************************************************************

 */


struct nodoSeccion{
    seccion *seccionActual;
    nodoSeccion *siguiente;
};

class examen{
private:
    int puntaje;
    int notaObtenida;
    nodoSeccion *listaSecciones;
    string estudiante;
    string profesor;
    string nombre;
public:
    examen(string profesorEntrante, string entradaNombre){
        nombre = entradaNombre;
        puntaje = 0;
        notaObtenida = 0;
        listaSecciones = NULL;
        estudiante = "";
        profesor = profesorEntrante;


    }
    int calificarExamen();
    void anadirSeccion(bool tipo, string nombre);
    void borrarSeccion(string nombre);
    void imprimirInforme();
    void modificar();
    void setPuntaje();
    int getPuntaje;
    void setnotaObtenida();
    int getnotaObtenida();
    void setEstudiante();
    string getEstudiante();
    void setProfesor(string profeNuevo);
    string getProfesor();
    void setNombre(string entradaNombre);
    string getNombre();

};

void examen::anadirSeccion(bool tipo, string nombre){
    seccion *nuevaSeccion = new seccion(tipo, nombre);
    nodoSeccion *nuevoNodo = new nodoSeccion();
    nuevoNodo->seccionActual = nuevaSeccion;
    nuevoNodo->siguiente = listaSecciones;
    listaSecciones = nuevoNodo;
};

void examen::borrarSeccion(string nombre){
    nodoSeccion *actual = listaSecciones;
    if (listaSecciones == NULL){
        cout<<"Examen vacio. "<<endl;
        return;}
    if(actual->seccionActual->getNombre() == nombre){
        cout << "Borrando" << actual->seccionActual->getNombre() << endl;
        listaSecciones = actual->siguiente;
        free(actual);
        return;
    }
    else{
    while(actual->siguiente!= NULL){
        if(actual->siguiente->seccionActual->getNombre() == nombre){
            nodoSeccion *aBorrar = actual->siguiente;
            actual->siguiente = actual->siguiente->siguiente;
            free(aBorrar);
            return;
        }
        else
            actual = actual->siguiente;
    }
    return;
    }
}

int examen::calificarExamen(){
    int puntaje;
    nodoSeccion *actual = listaSecciones;
    while (actual != NULL) {
        //puntaje += actual->seccionActual->calificarSeccion();
        actual = actual->siguiente;
    }

    return puntaje;
}

void examen::setProfesor(string profeNuevo){
    profesor = profeNuevo;

}

string examen::getProfesor(){
    return profesor;
}

void examen::setNombre(string entradaNombre){
    nombre = entradaNombre;

}

string examen::getNombre(){
    return nombre;
}

void examen::imprimirInforme(){
    nodoSeccion *tmp = listaSecciones;
    while(tmp != NULL){
        cout << tmp->seccionActual->getNombre() << endl;
        tmp = tmp->siguiente;
    }
}


/*
*********************************************************************************************************************************************
CLASS ARCHIVADOR

 Clase que se encarga de almacenar y gestionar los examenes.

******************************************************************************************** ***************************** ******************

*/

struct nodoExamen{
    examen *examenEnNodo;
    nodoExamen *siguiente;
};

class archivador{
private:
    nodoExamen *listaExamenes;
    int cantidadExamenes;

public:
    void anadirExamen(string profesor, string nombreExamen);
    void borrarExamen(string nombreExamen);
    bool buscarExamen(string nombreExamen);
    void imprimirExamenes();
};

void archivador::anadirExamen(string profesor, string nombreExamen){
    nodoExamen *nuevoNodo = new nodoExamen();
    examen *nuevoExamen = new examen(profesor,nombreExamen); //se crea examen con el constructor de examen

    nuevoNodo->examenEnNodo = nuevoExamen;//se apunta al examen en nodo el examen que se va a crear

    nuevoNodo->siguiente = listaExamenes;
    listaExamenes = nuevoNodo;
    cantidadExamenes++;
}

bool archivador::buscarExamen(string nombreExamen){
    nodoExamen *nodoActual = listaExamenes;
    while (nodoActual!=NULL){
        if (nodoActual->examenEnNodo->getNombre()== nombreExamen)//si el nombre del examen es igual al del nodo
            return true;
        nodoActual = nodoActual->siguiente;
    }
    return false ;
}

void archivador::borrarExamen(string nombreExamen){
    nodoExamen *nodoActual = listaExamenes;
    if (listaExamenes == NULL){
        cout<<"No hay examenes. "<<endl;
        return;
    }
    if (listaExamenes->examenEnNodo->getNombre() == nombreExamen){
        listaExamenes = nodoActual->siguiente;
        free(nodoActual);
        return;
    }
    while(nodoActual->siguiente!=NULL){
        if (nodoActual->siguiente->examenEnNodo->getNombre() == nombreExamen){
            nodoExamen *nodoBorrar = nodoActual->siguiente;
            nodoActual->siguiente = nodoActual->siguiente->siguiente;
            free(nodoBorrar);
            return;
        }
        nodoActual = nodoActual->siguiente;
    }
    cout<<"No existe ese examen!"<<endl;
    return;
}

void archivador::imprimirExamenes(){
    nodoExamen *tmp = listaExamenes;
    cout << "IMPRIMIENDO EXAMENES " << endl;
    while(tmp != NULL){
        cout << tmp->examenEnNodo->getNombre()<<endl;
        tmp = tmp->siguiente;
    }

}
/*
 *********************************************************************************************************************************************
 MAIN
 parte principal donde se ejecuta el codigo
 *********************************************************************************************************************************************
 */
int main() {
    examen *examen1 = new examen("julio" , "examen1");
    examen1->anadirSeccion(true, "RespuestaCorta1");
    examen1->anadirSeccion(true, "RespuestaCorta2");
    examen1->anadirSeccion(false, "Selecion Unica");
    cout << "PROBANDO AÑADIR SECCIONES" << endl;
    examen1->imprimirInforme();
    examen1->borrarSeccion("RespuestaCorta1");
    cout << "PROBANDO BORRAR SECCIONES" << endl;
    examen1->imprimirInforme();

    archivador archivadorprincipal = archivador();
    archivadorprincipal.anadirExamen("beto", "Quimica1");
    archivadorprincipal.anadirExamen("beto", "algebra2");
    archivadorprincipal.anadirExamen("beto", "algebra3");
    archivadorprincipal.anadirExamen("beto", "algebra4");
    archivadorprincipal.imprimirExamenes();
    archivadorprincipal.borrarExamen("algebra4");
    archivadorprincipal.imprimirExamenes();
    return 0;
}
