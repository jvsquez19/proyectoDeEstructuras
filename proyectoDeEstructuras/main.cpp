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
struct nodoRespuesta{
    string respuesta;
    nodoRespuesta *siguiente;
};
struct preguntaSeleccionUnica{
    int numero;
    string textoPregunta;
    int cantOpciones;
    nodoRespuesta *cabezaRespuesta;
    void anadirRespuesta(){
        nodoRespuesta *nuevaRespuesta = new nodoRespuesta;
        if(cabezaRespuesta == NULL){
            cabezaRespuesta = nuevaRespuesta;
            nuevaRespuesta->siguiente = cabezaRespuesta;
        }
        else{
            nodoRespuesta *actual = cabezaRespuesta;

            while(actual->siguiente!= cabezaRespuesta)
                actual = actual->siguiente;
            actual->siguiente = nuevaRespuesta;
            nuevaRespuesta->siguiente = cabezaRespuesta;
            cout << "DIGITE EL TEXTO DE LA RESPUESTA" << endl;
            getline(cin,nuevaRespuesta->respuesta,'n');
            cout << "AÑADIDO" << endl;
        }

    }
    void borrarRespuesta(){
        string aBorrar;
        nodoRespuesta *actual = cabezaRespuesta;
        cout << "DIGITE LA RESPUESTA A BORRAR" << endl;
        getline(cin,aBorrar,'n');
        while(actual->siguiente!=cabezaRespuesta)
            if(aBorrar==actual->siguiente->respuesta){
                nodoRespuesta *tmp = actual->siguiente;
                actual->siguiente = actual->siguiente->siguiente;
                free(tmp);
                cout << "BORRADO" << endl;
                return;
            }
        cout << "respuesta no encontrada" << endl;
        return;
    }


};



struct preguntaRespuestaCorta{
    int numero;
    string textoPregunta;
    string RespuestaCorrecta;
    int PuntajeDePregunta;
    int PuntajeObtenido;


};

struct nodoPreguntaSeleccionUnica{
    preguntaSeleccionUnica *preguntaActual;
    nodoPreguntaSeleccionUnica *siguiente;
};

struct nodoPreguntaRespuestaCorta{
    preguntaRespuestaCorta *preguntaActual;
    nodoPreguntaRespuestaCorta *siguiente;
};


class seccion{
private:
    string nombre;
    int PuntajeDeSeccion;
    int PuntajeDeSeccionObtenido;
    bool tipo; // true-> Respuesta Corta || false-> Seleccion Única
    nodoPreguntaSeleccionUnica *listaPreguntasSeleccionUnica;
    nodoPreguntaRespuestaCorta *listaPreguntasRespuestaCorta;

public:
    seccion(bool tipo1, string newnombre){
        tipo = tipo1;
        PuntajeDeSeccion = 0;
        nombre = newnombre;
    }

    void ImprimirInforme();
    int calificarSeccion();
    void anadirPregunta();
    void borrarPregunta(int numeroPregunta);
    void setNombre();
    string getNombre();


};

string seccion::getNombre(){
    return nombre;
}

void seccion::anadirPregunta(){
    if (tipo){
        preguntaRespuestaCorta *nuevaPregunta = new preguntaRespuestaCorta;
        cout << "DIGITE EL TEXTO DE LA PREGUNTA" << endl;
        getline(cin,nuevaPregunta->textoPregunta,'n');
        cout << "AHORA DIGITE LA RESPUESTA CORRECTA" << endl;
        getline(cin, nuevaPregunta->RespuestaCorrecta,'n');
        nodoPreguntaRespuestaCorta *nuevoNodo = new nodoPreguntaRespuestaCorta;
        nuevoNodo->siguiente = listaPreguntasRespuestaCorta;
        nuevoNodo->preguntaActual = nuevaPregunta;
        listaPreguntasRespuestaCorta = nuevoNodo;

    }

    else{
        preguntaSeleccionUnica *nuevaPregunta = new preguntaSeleccionUnica;
        cout << "DIGITE EL TEXTO DE LA PREGUNTA" << endl;
        getline(cin,nuevaPregunta->textoPregunta,'n');
        cout << "AHORA DIGITE EL NUMERO DE OPCIONES QUE DESEA PARA LA PREGUNTA:" << endl;
        cin >>nuevaPregunta->cantOpciones;

        nodoPreguntaSeleccionUnica *nuevoNodo = new nodoPreguntaSeleccionUnica;
        nuevoNodo->siguiente = listaPreguntasSeleccionUnica;
        nuevoNodo->preguntaActual = nuevaPregunta;
        listaPreguntasSeleccionUnica = nuevoNodo;
    }

}

void seccion::borrarPregunta(int numeroPregunta){// true-> Respuesta Corta || false-> Seleccion Única
    if (tipo){
        nodoPreguntaRespuestaCorta *actualCorta = listaPreguntasRespuestaCorta;
        if (listaPreguntasRespuestaCorta == NULL){
            cout<<"Esta seccion no contiene preguntas. "<<endl;
            return;}
        if(actualCorta->preguntaActual->numero == numeroPregunta){
            cout << "Borrando..." << actualCorta->preguntaActual->numero<< endl;
            listaPreguntasRespuestaCorta = actualCorta->siguiente;
            free(actualCorta);
            return;
        }
    while(actualCorta->siguiente!= NULL){
        if(actualCorta->siguiente->preguntaActual->numero== numeroPregunta){
            nodoPreguntaRespuestaCorta *nodoBorrar = actualCorta->siguiente;
            actualCorta->siguiente = actualCorta->siguiente->siguiente;
            free(nodoBorrar);
            return;
        }
            actualCorta = actualCorta->siguiente;
    }
    return;
    }

    else {
        nodoPreguntaSeleccionUnica *actualUnica = listaPreguntasSeleccionUnica;
        if (listaPreguntasSeleccionUnica == NULL){
            cout<<"Esta seccion no contiene preguntas. "<<endl;
            return;}
        if(actualUnica->preguntaActual->numero == numeroPregunta){
            cout << "Borrando..." << actualUnica->preguntaActual->numero<< endl;
            listaPreguntasSeleccionUnica = actualUnica->siguiente;
            free(actualUnica);
            return;
        }
    while(actualUnica->siguiente!= NULL){
        if(actualUnica->siguiente->preguntaActual->numero== numeroPregunta){
            nodoPreguntaSeleccionUnica *nodoBorrar = actualUnica->siguiente;
            actualUnica->siguiente = actualUnica->siguiente->siguiente;
            free(nodoBorrar);
            return;
        }
            actualUnica = actualUnica->siguiente;
    }
    return;
    }
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
    cout<<"Seccion agregada con exito.\n\n\n\n";
    return;
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
    nodoExamen *buscarExamen(string nombreExamen);
    void imprimirExamenes();
    void llenarExamen(string examenModificar);
};

void archivador::anadirExamen(string profesor, string nombreExamen){
    nodoExamen *nuevoNodo = new nodoExamen();
    examen *nuevoExamen = new examen(profesor,nombreExamen); //se crea examen con el constructor de examen

    nuevoNodo->examenEnNodo = nuevoExamen;//se apunta al examen en nodo el examen que se va a crear

    nuevoNodo->siguiente = listaExamenes;
    listaExamenes = nuevoNodo;
    cantidadExamenes++;
    cout<<"Agregado con exito. \n\n\n\n";
}

 nodoExamen *archivador::buscarExamen(string nombreExamen){
    nodoExamen *nodoActual = listaExamenes;
    while (nodoActual!=NULL){
        if (nodoActual->examenEnNodo->getNombre()== nombreExamen)//si el nombre del examen es igual al del nodo
            return nodoActual;
        nodoActual = nodoActual->siguiente;
    }
    return NULL ;
}

void archivador::borrarExamen(string nombreExamen){
    nodoExamen *nodoActual = listaExamenes;
    if (listaExamenes == NULL){
        cout<<"No hay examenes. \n\n\n\n";
        return;
    }
    if (listaExamenes->examenEnNodo->getNombre() == nombreExamen){
        listaExamenes = nodoActual->siguiente;
        free(nodoActual);
        cout<<"Borrado con exito. \n\n\n\n";
        return;
    }
    while(nodoActual->siguiente!=NULL){
        if (nodoActual->siguiente->examenEnNodo->getNombre() == nombreExamen){
            nodoExamen *nodoBorrar = nodoActual->siguiente;
            nodoActual->siguiente = nodoActual->siguiente->siguiente;
            free(nodoBorrar);
            cout<<"Borrado con exito. \n\n\n\n";
            return;
        }
        nodoActual = nodoActual->siguiente;
    }
    cout<<"No existe ese examen!"<<endl;
    return;
}

void archivador::imprimirExamenes(){
    nodoExamen *tmp = listaExamenes;
    cout << "\n\n\n\nIMPRIMIENDO EXAMENES " << endl;
    while(tmp != NULL){
        cout << tmp->examenEnNodo->getNombre()<<endl;
        tmp = tmp->siguiente;
    }
    cout<<"\n\n\n\n";
}

void archivador::llenarExamen(string examenModificar){
    nodoExamen *nodoExamenModificar = buscarExamen(examenModificar);
    if (nodoExamenModificar == NULL){
        cout<<"No se encontro el examen requerido. \n\n\n\n";
        return;
    }
    int opcion;string nombreSeccion;
    cout<<"Escriba el nombre de la seccion para agregar: ";cin>>nombreSeccion;
    cout<<"\n\n\n\n1. Seccion Seleccion unica. \n"
          "2. Seccion Respuesta Corta. \n"
          "Cualquier otra tecla para cancelar"
          "Que seccion desea agregar: ";cin>>opcion;
          switch(opcion){
            case 1:
                nodoExamenModificar->examenEnNodo->anadirSeccion(false,nombreSeccion);
                return;
            case 2:
                nodoExamenModificar->examenEnNodo->anadirSeccion(true,nombreSeccion);
                return;
            default:
                cout<<"\n\n\n\n";
                return;
          }
}
/*
 *********************************************************************************************************************************************
 MAIN
 parte principal donde se ejecuta el codigo
 *********************************************************************************************************************************************
 */

void menu(archivador *nuevoArchivador){
    int opcion;
    string profesor,nombreExamen,examenModificar,examenBorrar,nombreAlumno,nombreExamenAlumno;
    cout<<"BIENVENIDO! \n"
          "1. Crear examen. \n"
          "2. Llenar examen. \n"
          "3. Borrar examen. \n"
          "4. Realizar examen. \n"
          "5. Ver todos los examenes (nombre examen). \n"
          "6. Calificar examen. \n"
          "7. Salir \n"
          "Seleccione una opcion: ";
          cin>>opcion;
    switch (opcion){
        case 1:
            cout<<"\n\n\n\nDigite su nombre (profesor): ";
            cin>>profesor;
            cout<<"Digite el nombre del examen a crear: ";
            cin>>nombreExamen;
            nuevoArchivador->anadirExamen(profesor,nombreExamen);
            return;

        case 2:
            cout<<"\n\n\n\nDigite el nombre del examen para ser llenado: ";
            cin>>examenModificar;
            nuevoArchivador->llenarExamen(examenModificar);
            return;

        case 3:
            cout<<"\n\n\n\nDigite el nombre del examen para ser borrado: ";
            cin>>examenBorrar;
            nuevoArchivador->borrarExamen(examenBorrar);
            return;

        case 4:
            cout<<"\n\n\n\nEscriba el nombre del examen que quiere realizar (alumno): ";
            cin>>nombreExamenAlumno;
            cout<<"Escriba su nombre para realizar el examen: ";
            cin>>nombreAlumno;
            ///nodoExamen *examenAlumno;
            ///examenAlumno = nuevoArchivador->buscarExamen(nombreExamenAlumno);
            //examenAlumno = falta crear metodo para realizar examen en archivador(nombreAlumno)
            return;
        case 5:
            nuevoArchivador->imprimirExamenes();
            return;

        case 6:
            //metodo de calificacion de examenes
            return;

        case 7:
            exit(0);

        default:
            cout<<"\n\n\n\nEse digito es incorrecto. Intente de nuevo\n\n\n\n";
            return;}

}


int main() {
    archivador *nuevoArchivador = new archivador();
    while(true)
        menu(nuevoArchivador);
    return 0;
}
