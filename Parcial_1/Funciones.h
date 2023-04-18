#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
#include <fstream>
#endif // FUNCIONES_H


void CargarMaterias(char Codigos[20][7], char Nombres[20][40], char *Teoricas, char *Independientes, char *Creditos);
void Reiniciar(char* Arreglo, unsigned int Tamano);
void CopiarA(char *Arreglo, char *Arreglo2, unsigned int Tamano);

void CargarMaterias(char Codigos[20][7], char Nombres[20][40], char *Teoricas, char *Independientes, char *Creditos)
{
    // Se leerá el archivo en formato Codigo:Nombre:Teoricas:Independientes:Creditos
    std::ifstream Archivo("Materias.txt");
    try
    {
        if(!Archivo.is_open())
        {
            throw 0;
        }
        char Letra=0;
        unsigned int IteradorSegmentacion=0, Iterador=0, IteradorMaterias=0;;
        char Codigo[7]={}, Nombre[40]={}, _Teoricas, _Independientes, _Creditos;
        while(Archivo>>std::noskipws >>Letra)
        {
            if(Letra=='\n')
            {
                IteradorSegmentacion=0;
                CopiarA(Codigo, Codigos[IteradorMaterias], 7);
                CopiarA(Nombre, Nombres[IteradorMaterias],40);
                *(Teoricas+IteradorMaterias)=_Teoricas;
                *(Independientes+IteradorMaterias)=_Independientes;
                *(Creditos+IteradorMaterias)=_Creditos;

                Reiniciar(Codigo, 7);
                Reiniciar(Nombre, 30);
                _Teoricas=0;
                _Independientes=0;
                _Creditos=0;
                IteradorMaterias+=1;
                Iterador=0;
            }
            else if(Letra==':')
            {
                IteradorSegmentacion+=1;
                Iterador=0;
            }
            else if(IteradorSegmentacion==0)
            {
                *(Codigo+Iterador)=Letra;
                Iterador+=1;
            }
            else if (IteradorSegmentacion==1)
            {
                *(Nombre+Iterador)=Letra;
                Iterador+=1;
            }
            else if(IteradorSegmentacion==2)
            {
                _Teoricas=Letra;
                Iterador+=1;
            }
            else if(IteradorSegmentacion==3)
            {
                _Independientes=Letra;
                Iterador+=1;
            }
            else if(IteradorSegmentacion==4)
            {
                _Creditos=Letra;
                Iterador+=1;
            }
        }
        Archivo.close();
    }
    catch (int Excepcion)
    {
        std::cout << "Excepcion #" << Excepcion;
        switch (Excepcion)
        {
        case 0:
            std::cout << ": No se ha podido abrir el archivo" << std::endl;
            break;
        default:
            break;
        }
    }
}

void Reiniciar(char* Arreglo, unsigned int Tamano)
{
    //Reinicio del arreglo a 0
    for(unsigned int i=0; i<Tamano; i++)
    {
        *(Arreglo+i)=0;
    }
}

void CopiarA(char *Arreglo, char *Arreglo2, unsigned int Tamano)
{
    //Copia Arreglo a Arreglo2
    for(unsigned int i=0; i< Tamano; i++)
    {
        *(Arreglo2+i)=*(Arreglo+i);
    }
}

void CalculoIndependientes(char *Teoricas, char *Independientes, char *Creditos)
{
    for(int i=0; i<20; i++)
    {
        if(Creditos[i]==0)
        {
            break;
        }
        unsigned int Horas=(Creditos[i]-48)*3;
        unsigned int HorasTeoricas=Teoricas[i]-48;
        *(Independientes+i)=Horas-HorasTeoricas+48;
    }
}
