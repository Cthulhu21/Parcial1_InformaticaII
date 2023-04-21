#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
#include <fstream>
#endif // FUNCIONES_H


//void CargarMaterias(char Codigos[20][7], char Nombres[20][40], char *Teoricas, char *Independientes, char *Creditos, char Horarios[20][40]);
void Reiniciar(char* Arreglo, unsigned int Tamano);
void CopiarA(char *Arreglo, char *Arreglo2, unsigned int Tamano);
void GestionHorario(char Horario[168][7], char Codigos[20][7], char Nombres[20][40], char Creditos[20],  char Horarios[20][40]);
void MostrarOferta(char Codigos[20][7], char Nombres[20][40],char Creditos[20],char Horarios[20][40]);
void MeterEnHorario(char Horario[168][7], char Codigo[7], char HorariosMaterias[40]);
void MostrarHorario(char Horario[168][7], char Codigos[20][7], char Nombres[20][40]);
void MostrarNombreDeCodigo(char Codigo[7], char Codigos[20][7], char Nombres[20][40], char Nombre[40]);
void PosicionCodigo(char Codigo[7], char Codigos[20][7], unsigned int *Posicion);

void CargarMaterias(char Codigos[20][7], char Nombres[20][40], char *Teoricas, char *Independientes, char *Creditos, char Horarios[20][40])
{
    using namespace std;
    // Se leerá el archivo en formato Codigo:Nombre:Teoricas:Independientes:Creditos
    ifstream Archivo("Materias.txt");
    try
    {
        //Se guardan los datos en los arrays
        if(!Archivo.is_open())
        {
            throw 0;
        }
        char Letra=0;
        unsigned int IteradorSegmentacion=0, Iterador=0, IteradorMaterias=0;;
        char Codigo[7]={}, Nombre[40]={}, _Teoricas=0, _Independientes=0, _Creditos=0, Horario[40]={};
        while(Archivo>>noskipws >>Letra) // Itera sin saltar espacios en blanco (incluye tabs, retornos de linea)
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
    //Reinicio del arreglo a \0
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
        unsigned int Horas=(Creditos[i]-48)*3; // 3 porque sería 48/16
        unsigned int HorasTeoricas=Teoricas[i]-48;
        *(Independientes+i)=Horas-HorasTeoricas+48;
    }
}

void GestionHorario(char Horario[168][7], char Codigos[20][7], char Nombres[20][40], char Creditos[20], char Horarios[20][40])
{
    using namespace std;
    {
        cout<<"A continuacion se le mostraran las materias ofertadas y usted elegira cuales desea cursar 1 a 1" <<endl;
        char Entrada={};
        do
        {
            MostrarOferta(Codigos, Nombres, Creditos, Horarios);
            cout<< "Ingrese el numero de la materia que desea registrar en su horario (0 para salir)" << endl;
            cin >> Entrada;
            if(Entrada>48 and Entrada<69) //Sólo 20 materias
            {
                MeterEnHorario(Horario, Codigos[Entrada-49], Horarios[Entrada-49]);
            }
            MostrarHorario(Horario, Codigos, Nombres);
        }while(Entrada!=48);
    }
}

void MeterEnHorario(char Horario[168][7], char Codigo[7], char HorarioMateria[40])
{
    //Lee HorarioMateria para determinar el
    using namespace std;
    unsigned int Dia[3]={}, Horas[3]={}, Duracion[3]={};//Maximo 3 datos
    unsigned int Iterador=0;
    for(int i=0; i<40; i++)
    {
        char Letra=HorarioMateria[i];
        if(Letra=='\0')
        {
            break;
        }
        if(Letra>64 and Letra<91) //Si letra mayuscula
        {
            switch (Letra)
            {
            case 'L':
                Dia[Iterador]=1;
                break;
            case 'M':
                Dia[Iterador]=2;
                break;
            case 'W':
                Dia[Iterador]=3;
                break;
            case 'J':
                Dia[Iterador]=4;
                break;
            case 'V':
                Dia[Iterador]=5;
                break;
            case 'S':
                Dia[Iterador]=6;
                break;
            case 'D':
                Dia[Iterador]=7;
                break;
            default:
                break;
            }
            unsigned int NumTemp=0;
            NumTemp=(HorarioMateria[i+1]-48)*10+(HorarioMateria[i+2]-48);//Se determina a que hora empieza
            Horas[Iterador]=NumTemp;
            unsigned int Decena1=(HorarioMateria[i+3]-48)*10;
            unsigned int Unidad1=(HorarioMateria[i+4]-48);
            unsigned int Decena2=(HorarioMateria[i+1]-48)*10;
            unsigned int Unidad2=(HorarioMateria[i+2]-48);
            NumTemp=Decena1+Unidad1-Decena2-Unidad2;
            Duracion[Iterador]=NumTemp; //Cuanto dura esa sesison
            Iterador+=1;
        }
    }
    for(int i=0; i<3; i++)//Se determina la hora en la semana donde se mete
    {
        if(Dia[i]==0)
        {
            break;
        }
        unsigned int HoraSemanal=(Dia[i]-1)*24+Horas[i];
        unsigned int temp=0;
        if(Horario[HoraSemanal][0]==0)// Si está vacio se puede escoger ese horario
        {
            while(temp<Duracion[i])
            {
                for(int j=0; j<7; j++)
                {
                    Horario[HoraSemanal+temp][j]=Codigo[j];
                }
                temp+=1;
            }
        }
        else
        {
            cout << "Lo sentimos, en este horario presenta incompatibilidad" << endl;
            break;
        }

    }
}

void MostrarOferta(char Codigos[20][7], char Nombres[20][40],char Creditos[20], char Horarios[20][40])
{
    //Muestran los datos de manera "estilizada"
    using namespace std;
    {
        cout << "Numero\tCodigo\t\tNombre\t\t\t\t\tCreditos\tHorarios\n";
        unsigned int Tamano=0;
        for(int i=0; i<20;i++) //Se determina el tamaño usado
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
            for(int j=0; j<40; j++)//Mostrar el horario de la materia
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

void RecomendarHorario(char Codigos[20][7], char Nombres[20][40], char Horario[168][7], char Independientes[20])
{
    using namespace std;
    char Materias[20][7]={};
    unsigned int Iterador=0;
    for(unsigned int i=0; i<168; i++) // Se buscan todas las materias que fueron escogidas por el estudiante
    {
        if(Horario[i][0]!='\0')
        {
            char Codigo[7]={};
            CopiarA(Horario[i],Codigo,7);//Se determina el codigo
            bool Encontrado=false;
            for(unsigned int IteradorMateria=0; IteradorMateria<20; IteradorMateria++)
            {
                //Asegurarse que la materia no se meta varias veces
                if(Materias[IteradorMateria][0]!='\0')
                {
                    char CodigoTemp_[7]={};
                    CopiarA(Materias[IteradorMateria], CodigoTemp_, 7);
                    int Suma=0;
                    for(Suma=0; Suma<7; Suma++)
                    {
                        if(Codigo[Suma]!=CodigoTemp_[Suma])
                        {
                            break;
                        }
                    }
                    if(Suma==7)
                    {
                        Encontrado=true;
                    }
                    if(Encontrado)
                    {
                        break;
                    }
                }
            }
            if(!Encontrado)
            {
                CopiarA(Horario[i],Materias[Iterador],7);
                Iterador+=1;
            }
        }
    }
    for(unsigned int i=0; i<20; i++)
    {
        char Codigo[7]={};
        if(Materias[i][0]!='\0')
        {
            CopiarA(Materias[i], Codigo, 7);
            unsigned int Posicion=-1; // Se compila como el valor maximo
            PosicionCodigo(Codigo, Codigos, &Posicion);
            unsigned int HorasIndependientes=Independientes[Posicion]-48;
            unsigned int PosicionHoras=0;
            while(HorasIndependientes>0)
            {
                if((PosicionHoras%24>6) and (PosicionHoras%24<22))//Se evitan horas extremas
                {
                    if(Horario[PosicionHoras][0]=='\0')
                    {
                        unsigned int iterador=0;
                        while(iterador<7)
                        {
                            Horario[PosicionHoras][iterador]=Codigo[iterador];
                            iterador+=1;
                        }
                        HorasIndependientes-=1;
                    }
                    else
                    {
                        unsigned int Extra=(Horario[PosicionHoras][2]-48)*10%(Codigo[6]-28);//Pseudoaleatorio
                        PosicionHoras+=Extra;
                    }
                }
                PosicionHoras+=2;
                if(PosicionHoras>167)
                {
                    PosicionHoras%=167;
                }
            }
        }
        else
        {
            MostrarHorario(Horario, Codigos, Nombres);
            break;
        }

    }
}


void MostrarHorario(char Horario[168][7], char Codigos[20][7], char Nombres[20][40])
{
    using namespace std;
    cout << "\tLunes\tMartes\tMiercoles\tJueves\tViernes\tSabado\tDomingo\n";
    for(unsigned int i=0; i<24; i++)
    {
        char Codigo[7]={};
        unsigned int Dia=0;
        cout << i << "\t";
        while(Dia<7)
        {
            unsigned int iteradorletras=0;
            while (iteradorletras<7)
            {
                Codigo[iteradorletras]=Horario[(i+(Dia*24))][iteradorletras];
                iteradorletras+=1;
            }
            char Nombre[40];
            MostrarNombreDeCodigo(Codigo, Codigos, Nombres, Nombre);
            Dia+=1;
        }
        cout << endl;
    }
}

void MostrarNombreDeCodigo(char Codigo[7],char Codigos[20][7], char Nombres[20][40], char Nombre[40])
{
    using namespace std;
    unsigned int Posicion=-1;
    PosicionCodigo(Codigo,Codigos,&Posicion);
    unsigned int Iterador=0;
    while(Iterador<40)
    {
        Nombre[Iterador]=Nombres[Posicion][Iterador];
        Iterador+=1;
    }
    cout << "|";
    if(Codigo[0]!='\0')
    {
        cout << Nombre;
    }
    else
    {
       cout <<"0";
    }
    cout << "|\t";
}

void PosicionCodigo(char Codigo[7], char Codigos[20][7], unsigned int *Posicion)
{
    //Halla la posicion de Codigo en Codigos
    *Posicion=-1;
    for(unsigned int IteradorCodigos=0; IteradorCodigos<20; IteradorCodigos++)
    {
       char Codigo_[7]={};
       CopiarA(Codigos[IteradorCodigos], Codigo_, 7);
        /*for(int i=0; i<7; i++)
        {
            Codigo_[i]=Codigos[IteradorCodigos][i];
        }*/
       for(unsigned int PosicionLetra=0; PosicionLetra<7; PosicionLetra++)
       {
           if(Codigo[PosicionLetra]!=Codigos[IteradorCodigos][PosicionLetra])
           {
               break;
           }
           if(PosicionLetra==6)
           {
               *Posicion=IteradorCodigos;
           }
       }
       if(*Posicion!=4294967295)
       {
           break;
       }
    }
}
