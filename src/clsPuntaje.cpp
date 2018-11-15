//#############################################################################
// ARCHIVO             : clsMotor.cpp
// AUTOR               : Juan Agustin Gonzalez
// VERSION             : 1.0.
// FECHA DE CREACION   : 06/10/2018.
// ULTIMA ACTUALIZACION: 15/11/2018.          .
// LICENCIA             : GPL (General Public License) - Version 3.
//=============================================================================
// SISTEMA OPERATIVO   : Linux / Windows.
// IDE                 : Code::Blocks - 17.12.
// COMPILADOR          : GNU GCC Compiler (Linux) / MinGW (Windows).
//=============================================================================
// DESCRIPCION: Este archivo contiene la definici�n de los m�todos de la clas
//              "clsMotor".
//
//              "clsMotor" consta de los objetos necesarios para levantar el
//              modo gr�fico, la presentaci�n, el juego y la salida.
//
///////////////////////////////////////////////////////////////////////////////
#include "clsPuntaje.h"

int clsPuntaje::init()
{
    puntos = 0;
    strcpy(nombre, "");

    FILE *p = fopen("puntajes.dat", "rb");
    if(p == NULL) p = fopen("puntajes.dat", "wb");
    fclose(p);

    return 0;
}

void clsPuntaje::guardar()
{
    FILE *p = fopen("puntajes.dat", "ab");
    fwrite(this, sizeof(clsPuntaje), 1, p);
    fclose(p);
}

void clsPuntaje::setNombre(const char* nombre)
{
    strcpy(this->nombre, nombre);
}

void clsPuntaje::setPuntos(int p)
{
    puntos = p;
}

int clsPuntaje::getPuntos()
{
    return puntos;
}

const char* clsPuntaje::getNombre()
{
    return nombre;
}

void clsPuntaje::operator=(clsPuntaje externo)
{
    this->puntos = externo.puntos;
    strcpy(this->nombre, externo.nombre);
}
