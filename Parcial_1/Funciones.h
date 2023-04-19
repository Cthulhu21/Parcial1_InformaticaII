#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
#include <fstream>
#endif // FUNCIONES_H


void CargarMaterias(char Codigos[20][7], char Nombres[20][40], char *Teoricas, char *Independientes, char *Creditos, char Horarios[20][40]);
void Reiniciar(char* Arreglo, unsigned int Tamano);
void CopiarA(char *Arreglo, char *Arreglo2, unsigned int Tamano);
void GestionHorario(char Horario[7][24], char Codigos[20][7], char Nombres[20][40], char Creditos[20],  char Horarios[20][40]);
void MostrarOferta(char Codigos[20][7], char Nombres[20][40],char Creditos[20],char Horarios[20][40]);

void CargarMaterias(char Codigos[20][7], char Nombres[20][40], char *Teoricas, char *Independientes, char *Creditos, char Horarios[20][40])
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
        char Codigo[7]={}, Nombre[40]={}, _Teoricas, _Independientes, _Creditos, Horario[40]={};
        while(Archivo>>std::noskipws >>Letra)
        {
            if(Letra=='\n')
            {
                IteradorSegmentacion=0;
                CopiarA(Codigo, Codigos[IteradorMaterias], 7);
                CopiarA(Nombre, Nombres[IteradorMaterias],40);
                CopiarA(Horario, Horarios[IteradorMaterias],40);
                *(Teoricas+IteradorMaterias)=_Teoricas;
                *(Independientes+IteradorMaterias)=_Independientes;
                *(Creditos+IteradorMaterias)=_Creditos;

                Reiniciar(Codigo, 7);
                Reiniciar(Nombre, 40);
                Reiniciar(Horario, 40);
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
            else
            {
                *(Horario+Iterador)=Letra;
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

void GestionHorario(char Horario[7][24], char Codigos[20][7], char Nombres[20][40], char Creditos[20], char Horarios[20][40])
{
    using namespace std;
    {
        std::cout<<"A continuacion se le mostraran las materias ofertadas y usted elegira cuales desea cursar 1 a 1" << std::endl;
        char Entrada[2]={};
        do
        {
            MostrarOferta(Codigos, Nombres, Creditos, Horarios);
            cout<< "Ingrese el numero de la materia que desea registrar en su horario (0 para salir)" << endl;
            cin >> Entrada;
        }while(Entrada[0]==true);
    }
}

void MostrarOferta(char Codigos[20][7], char Nombres[20][40],char Creditos[20], char Horarios[20][40])
{
    using namespace std;
    {
        cout << "Numero\tCodigo\t\tNombre\t\t\t\t\tCreditos\tHorarios\n";
        unsigned int Tamano=0;
        for(int i=0; i<20;i++)
        {
            if(Codigos[i][0]=='\0')
            {
                break;
            }
            Tamano+=1;
        }
        for(unsigned int i=0; i<Tamano;i++) //Mostrar codigos
        {
            cout <<i+1<<"\t";
            for(int j=0; j<7; j++)
            {
                cout << Codigos[i][j];
            }
            cout <<"\t\t";
            for(int j=0; j<40; j++) //Mostrar Nombres
            {
                cout << Nombres[i][j];
                if(Nombres[i][j]=='\0')
                {
                    cout<<"\t\t\t";
                    break;
                }
            }
            cout << Creditos[i]<<"\t"; //Mostrar Creditos
            for(int j=0; j<40; j++)
            {
                if(Horarios[i][j]=='\0')
                {
                    break;
                }
                if(Horarios[i][j]>64 and Horarios[i][j]<91)
                {
                    cout << "\t";
                }
                cout << Horarios[i][j];
            }
            cout << endl;
        }
    };
}
