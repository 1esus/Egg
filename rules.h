#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

namespace rules
{
    bool GeneralaFuncion(int vec[], int tam)
    {
        int i, x;
        for (i = 0; i < tam; i++)
        {
            for (x = 0; x < tam; x++)
            {
                if (vec[x] != vec[i])
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool PokerFuncion(int vec[], int tam)
    {
        int i, x, dif = 0, cont = 0, cont2 = 0;
        for (i = 0; i < tam; i++)
        {
            dif = 0;
            cont = 0;
            cont2 = 0;
            for (x = 0; x < tam; x++)
            {
                if (vec[x] == vec[i])
                {
                    cont++;
                }
                else
                {
                    if (dif == 0)
                    {
                        cont2++;
                        dif = vec[x];
                    }
                    else
                    {
                        if (vec[x] == dif)
                        {
                            cont2++;
                        }
                    }
                }
            }
        }
        if (cont == 4 || cont2 == 4)
        {
            return true;
        }
        return false;
    }

    bool FullFuncion(int vec[], int tam)
    {
        int i, x, dif = 0, cont = 0, cont2 = 0;
        for (i = 0; i < tam; i++)
        {
            dif = 0;
            cont = 0;
            cont2 = 0;
            for (x = 0; x < tam; x++)
            {
                if (vec[x] == vec[i])
                {
                    cont++;
                }
                else
                {
                    if (dif == 0)
                    {
                        cont2++;
                        dif = vec[x];
                    }
                    else
                    {
                        if (vec[x] == dif)
                        {
                            cont2++;
                        }
                    }
                }
            }
        }
        if ((cont == 3 && cont2 == 2) || (cont == 2 && cont2 == 3))
        {
            return true;
        }
        return false;
    }

    bool EscaleraFuncion(int vec[], int tam)
    {
        int i, x, cont = 0, cont2 = 0;
        for (i = 0; i < tam; i++)
        {
            cont2 = 0;
            for (x = 0; x < tam; x++)
            {
                if (vec[x] == 1 || vec[x] == 6)
                {
                    if (cont2 == 0)
                    {
                        cont2 = 1;
                        if ((vec[x] == vec[i]) && (x != i))
                        {
                            cont = 1;
                        }
                    }
                    else
                    {
                        cont = 1;
                    }
                }
                else
                {
                    if ((vec[x] == vec[i]) && (x != i))
                    {
                        cont = 1;
                    }
                }
            }
        }
        if (cont == 0)
        {
            return true;
        }
        return false;
    }

    int PuntosFuncion1A6(int vec[], int tam, int punto){
        int cont = 0;
        for(int i = 0; i < tam; i++){
            if(vec[i] == punto){
                cont+=punto;
            }
        }
        return cont;
    }
    /*int Puntos1Funcion(int vec[], int tam)
    {
        int i, cont = 0;
        for (i = 0; i < tam; i++)
        {
            if (vec[i] == 1)
            {
                cont += 1;
            }
        }
        return cont;
    }

    int Puntos2Funcion(int vec[], int tam)
    {
        int i, cont = 0;
        for (i = 0; i < tam; i++)
        {
            if (vec[i] == 2)
            {
                cont += 2;
            }
        }
        return cont;
    }

    int Puntos3Funcion(int vec[], int tam)
    {
        int i, cont = 0;
        for (i = 0; i < tam; i++)
        {
            if (vec[i] == 3)
            {
                cont += 3;
            }
        }
        return cont;
    }

    int Puntos4Funcion(int vec[], int tam)
    {
        int i, cont = 0;
        for (i = 0; i < tam; i++)
        {
            if (vec[i] == 4)
            {
                cont += 4;
            }
        }
        return cont;
    }

    int Puntos5Funcion(int vec[], int tam)
    {
        int i, cont = 0;
        for (i = 0; i < tam; i++)
        {
            if (vec[i] == 5)
            {
                cont += 5;
            }
        }
        return cont;
    }

    int Puntos6Funcion(int vec[], int tam)
    {
        int i, cont = 0;
        for (i = 0; i < tam; i++)
        {
            if (vec[i] == 6)
            {
                cont += 6;
            }
        }
        return cont;
    }
    */
}
