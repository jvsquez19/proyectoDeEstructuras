//
//  seccion.h
//  proyectoDeEstructuras
//
//  Created by Jafeth  Vásquez on 11/9/16.
//  Copyright © 2016 Jafeth Vásquez. All rights reserved.
//

#ifndef seccion_h
#define seccion_h

using namespace std;


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
    int calificar();
    void añadirPregunta();
    void borrarPregunta();
    void setNombre();
    string getNombre();
    
    
};

string seccion::getNombre(){
    return nombre;
}

void seccion::añadirPregunta(){
    
    
}


#endif /* seccion_h */
