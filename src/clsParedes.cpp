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
#include "clsParedes.h"

int clsParedes::init(clsScreen *scr, int cant)
{
    screen = scr;
    cantParedes = cant;
    distHorizontal = 450;
    distVertical = 150;

    random.init();

    inferiores = new clsPared[cantParedes];
    if(inferiores == NULL) return 2;

    superiores = new clsPared[cantParedes];
    if(superiores == NULL) return 2;

    for(int x=0; x<cantParedes; x++)
    {
        error.set(superiores[x].init());
        if(error.get()) return error.get();

        error.set(inferiores[x].init());
        if(error.get()) return error.get();

        superiores[x].setY(random.getNumber(screen->getHeight()-distVertical*2)+distVertical-screen->getHeight());
        superiores[x].setX(distHorizontal*x+(screen->getWidth()*3/2));

        inferiores[x].setY(superiores[x].getY()+screen->getHeight()+distVertical);
        inferiores[x].setX(distHorizontal*x+(screen->getWidth()*3/2));
    }

    return 0;
}

void clsParedes::mostrar()
{
    for(int x=0; x<cantParedes; x++)
    {
        if(superiores[x].getX() <= screen->getWidth() && superiores[x].getX() >= -superiores[x].getWidth())
            superiores[x].paste(screen->getPtr());
        if(inferiores[x].getX() <= screen->getWidth() && inferiores[x].getX() >= -inferiores[x].getWidth())
            inferiores[x].paste(screen->getPtr());
    }
}

void clsParedes::mover(int dist)
{
    for(int x=0; x<cantParedes; x++)
    {
        superiores[x].setX(superiores[x].getX()-dist);
        inferiores[x].setX(inferiores[x].getX()-dist);
    }
}

bool clsParedes::seTocan(clsSprite *sprite)
{
    for(int x=0; x<cantParedes; x++)
    {
        if(superiores[x].getContact(sprite))
            return true;

        if(inferiores[x].getContact(sprite))
            return true;
    }
    return false;
}

int clsParedes::pasadas(clsSprite *spr)
{
    int cont=0;

    for(int x=0; x<cantParedes; x++)
    {
        if(spr->getX() >= superiores[x].getX()+superiores[x].getWidth())
            cont++;
    }

    return cont;
}

clsParedes::~clsParedes()
{
    delete inferiores;
    delete superiores;
}
