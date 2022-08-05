#include "rlutil.h"
#include <iostream>
using namespace std;

namespace pen
{

    void drawHorizontalLines(const int posX, const int posY, int characterAscci, const int longitud, const int separacion, const int cantLines)
    {

        int contLines = 0;
        int newPositionY = posY;

        while (contLines < cantLines)
        {
            contLines++;

            for (int i = 0; i <= longitud; i++)
            {

                // Cambiamos la posicion del cursor
                rlutil::locate(posX + i, newPositionY);

                // Mostramos por consola el 205 de la tabla ascci
                cout << (char)characterAscci;
            }
            newPositionY = posY + separacion;
        }
    }
    void drawVerticalLines(const int posX, const int posY, const int characterAscci, const int longitud, const int separacion, const int cantLines)
    {

        int contLines = 0;
        int newPositionX = posX;

        while (contLines < cantLines)
        {
            contLines++;

            for (int i = 0; i <= longitud; i++)
            {

                // Cambiamos la posicion del cursor
                rlutil::locate(newPositionX, posY + i);

                // Mostramos por consola el 205 de la tabla ascci
                cout << (char)characterAscci;
            }
            newPositionX = posX + separacion;
        }
    }
    void dibujarCuadradoRectangulo(const int posX, const int posY, const int ancho, const int alto)
    {
        drawHorizontalLines(posX, posY, 223, ancho, alto, 2);
        drawVerticalLines(posX, posY, 219, alto - 1, ancho, 2); // Alto -1
    }

    void dibujarDado(const int valor, const int posX, const int posY)
    {

        pen::dibujarCuadradoRectangulo(posX, posY, 10, 5);

        switch (valor)
        {
        case 1:
            rlutil::locate(posX + 5, posY + 2);
            cout << (char)254;
            break;
        case 2:
            rlutil::locate(posX + 3, posY + 3);
            cout << (char)254;
            rlutil::locate(posX + 7, posY + 1);
            cout << (char)254;
            break;
        case 3:
            rlutil::locate(posX + 3, posY + 3);
            cout << (char)254;
            rlutil::locate(posX + 7, posY + 1);
            cout << (char)254;
            rlutil::locate(posX + 5, posY + 2);
            cout << (char)254;
            break;
        case 4:
            rlutil::locate(posX + 3, posY + 1);
            cout << (char)254;
            rlutil::locate(posX + 7, posY + 1);
            cout << (char)254;
            rlutil::locate(posX + 3, posY + 3);
            cout << (char)254;
            rlutil::locate(posX + 7, posY + 3);
            cout << (char)254;

            break;
        case 5:
            rlutil::locate(posX + 3, posY + 1);
            cout << (char)254;
            rlutil::locate(posX + 7, posY + 1);
            cout << (char)254;
            rlutil::locate(posX + 3, posY + 3);
            cout << (char)254;
            rlutil::locate(posX + 7, posY + 3);
            cout << (char)254;
            rlutil::locate(posX + 5, posY + 2);
            cout << (char)254;
            break;
        case 6:
            rlutil::locate(posX + 2, posY + 1);
            cout << (char)254;
            rlutil::locate(posX + 5, posY + 1);
            cout << (char)254;
            rlutil::locate(posX + 8, posY + 1);
            cout << (char)254;
            rlutil::locate(posX + 2, posY + 3);
            cout << (char)254;
            rlutil::locate(posX + 5, posY + 3);
            cout << (char)254;
            rlutil::locate(posX + 8, posY + 3);
            cout << (char)254;
            break;
        }
    }

    void dibujarPantallaFinal(char nombre[15], int tiradasTotales, int puntajes){
        // Limpiamos la pantalla de juego
        rlutil::cls();

        // Dibujamos un rectangulo
        dibujarCuadradoRectangulo(25, 12, 60, 15);

        // Mostramos en mensaje en el medio del rectangulo dibujado
        rlutil::locate(40, 18);
        cout << "El jugador " << nombre;

        rlutil::locate(40, 20);
        cout << "En " << tiradasTotales << " tiradas";

        rlutil::locate(40, 22);
        cout << "obtuvo " << puntajes<< " puntos";

        rlutil::locate(10, 10);
        cout << "Presione cualquier tecla para continuar";

    }

    void pedirNombres(char nombres[2][15], int jugador = 0){
        // Limpiamos la pantalla de menu
        rlutil::cls();

        // Dibujamos un rectangulo
        dibujarCuadradoRectangulo(25, 12, 60, 15);

        // Mostramos en mensaje en el medio del rectangulo dibujado
        rlutil::locate(40, 18);
        cout << "INGRESE NOMBRE DE JUGADOR " << jugador + 1;

        // Asignamos visibilidad al cursor para que se vea mejor
        rlutil::setCursorVisibility(true);

        // Posicionamos el ingreso del nombre
        rlutil::locate(40, 20);

        cin.getline(nombres[jugador], 15);

        // Volvemos a esconder el cursor
        rlutil::hidecursor();
    }
    void dibujarContenidoInterfaz(char nombres[2][15], int dados[5], int *ronda, int *tirada, int puntajes[2], int tiradasTotales[2], int turno = 0){
        int posXD;
        posXD = 5;

        // Dibuja los dados
        for (int i = 0; i < 5; i++)
        {
            pen::dibujarDado(dados[i], posXD, 9);
            posXD += 15;
        }

        rlutil::locate(1, 2);

        cout << "TURNO DE " << nombres[turno];

        rlutil::locate(26, 2);
        cout << "RONDA N" << (char)167 << *ronda;

        rlutil::locate(56, 2);
        cout << "PUNTAJE TOTAL: " << puntajes[turno];

        rlutil::locate(1, 5);
        cout << "TIRADA N" << (char)167 << *tirada;

        rlutil::locate(31, 5);
        cout << "TIRADAS TOTALES: " << tiradasTotales[turno];

    }
    void dibujarInterfazJuego(){
        // Longitud de la linea
        int longitud = 119;

        int posX, posY;

        // Separacion entre lineas
        int separacion = 3;

        // Limpiamos la pantalla de ingresar nombres
        rlutil::cls();

        // Posicionn inicial del cursor
        posX = 1;
        posY = 3;

        // Dibujo las dos primera lineas horizontal
        pen::drawHorizontalLines(posX, posY, 223, longitud, separacion, 2);

        // Cambio la posicion de la tercera linea horizontal y dibujo
        posY = 20;

        pen::drawHorizontalLines(posX, posY, 223, longitud, 0, 1);

        // Cambiamos la longitud de la linea
        longitud = 1;

        // Cambiamos posicion del cursor para dibujar las lineas verticales
        posX = 22;
        posY = 1;

        // Separacion entre lineas
        separacion = 30;

        // Dibujamos lineas verticales
        pen::drawVerticalLines(posX, posY, 219, longitud, separacion, 2);
    }

    void dibujarMayorPuntaje(char nombreMax[15], int tiradasTotalesMax, int puntajeMax){
        // Limpiamos la pantalla de juego
        rlutil::cls();

        // Dibujamos un rectangulo
        dibujarCuadradoRectangulo(25, 12, 60, 15);

        // Mostramos en mensaje en el medio del rectangulo dibujado
        rlutil::locate(40, 18);
        cout << "El jugador " << nombreMax;

        rlutil::locate(40, 20);
        cout << "En " << tiradasTotalesMax << " tiradas";

        rlutil::locate(40, 22);
        cout << "obtuvo " << puntajeMax << " puntos";

        rlutil::locate(10, 10);
        cout << "Presione cualquier tecla para continuar";


    }
    void dibujarPantallaPrimerIngresoManual(){
        // Limpiamos la pantalla de juego
        rlutil::cls();

        // Dibujamos un rectangulo
        dibujarCuadradoRectangulo(25, 12, 60, 15);

        // Mostramos en mensaje en el medio del rectangulo dibujado
        rlutil::locate(40, 18);
        cout << "Ingrese los primeros valores del dado";
    }
    void dibujarPantallaCambioTurno(char nombres[2][15], int tiradasTotales[2], int puntajes[2], int ronda, int turno){
        // Limpiamos la pantalla de juego
        rlutil::cls();

        // Dibujamos un rectangulo
        dibujarCuadradoRectangulo(25, 12, 60, 15);

        // Mostramos en mensaje en el medio del rectangulo dibujado
        rlutil::locate(40, 18);
        cout << "Ronda N"<< (char)167 << " " <<ronda;

        rlutil::locate(40, 19);
        cout << "Proximo turno: " << nombres[turno];

        rlutil::locate(40, 20);
        cout << "Tiradas totales: " << tiradasTotales[turno];

        rlutil::locate(40, 22);
        cout << "Puntaje " << nombres[0] << ": " << puntajes[0] << " puntos";

        rlutil::locate(40, 23);
        cout << "Puntaje " << nombres[1] << ": " << puntajes[1] << " puntos";

        rlutil::locate(5, 30);
        cout << "Presione cualquier tecla para continuar.....";

    }
}
