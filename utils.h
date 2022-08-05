namespace utils
{

    void blanquearVector(int v[], int tam)
    {
        for (int i = 0; i < tam; i++)
        {
            v[i] = 0;
        }
    }
    void cargarVectorEntero(int v[], int tam, int n)
    {
        for (int i = 0; i < tam; i++)
        {
            v[i] = n;
        }
    }
    void cargarVectorBooleano(bool v[], int tam, bool n)
    {
        for (int i = 0; i < tam; i++)
        {
            v[i] = n;
        }
    }
    void maximoPuntaje(int puntaje, int tiradasTotales, char nombre[15] ,int *puntajeMax, int *tiradasTotalesMax, char nombreMax[15]){
        if(puntaje > *puntajeMax){
            *puntajeMax = puntaje;
            *tiradasTotalesMax = tiradasTotales;
            strcpy(nombreMax, nombre);
            cout << tiradasTotales;
        }

    }
}