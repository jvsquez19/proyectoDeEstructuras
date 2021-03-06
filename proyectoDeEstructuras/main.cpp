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
#include <vector>
#include <functional>
#include <time.h>

using namespace std;

/*

 SECCION CLASS

 Clase donde se encuentra la estructura de seccion y se pueden añadir preguntas.
 *********************************************************************************************************************************************

 */
// Esta estructura almacena una respuesta de una pregunta de seleccion Única
struct nodoRespuesta{
    string respuesta;
    nodoRespuesta *siguiente;
};

// Esta estructura contiene la cantidad de respuestas, los puntos que vale y el número de una pregunta.
struct preguntaSeleccionUnica{
    int numero,cantOpciones,valorPregunta;
    string textoPregunta;
    nodoRespuesta *cabezaRespuesta = NULL;
    bool correcto;

// Metodo/Funcion dentro del struct que permite añadir una respuesta para la pregunta.
    void anadirRespuesta(){
        int contador = 0;
        string respuesta;
        contador = cantOpciones;
        cout<<"Digite la respuesta correcta: ";
        getline(cin,respuesta,'\n');getline(cin,respuesta,'\n');

        while(contador!=0){
        if (cabezaRespuesta == NULL){
            nodoRespuesta *nuevaRespuesta = new nodoRespuesta();
            nuevaRespuesta->siguiente = nuevaRespuesta;
            nuevaRespuesta->respuesta = respuesta;
            cabezaRespuesta = nuevaRespuesta;
            contador --;
            continue;
        }
        else {
            cout<<"Digite la respuesta incorrecta: ";
            getline(cin,respuesta,'\n');
            nodoRespuesta *actualRespuesta = cabezaRespuesta;
            while(actualRespuesta->siguiente != cabezaRespuesta){
                actualRespuesta = actualRespuesta->siguiente;
            }
            nodoRespuesta *nuevaRespuesta = new nodoRespuesta();
            nuevaRespuesta->respuesta = respuesta;
            actualRespuesta->siguiente = nuevaRespuesta;
            nuevaRespuesta->siguiente = cabezaRespuesta;
            contador--;
            continue;
            }

        }
        nodoRespuesta *tmp = cabezaRespuesta;
        cout<<"\n\nVISTA PRELIMINAR DE RESPUESTAS: ";
        do {
            cout<<tmp->respuesta<<"\n";
            tmp=tmp->siguiente;
        } while(tmp!=cabezaRespuesta);
        return;
    }

    int calificar(){
        nodoRespuesta *respuestaActual = cabezaRespuesta;
        int opcionUsuario;
        int tmp = 0;
        nodoRespuesta *Arreglo[cantOpciones];//que va en la lista que se va a crear de nodos
        int random = rand()%cantOpciones+1;


        for(int i = 1;i<random;i++)
            respuestaActual = respuestaActual->siguiente;

        nodoRespuesta *opcion = respuestaActual;
        Arreglo[tmp] = opcion;
        tmp++;
        do {
            Arreglo[tmp] = opcion->siguiente;
            tmp++;
            opcion = opcion->siguiente;
        } while(opcion->siguiente != respuestaActual);

        cout <<"\n\n"<<textoPregunta << endl;
        for(int x = 0;x<cantOpciones;x++)
            cout<<x+1<<". "<<Arreglo[x]->respuesta<<"\n";
        cout<<"Escoja una opcion: ";cin>>opcionUsuario;

        ///parte de calificar

        if (Arreglo[opcionUsuario-1]==cabezaRespuesta){
            correcto = true;
            return valorPregunta;}
        else{
            correcto = false;
            return 0;
        }
    }
};

struct preguntaRespuestaCorta{
    int numero;
    string textoPregunta;
    string RespuestaCorrecta;
    bool correcto;
    int PuntajeDePregunta;

    /*METODO CALIFICAR

     Pide al usuario la respuesta y luego compara cada uno de los caracteres del string con la respuesta correcta.
     Para determinar que respondio correctamente ambos strings deben tener un 60% similitud */

    int calificar(){
        string respuestaUsuario;
        int aciertos = 0;
        cout << textoPregunta << endl;
        getline(cin,respuestaUsuario,'\n');
        int longitud1 = RespuestaCorrecta.length();
        int longitud2= respuestaUsuario.length();

        int tmp = 0;
        while((tmp < longitud1)&&(tmp < longitud2)){
            if (RespuestaCorrecta[tmp]==respuestaUsuario[tmp]){
                aciertos++;
                cout << RespuestaCorrecta[tmp];
                tmp++;
            }
            else
                tmp++;
        }
        if (aciertos > (longitud1 * 0.6)){ // Si existe más de un 60% de acierto se califica como correcta y obtiene todos los puntos.
            correcto = true;
            return PuntajeDePregunta;
        }
        correcto = false;
        return 0;
    }

};

struct nodoPreguntaSeleccionUnica{
    preguntaSeleccionUnica *preguntaActual;
    nodoPreguntaSeleccionUnica *siguiente;
    nodoPreguntaSeleccionUnica *anterior;
};
struct nodoPreguntaRespuestaCorta{
    preguntaRespuestaCorta *preguntaActual;
    nodoPreguntaRespuestaCorta *siguiente;
    nodoPreguntaRespuestaCorta *anterior;
};

class seccion{
private:
    string nombre;
    int puntajeDeSeccion;
    int puntajeDeSeccionObtenido;
    bool tipo; // true-> Respuesta Corta || false-> Seleccion Única
    nodoPreguntaSeleccionUnica *listaPreguntasSeleccionUnica = NULL;
    nodoPreguntaRespuestaCorta *listaPreguntasRespuestaCorta = NULL;

public:
    seccion(bool tipo1, string newnombre){
        tipo = tipo1;
        puntajeDeSeccion = 0;
        nombre = newnombre;
    }

    void ImprimirInforme();
    int calificarSeccion(bool modalidad);
    void anadirPregunta();
    void borrarPregunta(int numeroPregunta);
    void setNombre();
    string getNombre();
    void menuseccion();
    void imprimirPreguntasSeleccionUnica();
    void imprimirPreguntasRespuestaCorta();
    void imprimirCorrectas();
    int getPuntajeDeSeccion();

};

int seccion::getPuntajeDeSeccion(){
    return puntajeDeSeccion;
}

//////////////////
////////////////
//////////////

string seccion::getNombre(){
    return nombre;
}

/* METODO CALIFICAR SECCION:

 En este metodo se califica la seccion para hacerlo se llama al metodo calificar de cada una de sus preguntas y va sumando la nota que luego se guardara en Puntaje Obtenido.*/

int seccion::calificarSeccion(bool modalidad){
    if(modalidad){
    if(tipo){
        nodoPreguntaRespuestaCorta *actual = listaPreguntasRespuestaCorta;
        while(actual != NULL){
            puntajeDeSeccion += actual->preguntaActual->PuntajeDePregunta;
            actual = actual->siguiente;
            continue;
        }
        actual = listaPreguntasRespuestaCorta;
        while(actual != NULL){
            puntajeDeSeccionObtenido += actual->preguntaActual->calificar();
            actual = actual->siguiente;
            continue;
        }
    }
    else{
        nodoPreguntaSeleccionUnica *actual = listaPreguntasSeleccionUnica;
        if(actual == NULL){
            return 0;}
        while(actual != NULL){
            puntajeDeSeccion += actual->preguntaActual->valorPregunta;
            actual = actual->siguiente;
            continue;
        }
        actual = listaPreguntasSeleccionUnica;
        while(actual != NULL){
            puntajeDeSeccionObtenido += actual->preguntaActual->calificar();
            actual = actual->siguiente;
            continue;
        }


        }
    }
    else{
        if(tipo){
            nodoPreguntaRespuestaCorta *actual = listaPreguntasRespuestaCorta;

            if(actual == NULL){
                return 0;}
            while(actual->siguiente != NULL){
                actual = actual->siguiente;
            }
            nodoPreguntaRespuestaCorta *tmp = actual;
            while(tmp != NULL){
                puntajeDeSeccion += actual->preguntaActual->PuntajeDePregunta;
                tmp = tmp->anterior;
                continue;
            }
            while(actual != NULL){
                puntajeDeSeccionObtenido += actual->preguntaActual->calificar();
                actual = actual->anterior;
                continue;
            }
        }
        else{
            nodoPreguntaSeleccionUnica *actual = listaPreguntasSeleccionUnica;
            if(actual == NULL){
                return 0;
            }
            while(actual->siguiente != NULL){
                actual = actual->siguiente;
            }
            nodoPreguntaSeleccionUnica *tmp = actual;

            while(tmp != NULL){
                puntajeDeSeccion += tmp->preguntaActual->valorPregunta;
                tmp = tmp->anterior;
                continue;
            }
            while(actual != NULL){
                puntajeDeSeccionObtenido += actual->preguntaActual->calificar();
                actual = actual->anterior;
                continue;
            }
    }
    }
        return puntajeDeSeccionObtenido;

};






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////
////////////////
//////////////

void seccion::anadirPregunta(){

// Solicitud de informacion...

    string pregunta, respuesta;
    int cantidad, valor;

    /// Si es Pregunta Respuesta Corta.
    if (tipo){
        preguntaRespuestaCorta *nuevaPregunta = new preguntaRespuestaCorta;
        cout << "DIGITE EL TEXTO DE LA PREGUNTA" << endl;
        getline(cin,pregunta,'\n');
        getline(cin,pregunta,'\n');
        cout << "AHORA DIGITE EL PUNTAJE QUE TENDRÁ LA PREGUNTA: ";
        int puntaje;
        cin >> puntaje;
        nuevaPregunta->PuntajeDePregunta = puntaje;
        nuevaPregunta->textoPregunta = pregunta;
        cout << "AHORA DIGITE LA RESPUESTA CORRECTA" << endl;
        getline(cin,respuesta,'\n');
        getline(cin,respuesta,'\n');
        nuevaPregunta->RespuestaCorrecta = respuesta;

// Insersion en la lista...

            nodoPreguntaRespuestaCorta *actual = listaPreguntasRespuestaCorta;
            nodoPreguntaRespuestaCorta *nuevoNodo = new nodoPreguntaRespuestaCorta;
            nuevoNodo->preguntaActual = nuevaPregunta;
        if(actual == NULL){
                listaPreguntasRespuestaCorta = nuevoNodo;
                return;
        }

        else if(actual->preguntaActual->PuntajeDePregunta < nuevaPregunta->PuntajeDePregunta){
            nuevoNodo->siguiente = actual;               // si es mayor se inserta antes de acutal.
            nuevoNodo->anterior = actual->anterior;
            actual->anterior = nuevoNodo;
            listaPreguntasRespuestaCorta = nuevoNodo;
            return;
        }


                while(actual != NULL) { // Recorre la lista

                    if(actual->preguntaActual->PuntajeDePregunta < nuevaPregunta->PuntajeDePregunta){ // si es si es mayor inserta
                        nuevoNodo->siguiente = actual;
                        nuevoNodo->anterior = actual->anterior;
                        actual->anterior->siguiente=nuevoNodo;
                        actual->anterior = nuevoNodo;
                        //listaPreguntasSeleccionUnica = nuevoNodo;
                        break;

                    }
                    else if(actual->siguiente == NULL){
                        nuevoNodo->anterior = actual;
                        actual->siguiente = nuevoNodo;
                        cout << "actual->siguiente == NULL" << endl;
                        break;
                    }



                    else{
                        actual = actual->siguiente;
                        continue;
                    }
                }
            }

    else{// Si es pregunta en seleccion unica.
        preguntaSeleccionUnica *nuevaPregunta = new preguntaSeleccionUnica;
        cout << "DIGITE EL TEXTO DE LA PREGUNTA: ";
        getline(cin,pregunta,'\n');
        getline(cin,pregunta,'\n');
        nuevaPregunta->textoPregunta = pregunta;

        cout << "AHORA DIGITE EL NUMERO DE OPCIONES QUE DESEA PARA LA PREGUNTA: ";
        cin>>cantidad;
        nuevaPregunta->cantOpciones = cantidad;

        cout<< "POR ULTIMO, DIGITE EL VALOR DE LA PREGUNTA: ";
        cin>>valor;
        nuevaPregunta->valorPregunta = valor;
        nuevaPregunta->anadirRespuesta();

        nodoPreguntaSeleccionUnica *nuevoNodo = new nodoPreguntaSeleccionUnica;
        nodoPreguntaSeleccionUnica *actual = listaPreguntasSeleccionUnica;

            nuevoNodo->preguntaActual = nuevaPregunta;
        if(actual == NULL){
                listaPreguntasSeleccionUnica = nuevoNodo;
                return;}
        else if(actual->preguntaActual->valorPregunta < nuevaPregunta->valorPregunta){
            nuevoNodo->siguiente = actual;               // si es mayor se inserta antes de acutal.
            nuevoNodo->anterior = actual->anterior;
            actual->anterior = nuevoNodo;
            listaPreguntasSeleccionUnica = nuevoNodo;
            return;
            }

            while(actual != NULL) { // Recorre la lista

                if(actual->preguntaActual->valorPregunta < nuevaPregunta->valorPregunta){ // si es si es mayor inserta
                    nuevoNodo->siguiente = actual;
                    nuevoNodo->anterior = actual->anterior;
                    actual->anterior->siguiente=nuevoNodo;
                    actual->anterior = nuevoNodo;
                    //listaPreguntasSeleccionUnica = nuevoNodo;
                    break;

                }
                else if(actual->siguiente == NULL){
                    nuevoNodo->anterior = actual;
                    actual->siguiente = nuevoNodo;
                    break;
                }



                else{
                    actual = actual->siguiente;
                    continue;
                }
            }
        return;
    }
}

//////////////////
////////////////
//////////////


void seccion::imprimirCorrectas(){
    if(tipo){
        nodoPreguntaRespuestaCorta *actual = listaPreguntasRespuestaCorta;
        int contador = 1;
        while (actual != NULL) {
            if (actual->preguntaActual->correcto) {
                cout << "Pregunta " << contador <<" CORRECTA " << actual->preguntaActual->PuntajeDePregunta << " Puntos Obtenidos" << endl;
                cout << actual->preguntaActual->textoPregunta << "\n\n";
                contador++;
            }
            else{
                    cout << "Pregunta " << contador <<" INCORRECTA " << actual->preguntaActual->PuntajeDePregunta << " Puntos Perdidos" << endl;
                    cout << actual->preguntaActual->textoPregunta << "\n\n";
                    contador++;
            }
            actual = actual->siguiente;
        }
    }
    else{
        nodoPreguntaSeleccionUnica *actual = listaPreguntasSeleccionUnica;
        int contador = 1;
        while (actual != NULL) {
            if (actual->preguntaActual->correcto) {
                cout << "Pregunta " << contador <<" CORRECTA " << actual->preguntaActual->valorPregunta << " Puntos Obtenidos" << endl;
                cout << actual->preguntaActual->textoPregunta << "\n\n";
                contador++;
            }
            else{
                cout << "Pregunta " << contador <<" INCORRECTA " << actual->preguntaActual->valorPregunta << " Puntos Perdidos" << endl;
                cout << actual->preguntaActual->textoPregunta << "\n\n";
                contador++;
            }
            actual = actual->siguiente;
        }
    }
}

//////////////////
////////////////
//////////////

void seccion::imprimirPreguntasSeleccionUnica(){
    nodoPreguntaSeleccionUnica *actualUnica = listaPreguntasSeleccionUnica;
    if (actualUnica == NULL){
        cout<<"No hay preguntas...\n\n";
        return;
    }
    while(actualUnica!=NULL){
        cout<<"Pregunta: "<<actualUnica->preguntaActual->valorPregunta<<endl;
        actualUnica = actualUnica->siguiente;
    }
    return;
}

void seccion::imprimirPreguntasRespuestaCorta(){
    nodoPreguntaRespuestaCorta *actualCorta = listaPreguntasRespuestaCorta;
    if (actualCorta == NULL){
        cout<<"No hay preguntas...\n\n";
        return;
    }
    while(actualCorta!=NULL){
        cout<<"Pregunta: "<<actualCorta->preguntaActual->textoPregunta<<endl;
        actualCorta = actualCorta->siguiente;
    }
    return;
}

//////////////////
////////////////
//////////////


void seccion::borrarPregunta(int numeroPregunta){// true-> Respuesta Corta || false-> Seleccion Única
    if (tipo){
        int contador = 1;
        nodoPreguntaRespuestaCorta *tmp = listaPreguntasRespuestaCorta;
        while(tmp != NULL){
            tmp->preguntaActual->numero = contador;
            contador++;
            tmp = tmp->siguiente;
        }
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

//////////////////
////////////////
//////////////

void seccion::menuseccion(){
    char opcion;int num;
    while(true){
        cout <<"\n\n\n\n"
        "1. Agregar pregunta. \n"
        "2. Borrar pregunta. \n"
        "3. Cambiar nombre de la seccion. \n"
        "4. Salir \n"
        "5 y 6 Imprimir preguntas. \n"
        "Seleccione una opcion: ";
        cin>>opcion;
        switch(opcion){
            case '1':
                anadirPregunta();
                break;
            case '2':
                cout << "\n\nDigite el nuumero de la pregunta a borrar: ";
                cin>>num;
                borrarPregunta(num);
                break;
            case '3':
                cout << "Digite el nuevo nombre para la sección" << endl;
                getline(cin,nombre,'\n');getline(cin,nombre,'\n');
                break;
            case '4':
                return;
            case '5':
                imprimirPreguntasSeleccionUnica();
                break;
            case '6':
                imprimirPreguntasRespuestaCorta();
                break;
            default:
                cout<<"\n\n\n\nERROR FATAL!!!!! ENTRADA INVALIDA";
                break;
        }
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
    nodoSeccion *getSeccion();

};

//////////////////
////////////////
//////////////

nodoSeccion *examen::getSeccion(){
    return listaSecciones;
}


//////////////////
////////////////
//////////////


void examen::anadirSeccion(bool tipo, string nombre){
    seccion *nuevaSeccion = new seccion(tipo, nombre);
    nodoSeccion *nuevoNodo = new nodoSeccion();
    nuevoNodo->seccionActual = nuevaSeccion;
    nuevoNodo->siguiente = listaSecciones;
    listaSecciones = nuevoNodo;
    cout<<"Seccion agregada con exito.\n\n\n\n";
    return;
};

//////////////////
////////////////
//////////////

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

//////////////////
////////////////
//////////////

int examen::calificarExamen(){
    cout << "Digite 1 si desea responder las preguntas de menor a mayor o cualquier tecla para responderlas en orden descendente" << endl;
    bool modalidad;
    int opcion;
    cin >> opcion;
    if(opcion == 1)
        modalidad = true;
    else
        modalidad = false;
    int puntajeObtenido = 0;
    nodoSeccion *actual = listaSecciones;

    while (actual != NULL) {
        puntajeObtenido += actual->seccionActual->calificarSeccion(modalidad);
        actual = actual->siguiente;
    }
    actual = listaSecciones;
    while(actual != NULL){
        puntaje += actual->seccionActual->getPuntajeDeSeccion();
        actual->seccionActual->imprimirCorrectas();
        actual = actual->siguiente;
    }
    cout << "Su nota en este Examen es de: " << ((puntajeObtenido* 1.0) * 100)/puntaje << endl;
    return puntajeObtenido;
}

//////////////////
////////////////
//////////////

void examen::setProfesor(string profeNuevo){
    profesor = profeNuevo;

}

//////////////////
////////////////
//////////////

string examen::getProfesor(){
    return profesor;
}

//////////////////
////////////////
//////////////

void examen::setNombre(string entradaNombre){
    nombre = entradaNombre;
}

//////////////////
////////////////
//////////////

string examen::getNombre(){
    return nombre;
}

//////////////////
////////////////
//////////////

void examen::imprimirInforme(){
    nodoSeccion *tmp = listaSecciones;
    while(tmp != NULL){
        cout << tmp->seccionActual->getNombre() << endl;
        tmp = tmp->siguiente;
    }
}
//////////////////
////////////////
//////////////

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
    void llenarExamen(nodoExamen *nodoExamenModificar);
    int getCantidadExamenes();
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
void archivador::llenarExamen(nodoExamen *nodoExamenModificar){
    if (nodoExamenModificar == NULL){
        cout<<"No se encontro el examen requerido. \n\n\n\n";
        return;
    }
    char opcion;string nombreSeccion;
    while (true){
    cout<<"\n\n\n\nOPCIONES LLENAR EXAMEN \n"
          "1. Seccion Seleccion unica. \n"
          "2. Seccion Respuesta Corta. \n"
          "Cualquier otra tecla para cancelar \n"
          "\nQue seccion desea agregar: ";cin>>opcion;
          switch(opcion){
            case '1':
                cout<<"\n\nEscriba el nombre de la seccion para agregar: ";
                getline(cin,nombreSeccion,'\n');getline(cin,nombreSeccion,'\n');
                nodoExamenModificar->examenEnNodo->anadirSeccion(false,nombreSeccion);
                nodoExamenModificar->examenEnNodo->getSeccion()->seccionActual->menuseccion();
                break;
            case '2':
                cout<<"\n\nEscriba el nombre de la seccion para agregar: ";
                getline(cin,nombreSeccion,'\n');getline(cin,nombreSeccion,'\n');
                nodoExamenModificar->examenEnNodo->anadirSeccion(true,nombreSeccion);
                nodoExamenModificar->examenEnNodo->getSeccion()->seccionActual->menuseccion();
                break;
            default:
                cout<<"\n\n\n\n";
                return;
            }
    }
}
int archivador::getCantidadExamenes(){
    return cantidadExamenes;
};
/*
 *********************************************************************************************************************************************
 MAIN
 parte principal donde se ejecuta el codigo
 *********************************************************************************************************************************************
 */
void menu(archivador *nuevoArchivador){
    char opcion;
    string profesor,nombreExamen,examenModificar,examenBorrar,nombreAlumno,nombreExamenAlumno;
    cout<<"BIENVENIDO! \n"
          "1. Crear examen. \n"
          "2. Llenar examen. \n"
          "3. Borrar examen. \n"
          "4. Realizar examen. \n"
          "5. Ver todos los examenes (nombre examen). \n"
          "6. Numero de examenes creados \n"
          "7. Salir \n"
          "Seleccione una opcion: ";
          cin>>opcion;

    switch (opcion){
        case '1':
            cout<<"\n\n\n\nDigite su nombre (profesor): ";
            cin>>profesor;
            cout<<"Digite el nombre del examen a crear: ";
            getline(cin,nombreExamen,'\n');getline(cin,nombreExamen,'\n');
            nuevoArchivador->anadirExamen(profesor,nombreExamen);
            return;

        case '2':
            cout<<"\n\n\n\nDigite el nombre del examen para ser llenado: ";
            getline(cin,examenModificar,'\n');getline(cin,examenModificar,'\n');
            nodoExamen *nodoExamenModificar;
            nodoExamenModificar = nuevoArchivador->buscarExamen(examenModificar);
            nuevoArchivador->llenarExamen(nodoExamenModificar);
            return;

        case '3':
            cout<<"\n\n\n\nDigite el nombre del examen para ser borrado: ";
            getline(cin,examenBorrar,'\n');getline(cin,examenBorrar,'\n');
            nuevoArchivador->borrarExamen(examenBorrar);
            return;

        case '4'://esre es el del calificar el examen
            cout<<"\n\n\n\nEscriba el nombre del examen que quiere realizar (alumno): ";
            getline(cin,nombreExamenAlumno,'\n');getline(cin,nombreExamenAlumno,'\n');
            nodoExamen *examenAlumno;
            examenAlumno = nuevoArchivador->buscarExamen(nombreExamenAlumno);
            examenAlumno->examenEnNodo->calificarExamen();
            return;
        case '5':
            nuevoArchivador->imprimirExamenes();
            return;
        case '6':
            cout<<"\n\n\n\nNumero de examenes: "<<nuevoArchivador->getCantidadExamenes()<<"\n\n\n\n";
            return;

        case '7':
            exit(0);

        default:
            cout<<"\n\n\n\nEse digito es incorrecto. Intente de nuevo\n\n\n\n";
            return;}
}

int main() {
    srand (time(NULL));

    examen *examenPrueba = new examen("Rogelio","Estructuras");

    archivador *prueba = new archivador();

    seccion *seccionPrueba = new seccion(false,"uno");

    archivador *nuevoArchivador = new archivador();
    while(true)
        menu(nuevoArchivador);
    return 0;
}
