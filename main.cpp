#include <iostream>
#include "rlutil.h"
#include "pen.h"
#include "rules.h"
#include <stdio.h>
#include <time.h>
#include "utils.h"

using namespace std;

///funcion para pintar el selector del menu
void show(const char *text, bool select, int posX, int posY)
{
    if (select)
    {
        rlutil::setBackgroundColor(rlutil::BLUE);
    }
    else
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
    }
    rlutil::locate(posX, posY);

    cout << text;
    rlutil::setBackgroundColor(rlutil::BLACK);
}
///Tirar dados
int tiradaDados()
{
    return 1 + rand() % (7 - 1);
}
///Funcion para asignar los puntos a los jugadores y terminar la partida
void gamePlay(int combinaciones[10][4], int puntajes[2], int key, int tirada, int tiradasTotales[2], int ronda, char nombres[2][15], bool *terminarPartida, bool ingresoManual, int *turno, int *modo)
{
    bool genServJ1 = false;
    int cont = 0;

    for(int i = 0; i < 10; i++){
        if(combinaciones[i][0] == key){
            puntajes[*turno] = puntajes[*turno] + combinaciones[i][3];
            combinaciones[i][*turno+1] = 0;
        }
    }
    for(int i = 0; i < 10; i++){
        if(combinaciones[i][1] == 0){
            cont++;
        }
    }
    if(cont == 10){
        if(*modo == 0 && *turno == 0){
            *terminarPartida = true;
        }else if(*modo == 1){
            *modo = 0;
            *turno = 1;
        }
    }
    cont = 0;
    for(int i = 0; i < 10; i++){
        if(combinaciones[i][2] == 0){
            cont++;
        }
    }
    if(cont == 10){
        *terminarPartida = true;
    }

    if(ronda == 1 && tirada == 1){
        if(combinaciones[9][3] != 0 && key == combinaciones[9][0]){
            if(*turno==0){
                if(*modo==0){
                    pen::dibujarPantallaFinal(nombres[*turno], tiradasTotales[*turno], puntajes[*turno]);
                    *terminarPartida = true;
                }
            }else if(*turno == 1 && puntajes[0] == 50){
                if(*modo == 1){
                    *terminarPartida = true;
                }
            }
        }
        }
        if(*terminarPartida==true){
        pen::dibujarPantallaFinal(nombres[*turno], tiradasTotales[*turno], puntajes[*turno]);
        }
    if(puntajes[1] > 0 && *terminarPartida == true){
        if(puntajes[0] > puntajes[1]){
            pen::dibujarPantallaFinal(nombres[0], tiradasTotales[0], puntajes[0]);
        }else{
            pen::dibujarPantallaFinal(nombres[1], tiradasTotales[1], puntajes[1]);
        }

    }else if(puntajes[1] == 0 && *terminarPartida == true){
        pen::dibujarPantallaFinal(nombres[0], tiradasTotales[0], puntajes[0]);
    }



}
///Funcion de los nombres de las combinaciones
void nombresDeCombinacionesGanadoras(int n){
    switch(n){
        case 0: cout << "Juego de a 1" << endl;
            break;
        case 1: cout << "Juego de a 2" << endl;
            break;
        case 2: cout << "Juego de a 3" << endl;
            break;
        case 3: cout << "Juego de a 4" << endl;
            break;
        case 4: cout << "Juego de a 5" << endl;
            break;
        case 5: cout << "Juego de a 6" << endl;
            break;
        case 6: cout << "Escalera" << endl;
            break;
        case 7: cout << "Full" << endl;
            break;
        case 8: cout << "Poker" << endl;
            break;
        case 9: cout << "Generala" << endl;
            break;
    }
}
///Funcion de las posibles combinaciones ganadoras
void posiblesCombinaciones(int dados[5], int combinaciones[10][4], int turno)
{

    for(int i = 0; i < 6; i++){
        combinaciones[i][3] = combinaciones[i][turno+1] == 1 ? rules::PuntosFuncion1A6(dados, 5, i+1) : 0;
    }

    if(combinaciones[6][turno+1] == 1 && rules::EscaleraFuncion(dados, 5)){
        combinaciones[6][3] = 20;
    }else{
        combinaciones[6][3] = 0;
    }
    if(combinaciones[7][turno+1] == 1 && rules::FullFuncion(dados, 5)){
        combinaciones[7][3] = 30;
    }else{
        combinaciones[7][3] = 0;
    }
    if(combinaciones[8][turno+1] == 1 && rules::PokerFuncion(dados, 5)){
        combinaciones[8][3] = 40;
    }else{
        combinaciones[8][3] = 0;
    }
    if(combinaciones[9][turno+1] == 1 && rules::GeneralaFuncion(dados, 5)){
        combinaciones[9][3] = 50;
    }else{
        combinaciones[9][3] = 0;
    }
}
///Funcion para ingresar dados manual
void ingresarDadosManual(int dados[5], int xInit  , const int y  ){
    int x = xInit;
    int key;
///Para obtener el valor Ascii del numero ingresado
    for(int i = 0; i < 5; i++){
        key = rlutil::getkey() - 48;
        rlutil::locate(x , y);
        cout << key;
        dados[i] = key;
        x += 5;
    }
}

///Funcion para calcular los puntos de las combinaciones ganadores en cada tirada
void combinationController(int dados[5], int combinaciones[10][4], int turno){
    int indice = 0;
    posiblesCombinaciones(dados, combinaciones, turno);

        cout << endl;
        for(int i = 0; i < 10; i++){
            if(combinaciones[i][turno+1] == 1){
                combinaciones[i][0] = indice;
                indice++;
            }else{
                combinaciones[i][0] = -1;
            }
        }
        cout << endl;
        for (int i = 0; i < 10; i++)
        {
            if(combinaciones[i][turno+1] == 1 && combinaciones[i][3] != 0){
                cout << combinaciones[i][0] << "_ " << combinaciones[i][3] << " ";
                nombresDeCombinacionesGanadoras(i);
            }else if(combinaciones[i][turno+1] == 1){
                cout << combinaciones[i][0] << "_ ";
                nombresDeCombinacionesGanadoras(i);
            }

        }
}
///Funcion que controla gran parte del juego
void mainController(int dados[5], int dadosAtirar[5], int combinaciones[10][4], int *tirada, int puntajes[2], int *ronda, char nombres[2][15], int tiradasTotales[2], bool ingresoManual, bool *terminarPartida, int *turno, int *modo){
    int key = 0;
    bool dadosInvalidos = false;
    int cantDados;

    if(*tirada != 3){
        rlutil::locate(1, 16);
        cout << (char)168 << "CONTINUAR LANZANDO (S/N)" << (char)63;
        key = rlutil::getkey();
    }
    if ((key == 115 || key == 83) && *tirada != 3)
    {

        rlutil::locate(1, 17);
        cout << (char)168 << "CUANTOS DADOS VOLVES A TIRAR" << (char)63;

        // Pasa de ascii a decimal
        cantDados = rlutil::getkey() - 48;

        if(cantDados > 0 && cantDados < 6){
            cout << cantDados;
            rlutil::locate(1, 18);
            cout << (char)168 << "CUAL" << (char)63;

            for (int i = 0; i < cantDados; i++)
            {
                dadosAtirar[i] = rlutil::getkey() - 48;
                cout << dadosAtirar[i];
            }
            for(int i = 0; i < 5; i++){
                if(dadosAtirar[i] < 0 || dadosAtirar[i] > 6){
                    utils::blanquearVector(dadosAtirar, 5);
                    dadosInvalidos = true;
                }
            }
            if(!dadosInvalidos){
                *tirada += 1;
                tiradasTotales[*turno] = tiradasTotales[*turno] + 1;
            }

        }
        dadosInvalidos = false;

    }
    else if (key == 78 || key == 110 || *tirada == 3)
    {
        rlutil::locate(1, 20);
        cout << (char)168 << "Que combinacion elegis para cancelar o apuntar" << (char)63;

        combinationController(dados, combinaciones, *turno);

        key = rlutil::getkey() - 48;
        cout << key;

        gamePlay(combinaciones, puntajes, key, *tirada, tiradasTotales, *ronda, nombres, terminarPartida, ingresoManual, turno, modo);

        rlutil::locate(20,30);
        *tirada = 1;
        if(*terminarPartida != true){
            if(*modo == 1){
                if(*turno == 1){
                    *ronda = *ronda + 1;
                }
                tiradasTotales[*turno] = tiradasTotales[*turno] + 1;
                *turno = *turno == 0 ? 1 : 0;

                pen::dibujarPantallaCambioTurno(nombres, tiradasTotales, puntajes, *ronda, *turno);

            }else{
                if(*turno == 1){
                    pen::dibujarPantallaCambioTurno(nombres, tiradasTotales, puntajes, *ronda, *turno);
                }
                *ronda = *ronda + 1;
                tiradasTotales[0] = tiradasTotales[0] + 1;
            }
        }


        if(ingresoManual && *terminarPartida != true){
            if(*modo == 1){
                rlutil::anykey();
                rlutil::cls();
                pen::dibujarCuadradoRectangulo(25, 12, 60, 15);
                rlutil::locate(40,15);
                cout << "Ingrese los valores del dado para el siguiente turno";
            }else{
                rlutil::locate(60,22);
                cout << "Ingrese los valores del dado para la siguiente ronda";
            }

            ingresarDadosManual(dados,90,25);

        }
    }else if(key == 80 || key == 112){
        if(ingresoManual){
            rlutil::locate(60, 22);
            cout << "Ingrese los valores del dado para la siguiente tirada";
            ingresarDadosManual(dados,90,25);

            *tirada += 1;
            tiradasTotales[*turno] = tiradasTotales[*turno] + 1;



        }

    }
    rlutil::anykey();
}




int main()
{
    ///se inicializa el modulo random
    srand(time(NULL));
    ///se declaran las variables que se van a usar en el juego
    char nombres[2][15], nombreMax[15];
    int tiradasTotales[2], dados[5], dadosAtirar[5];
    int x, y, ronda;
    int opc, key, tirada;
    int combinaciones[10][4], puntajes[2];
    int rondaAnt, puntajeMax, tiradasTotalesMax;
    int turnoAnt, turno, modo;
    bool terminarPartida, terminarJuego = false;
    bool ingresoManual = false;
    ///se inicializan las variables en X e Y con la posicion inicial del cursor
    x = 0;
    y = 0;
    ///se inicializa la variable puntajeMax para guardar el puntaje maximo
    puntajeMax = 0;

    rlutil::hidecursor();
    ///se asigna el tamaño de la consola
    system("mode con: cols=120 lines=40");
    ///se inicializa el juego
    do{
        rlutil::cls();
    ///se inicializa el menu
        do{

            rlutil::setBackgroundColor(rlutil::BLACK);
            rlutil::setColor(rlutil::WHITE);
            show(" UN JUGADOR ", y == 0, 50, 20);
            show(" DOS JUGADORES ", y == 1, 50, 21);
            show(" MAYOR PUNTAJE ", y == 2, 50, 22);
            show(" SALIR ", y == 3, 50, 23);
            show(" Manual input", ingresoManual, 10, 10);
            key = rlutil::getkey();
            ///Ingreso manual es una flag para saber si se ingresa de manera el valor de los dados o no
            switch (key){
            case rlutil::KEY_DOWN:
                y++;
                if (y > 3)
                {
                    y = 3;
                }
                break;
            case rlutil::KEY_UP:
                y--;
                if (y < 0)
                {
                    y = 0;
                }
                break;
            case rlutil::KEY_ENTER:
                opc = y;
                break;
            case rlutil::KEY_ESCAPE:
                return 0;
            case 80:
                ingresoManual = true;
                break;
            case 112:
                ingresoManual = true;
                break;
            case 113:
                ingresoManual = false;
                break;
            case 81:
                ingresoManual = false;
                break;
            }
        }while(key != rlutil::KEY_ENTER);

        ///Un jugador
        if (opc == 0){
            ///Se inicalizan las variables para el modo un jugador
            tirada = 1;
            ronda = 1;
            ///La variable rondaAnt se utiliza para actuzalizar los dados cuando se selecciona una combinacion ganadora
            rondaAnt = ronda;
            turno = 0;
            modo = 0;
            ///Se habilitan las combinaciones ganadoras del jugador 1
            for(int i = 0; i < 10; i++){
                combinaciones[i][1] = 1;
                combinaciones[i][2] = -1;
            }
            ///Funcion para blanquear vectores
            utils::blanquearVector(puntajes, 2);
            utils::blanquearVector(tiradasTotales, 2);

            tiradasTotales[0] = 1;
            ///Funcion para la interfaz
            pen::pedirNombres(nombres);
            if(ingresoManual){
                ///Funcion ingreso manual de dados
                pen::dibujarPantallaPrimerIngresoManual();
                ingresarDadosManual(dados, 40, 20);
            }else{
                for (int i = 0; i < 5; i++){
                    dados[i] = tiradaDados();
                }
            }

            ///Va reseteando el vector
            utils::blanquearVector(dadosAtirar, 5);
            ///Se inicializa la variable terminarPartida = false iniciar una nueva partida
            terminarPartida = false;
            do
            {
                ///Se actualiza la pantalla
                rlutil::cls();
                pen::dibujarInterfazJuego();
                ///Si no se se ingresa los dados de manera manual
                if(!ingresoManual){
                    for (int i = 0; i < 5; i++){

                        for (int j = 0; j < 5; j++){

                            if (dadosAtirar[j] - 1 == i)
                            {
                                dados[i] = tiradaDados();
                            }
                        }
                        if(ronda != rondaAnt){
                            dados[i] = tiradaDados();
                        }
                    }
                }

                rondaAnt = ronda;


                utils::blanquearVector(dadosAtirar, 5);

                pen::dibujarContenidoInterfaz(nombres, dados, &ronda, &tirada, puntajes, tiradasTotales, turno);
                ///Funcion que controla la partida
                mainController(dados, dadosAtirar, combinaciones, &tirada, puntajes, &ronda, nombres, tiradasTotales, ingresoManual, &terminarPartida, &turno, &modo);
            } while (terminarPartida != true);
            utils::maximoPuntaje(puntajes[0], tiradasTotales[0], nombres[0], &puntajeMax, &tiradasTotalesMax, nombreMax);
        }else if(opc == 1){
            //DOS JUGADORES
            tirada = 1;
            ronda = 1;
            turno = 0;
            modo = 1;
            turnoAnt = turno;

            for(int i = 0; i < 10; i++){
                combinaciones[i][1] = 1;
                combinaciones[i][2] = 1;
            }

            utils::blanquearVector(puntajes, 2);
            utils::blanquearVector(tiradasTotales, 2);

            tiradasTotales[0] = 1;
            tiradasTotales[1] = 1;

            pen::pedirNombres(nombres, 0);
            pen::pedirNombres(nombres, 1);

            if(ingresoManual){
                pen::dibujarPantallaPrimerIngresoManual();
                ingresarDadosManual(dados, 40, 20);
            }else{
                for (int i = 0; i < 5; i++){
                    dados[i] = tiradaDados();
                }
            }

            utils::blanquearVector(dadosAtirar, 5);

            terminarPartida = false;
            do
            {

                rlutil::cls();
                pen::dibujarInterfazJuego();

                if(!ingresoManual){
                    for (int i = 0; i < 5; i++){

                        for (int j = 0; j < 5; j++){

                            if (dadosAtirar[j] - 1 == i)
                            {
                                dados[i] = tiradaDados();
                            }
                        }
                        if(turno != turnoAnt){
                            dados[i] = tiradaDados();
                        }
                    }
                }

                turnoAnt = turno;


                utils::blanquearVector(dadosAtirar, 5);

                pen::dibujarContenidoInterfaz(nombres, dados, &ronda, &tirada, puntajes, tiradasTotales, turno);
                mainController(dados, dadosAtirar, combinaciones, &tirada, puntajes, &ronda, nombres, tiradasTotales, ingresoManual, &terminarPartida, &turno, &modo);
            } while (terminarPartida != true);
            utils::maximoPuntaje(puntajes[0], tiradasTotales[0], nombres[0], &puntajeMax, &tiradasTotalesMax, nombreMax);
            utils::maximoPuntaje(puntajes[1], tiradasTotales[1], nombres[1], &puntajeMax, &tiradasTotalesMax, nombreMax);
        }else if(opc == 2){
            ///Mayor puntaje
            pen::dibujarMayorPuntaje(nombreMax, tiradasTotalesMax, puntajeMax);
            rlutil::anykey();
        }else if(opc == 3){
            ///Salir
            terminarJuego = true;
        }

    }while(!terminarJuego);

    return 0;

}
